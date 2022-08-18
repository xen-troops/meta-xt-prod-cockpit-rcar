#undef QT_NO_SSL
#include <linux/rpmsg.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <QtWebSockets/qwebsocket.h>
#include <QException>
#include <exception>
#include <system_error>
#include <filesystem>
#include <stdexcept>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QTimer>
#include "VisClient.h"
#include <limits>

QT_USE_NAMESPACE

const unsigned long visClientTimeout = 1000;
struct rpmsg_endpoint_info ept_info = {"rpmsg-openamp-demo-channel", 0x2, 0x1};


enum CtlIO_id{
    SPEED = 1,
    GEAR = 2,
    RPM = 3,
    TURN = 4,
};

enum GearPosition{
    PARK    	= 0,
    NEUTRAL 	= 2,
    DRIVE   	= 3,
    REVERSE 	= 4,
    GUNDEFINED 	= 5,
};

const int not_defined_value = std::numeric_limits<int>::max();

typedef struct {
    uint64_t   value;
    uint64_t   ioctl_cmd;
}taurus_cluster_data_t;


VisClient::VisClient(QObject *parent, const QString &url, const QString& rpmsg):QObject(parent),
	mUrl(url),
	mEptInfo{"rpmsg-openamp-demo-channel", 0x2, 0x1},
	mState(SubscrState::StateInit)
{
    qDebug() << "Create VIS client";

    connect(&mWebSocket,
		QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
		this,
		&VisClient::onError);
    connect(&mWebSocket, &QWebSocket::sslErrors, this, &VisClient::onSslErrors);
    connect(&mWebSocket, &QWebSocket::connected, this, &VisClient::onConnected);
    connect(&mWebSocket, &QWebSocket::disconnected, this, &VisClient::onDisconnected);
    connect(&mWebSocket, &QWebSocket::textMessageReceived, this, &VisClient::onTextMessageReceived);

    mFd = open("/dev/rpmsg_ctrl0", O_WRONLY);
    if(mFd < 0){
        throw std::invalid_argument("No device /dev/rpmsg_ctrl0");
    }

    ioctl(mFd, RPMSG_CREATE_EPT_IOCTL, &mEptInfo);

    mFdept = open(rpmsg.toStdString().c_str(), O_WRONLY);

    if(mFdept < 0){
        close(mFd);

        throw std::invalid_argument("No device "+rpmsg.toStdString());
    }
    qDebug() << "Create VIS client - send 100 for test";

    taurus_cluster_data_t data = {
	    .value = 100,
	    .ioctl_cmd = 1,
    };
    // just for the test purposes, to see that connection exists
    while(data.value != 0) {
	write(mFdept, &data, sizeof(data));
	--data.value;
    }
    data.value = 0;
    write(mFdept, &data, sizeof(data));
    qDebug() << "Create VIS client - send 0 to reset";
}
VisClient::~VisClient()
{
    qDebug() << "Delete VIS client";

    ioctl(mFdept, RPMSG_DESTROY_EPT_IOCTL);
    close(mFdept);
    close(mFd);
    mWebSocket.close();
}

void VisClient::connectTo()
{
    qDebug() << "Connect to:" << mUrl;

    mWebSocket.open(QUrl(mUrl));
}

void VisClient::disconnect()
{
    qDebug() << "Disconnect";

    mWebSocket.close();
}

bool VisClient::IsConnected()const
{
    return mWebSocket.state() == QAbstractSocket::ConnectedState;
}

void VisClient::sendMessage(const QString &message)
{
    qDebug() << "Send message:" << message;

    mWebSocket.sendTextMessage(message);
}

void VisClient::onConnected()
{
    auto sId = mID.createUuid().toString().replace("{","").replace("}","");
    mState = SubscrState::StateGetValues;
    qDebug() << "onConnected, state SubscrState::StateGetValues";
    sendMessage("{\"action\": \"get\", \"path\": \"*\", \"requestId\": \"" + sId + "\"}");

}

void VisClient::onDisconnected()
{
    Q_EMIT VisClient::disconnected();
    mState = SubscrState::StateInit;
    connectTo();
}

void VisClient::onSslErrors(const QList<QSslError> &errors)
{
    Q_FOREACH (QSslError error, errors) {
        if (error.error() == QSslError::SelfSignedCertificate
            || error.error() == QSslError::SelfSignedCertificateInChain) {
            mWebSocket.ignoreSslErrors();
            return;
        }
    }
}

void VisClient::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)

    qDebug() << "Error:" << mWebSocket.errorString();

    disconnect();

    Q_EMIT VisClient::error(mWebSocket.errorString());
}

void VisClient::onTextMessageReceived(const QString &message)
{
    qDebug() << "Receive message:" << message;
    // send dummy data 
    taurus_cluster_data_t data = {0, CtlIO_id::SPEED};
    
    QFile file("/var/vis-response-2.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
          // We're going to streaming text to the file
          QTextStream stream(&file);

          stream << message;

          file.close();
          qDebug() << "Writing finished\n";
    }

    qDebug() << "mState: " << mState;

    switch(mState)
    {
       case SubscrState::StateGetValues:
       {
          auto sId = mID.createUuid().toString().replace("{","").replace("}","");
          mState = SubscrState::StateSubscribe;
          qDebug() << "onConnected, send subscription";
          sendMessage("{\"action\": \"subscribe\", \"path\": \"*\", \"requestId\": \"" + sId + "\"}");
       }
       break;
       case SubscrState::StateSubscribe:
       {
          mSubscriptionId = getSubscriptionId(message);
	  mState = SubscrState::StateReady;
	  qDebug() << "Subscribed , Id." << mSubscriptionId;
       }
       break;
       case SubscrState::StateReady:
       {
	    auto sId = getSubscriptionId(message);
            if(sId == mSubscriptionId)
	    {
	       data.value = getSpeed(message);
	       qDebug() << " getSpeed " << data.value;
	       if(data.value != not_defined_value)
               {
		   data.ioctl_cmd = CtlIO_id::SPEED;
                   write(mFdept, &data, sizeof(data));
	       }
	       else
	       {
		  qDebug() << "No speed value in the message";
	       }
	       data.value = (uint64_t)getGearSelect(message);
               qDebug() << " getGear " << data.value;
               if(data.value != not_defined_value)
               {
		   data.ioctl_cmd = CtlIO_id::GEAR;
                   write(mFdept, &data, sizeof(data));
               }
               else
               {
                  qDebug() << "No Gear value in the message";
               }
	       data.value = getRpm(message);
               qDebug() << " getRpm " << data.value;
               if(data.value != not_defined_value)
               {
                   data.ioctl_cmd = CtlIO_id::RPM;
                   write(mFdept, &data, sizeof(data));
               }
               else
               {
                  qDebug() << "No RPM value in the message";
               }
               data.value = getTurnDirection(message);
               qDebug() << " getDirection " << data.value;
               if(data.value != not_defined_value)
               {
                   data.ioctl_cmd = CtlIO_id::TURN;
                   write(mFdept, &data, sizeof(data));
               }
               else
               {
                  qDebug() << "No Turn value in the message";
               }
	    }
	    else
	    {
	        qDebug("Wrong subscription received.");
	    }
       }
       break;
       default:
       {
           qDebug() << "Wrong subscrition state.";
           return;
       }
    }
}

int VisClient::getSpeed(const QString &message)const
{
    int res = getValue("Signal.Vehicle.Speed", message);
    return res == not_defined_value ? not_defined_value : (int)(res/1000);
}

GearPosition VisClient::getGearSelect(const QString & message)const
{
    int val = getValue("Signal.Drivetrain.Transmission.Gear", message);
    GearPosition res = GearPosition::GUNDEFINED;
    switch(val)
    {
	case 0: 
	res = GearPosition::PARK;
	break;
	case 2: 
	res = GearPosition::NEUTRAL;
	break;
	case 3: 
	res = GearPosition::DRIVE;
	break;
	case 4: 
	res = GearPosition::REVERSE;
	break;
    }
    return res;
}

int VisClient::getRpm(const QString & message)const
{
    return getValue("Signal.Drivetrain.InternalCombustionEngine.Engine.Speed", message);
}

int VisClient::getTurnDirection(const QString & message)const
{
    auto value = getStringValue("Signal.Traffic.Turn.Direction", message);
    if(value == "right")
    {
       return 1;
    }
    else if(value == "left")
    {
        return 2;
    }
    return 0;
}

QString VisClient::getStringValue(const QString & propId, const QString & message)const
{
    QString res;
    QByteArray br = message.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(br);
    QJsonObject obj = doc.object();
    QJsonArray arr = obj.value("value").toArray();
    foreach(const QJsonValue &v, arr){
        if(v.toObject().contains(propId)) {
           res = v.toObject().value(propId).toString();
           qDebug()<< propId  << " = " << res;
       }

    }
    return res;
}

int VisClient::getValue(const QString & propId, const QString & message)const
{
    int res = not_defined_value;
    QByteArray br = message.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(br);
    QJsonObject obj = doc.object();
    QJsonArray arr = obj.value("value").toArray();
    foreach(const QJsonValue &v, arr){
        if(v.toObject().contains(propId)) {
           res = (int)(v.toObject().value(propId).toInt());
	   qDebug()<< propId  << " = " << res;
       }

    }
    return res;
}

QString VisClient::getSubscriptionId(const QString &message)const
{
    QString res;
    QByteArray br = message.toUtf8();

    QJsonDocument doc = QJsonDocument::fromJson(br);

    QJsonObject obj = doc.object();
    QJsonValue value = obj.value("subscriptionId");
    res = value.toString();
    qDebug() << " -- getSubscriptionId " << res;
    
    return res;
}
