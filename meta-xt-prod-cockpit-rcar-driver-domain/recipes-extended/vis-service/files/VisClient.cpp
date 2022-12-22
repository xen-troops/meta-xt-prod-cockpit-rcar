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
#include <vector>

QT_USE_NAMESPACE

const unsigned long visClientTimeout = 1000;
struct rpmsg_endpoint_info ept_info = {"rpmsg-openamp-demo-channel", 0x2, 0x1};

enum CtlIO_id{
    SPEED = 1,
    GEAR = 2,
    RPM = 3,
    TURN = 4,
    DOOR_OPEN = 5,
    FOG_LIGHTS_BACK = 6,
    FOG_LIGHTS_FRONT = 7,
    HIGH_BEAMS_LIGHT = 8,
    HIGH_ENGINE_TEMPERATURE = 9,
    LOW_BATTERY = 10,
    LOW_BEAMS_LIGHTS = 11,
    LOW_FUEL = 12,
    LOW_OIL = 13,
    LOW_TIRE_PRESSURE = 14,
    SEAT_BELT = 15,
    SIDE_LIGHTS = 16,
    BATTERY_ISSUE = 17,
    AUTO_LIGHTING_ON = 18,
    CLUSTER_ACTIVE = 255,
};

const int not_defined_value = std::numeric_limits<int>::max();

typedef struct {
    uint64_t   value;
    uint16_t   ioctl_cmd;
}taurus_cluster_data_t;

struct AosVisParameter {
    QString paramName;
    CtlIO_id ctlIOId;
    int value;
    std::function<int(const QString & propId, const QString & message)> getValue;
};

const std::vector<AosVisParameter> aosVisParameters {
    {"Signal.Vehicle.Speed", CtlIO_id::SPEED, not_defined_value, VisClient::getValue},
    {"Signal.Drivetrain.Transmission.Gear", CtlIO_id::GEAR, not_defined_value, VisClient::getValue},
    {"Signal.Drivetrain.InternalCombustionEngine.Engine.Speed", CtlIO_id::RPM, not_defined_value, VisClient::getValue},
    {"Signal.Traffic.Turn.Direction", CtlIO_id::TURN, not_defined_value, VisClient::getTurnDirection},
    {"Signal.Cabin.Door.Row1.Left.IsOpen", CtlIO_id::DOOR_OPEN, not_defined_value, VisClient::getBool},
    {"Signal.Cabin.Door.Row1.Right.IsOpen", CtlIO_id::DOOR_OPEN, not_defined_value, VisClient::getBool},
    {"Signal.Cabin.Door.Row2.Left.IsOpen", CtlIO_id::DOOR_OPEN, not_defined_value, VisClient::getBool},
    {"Signal.Cabin.Door.Row2.Right.IsOpen", CtlIO_id::DOOR_OPEN, not_defined_value, VisClient::getBool},
    {"Signal.Body.Trunk.IsOpen", CtlIO_id::DOOR_OPEN, not_defined_value, VisClient::getBool},
    {"Signal.Cabin.Seat.Row1.Pos1.IsBelted", CtlIO_id::SEAT_BELT, not_defined_value, VisClient::getBeltStatus},
    {"Signal.Cabin.Seat.Row1.Pos2.IsBelted", CtlIO_id::SEAT_BELT, not_defined_value, VisClient::getBeltStatus},
    {"Signal.Cabin.Seat.Row2.Pos1.IsBelted", CtlIO_id::SEAT_BELT, not_defined_value, VisClient::getBeltStatus},
    {"Signal.Cabin.Seat.Row2.Pos2.IsBelted", CtlIO_id::SEAT_BELT, not_defined_value, VisClient::getBeltStatus},
    {"Signal.Body.Lights.IsLowBeamOn", CtlIO_id::LOW_BEAMS_LIGHTS, not_defined_value, VisClient::getBool},
    {"Signal.Body.Lights.IsHighBeamOn", CtlIO_id::HIGH_BEAMS_LIGHT, not_defined_value, VisClient::getBool},
    {"Signal.Body.Lights.IsFrontFogOn", CtlIO_id::FOG_LIGHTS_FRONT, not_defined_value, VisClient::getBool},
    {"Signal.Body.Lights.IsRearFogOn", CtlIO_id::FOG_LIGHTS_BACK, not_defined_value, VisClient::getBool},
    {"Signal.Chassis.Axle.Row1.Wheel.Left.Tire.Pressure", CtlIO_id::LOW_TIRE_PRESSURE, not_defined_value, VisClient::getTireStatus},
};

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

    qDebug() << "!!!! RESET VALUES:" << mUrl;
    for(int i = 5; i < aosVisParameters.size();++i)
    {
        data.value = 0;
        data.ioctl_cmd = i;
        write(mFdept, &data, sizeof(data));
    }
    // inform cr7: cluster is active
    data.value = 1;
    data.ioctl_cmd = CtlIO_id::CLUSTER_ACTIVE;
    write(mFdept, &data, sizeof(data));
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
                for (auto param : aosVisParameters)
                {
                    auto value = param.getValue(param.paramName, message);
                    if(value != not_defined_value)
                    {
                        data.value = value;
                        data.ioctl_cmd = param.ctlIOId;
                        write(mFdept, &data, sizeof(data));
                    }
                    else 
                    {
                        qDebug() << "Not processed parameter:" << param.paramName;
                    }
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

int VisClient::getTurnDirection(const QString & propId, const QString & message)
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
    return not_defined_value;
}

QString VisClient::getStringValue(const QString & propId, const QString & message)
{
    QString res;
    QByteArray br = message.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(br);
    QJsonObject obj = doc.object();
    QJsonArray arr = obj.value("value").toArray();
    foreach(const QJsonValue &v, arr){
        if(v.toObject().contains(propId)) {
           res = v.toObject().value(propId).toString();
       }
    }
    return res;
}

int VisClient::getBool(const QString & propId, const QString & message)
{
    int res = not_defined_value;
    QByteArray br = message.toUtf8();

    QJsonDocument doc = QJsonDocument::fromJson(br);
    if(doc["value"].isObject() && doc["value"][propId].isBool())
    {
        res = (int)doc["value"][propId].toBool();
    }
    return res;
}

int VisClient::getBeltStatus(const QString & propId, const QString & message)
{
    auto res = getBool(propId, message);
    if(res != not_defined_value)
    {
        res = !res;
    }
    return res;
}

int VisClient::getTireStatus(const QString & propId, const QString & message)
{
    int res = not_defined_value;
    QByteArray br = message.toUtf8();

    QJsonDocument doc = QJsonDocument::fromJson(br);
    if(doc["value"].isObject() && !doc["value"][propId].isUndefined())
    {
        res = doc["value"][propId].toInt();
        res = (int)(240 >= res);
    }
    return res;
}

int VisClient::getValue(const QString & propId, const QString & message)
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

QString VisClient::getSubscriptionId(const QString &message)
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
