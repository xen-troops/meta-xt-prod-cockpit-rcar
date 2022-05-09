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


QT_USE_NAMESPACE

const unsigned long visClientTimeout = 1000;
struct rpmsg_endpoint_info ept_info = {"rpmsg-openamp-demo-channel", 0x2, 0x1};

typedef struct {
    int   speed;
    int     rpm;
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
    int speed = 100;
    // just for the test purposes, to see that connection exists
    while(speed != 0) {
	write(mFdept, &speed, sizeof(speed));
	--speed;
    }
    speed = 0;
    write(mFdept, &speed, sizeof(speed));
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
    taurus_cluster_data_t data = {0, 0};
    
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
               data.speed = getSpeed(message);
	       qDebug() << " getSpeed " << data.speed;
	       if(data.speed >= 0)
               {
                   write(mFdept, &data, sizeof(data));
	       }
	       else
	       {
		  qDebug() << "No speed value in the message";
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
    int res = -1;
    QByteArray br = message.toUtf8();

    QJsonDocument doc = QJsonDocument::fromJson(br);

    QJsonObject obj = doc.object();

    QJsonArray arr = obj.value("value").toArray();
    
    const QString speedValue = "Signal.Vehicle.Speed";//"Signal.Cabin.Infotainment.Navigation.CurrentLocation.Speed";

    foreach(const QJsonValue &v, arr){
        if(v.toObject().contains(speedValue)) {//v.toObject().contains("Signal.Emulator.telemetry.veh_speed")) {
           qDebug()<<"speed " << (int)(v.toObject().value(speedValue).toInt()/1000);
	   res = (int)(v.toObject().value(speedValue).toInt()/1000);//"Signal.Emulator.telemetry.veh_speed").toInt();
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
