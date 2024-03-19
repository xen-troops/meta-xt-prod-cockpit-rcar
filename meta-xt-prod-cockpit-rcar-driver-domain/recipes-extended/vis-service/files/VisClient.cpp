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
#include <linux/r_taurus_cluster_protocol.h>

QT_USE_NAMESPACE

const unsigned long visClientTimeout = 1000;
struct rpmsg_endpoint_info ept_info = {"rpmsg-openamp-demo-channel", 0x2, 0x1};
const int not_defined_value = std::numeric_limits<int>::max();
struct AosVisParameter {
    QString paramName;
    uint32_t ctlIOId;
    int value;
    std::function<int(const QString & propId, const QString & message)> getValue;
};

const std::vector<AosVisParameter> aosVisParameters {
    {"Signal.Vehicle.Speed", CLUSTER_SPEED, not_defined_value, VisClient::getValue},
    {"Signal.Drivetrain.Transmission.Gear", CLUSTER_GEAR, not_defined_value, VisClient::getValue},
    {"Signal.Drivetrain.InternalCombustionEngine.Engine.Speed", CLUSTER_RPM, not_defined_value, VisClient::getValue},
    {"Signal.Traffic.Turn.Direction", CLUSTER_TURN, not_defined_value, VisClient::getTurnDirection},
    {"Signal.Cabin.Door.Row1.Left.IsOpen", CLUSTER_DOOR_OPEN, not_defined_value, VisClient::getValue},
    {"Signal.Cabin.Door.Row1.Right.IsOpen", CLUSTER_DOOR_OPEN, not_defined_value, VisClient::getValue},
    {"Signal.Cabin.Door.Row2.Left.IsOpen", CLUSTER_DOOR_OPEN, not_defined_value, VisClient::getValue},
    {"Signal.Cabin.Door.Row2.Right.IsOpen", CLUSTER_DOOR_OPEN, not_defined_value, VisClient::getValue},
    {"Signal.Body.Trunk.IsOpen", CLUSTER_DOOR_OPEN, not_defined_value, VisClient::getBool},
    {"Signal.Cabin.Seat.Row1.Pos1.IsBelted", CLUSTER_SEAT_BELT, not_defined_value, VisClient::getBeltStatus},
    {"Signal.Cabin.Seat.Row1.Pos2.IsBelted", CLUSTER_SEAT_BELT, not_defined_value, VisClient::getBeltStatus},
    {"Signal.Cabin.Seat.Row2.Pos1.IsBelted", CLUSTER_SEAT_BELT, not_defined_value, VisClient::getBeltStatus},
    {"Signal.Cabin.Seat.Row2.Pos2.IsBelted", CLUSTER_SEAT_BELT, not_defined_value, VisClient::getBeltStatus},
    {"Signal.Body.Lights.IsLowBeamOn", CLUSTER_LOW_BEAMS_LIGHTS, not_defined_value, VisClient::getValue},
    {"Signal.Body.Lights.IsHighBeamOn", CLUSTER_HIGH_BEAMS_LIGHT, not_defined_value, VisClient::getValue},
    {"Signal.Body.Lights.IsFrontFogOn", CLUSTER_FOG_LIGHTS_FRONT, not_defined_value, VisClient::getValue},
    {"Signal.Body.Lights.IsRearFogOn", CLUSTER_FOG_LIGHTS_BACK, not_defined_value, VisClient::getValue},
    {"Signal.Chassis.Axle.Row1.Wheel.Left.Tire.Pressure", CLUSTER_LOW_TIRE_PRESSURE, not_defined_value, VisClient::getTireStatus},
};

VisClient::VisClient(QObject *parent, const QString &url, const QString& rpmsg):QObject(parent),
	mUrl(url),
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

    mFdept = open("/dev/cluster-taurus", O_WRONLY);
    if(mFdept < 0){
        throw std::invalid_argument("No device /dev/cluster-taurus");
    }

    qDebug() << "Create VIS client - send 0 to reset";

    qDebug() << "!!!! RESET VALUES:" << mUrl;
    for(int i = 5; i < aosVisParameters.size();++i)
    {
        ioctl(mFdept, i, 0);
    }
    ioctl(mFdept, CLUSTER_ACTIVE, 1);
}
VisClient::~VisClient()
{
    qDebug() << "Delete VIS client";
    close(mFdept);
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
    struct taurus_cluster_data data = {0, CLUSTER_SPEED};
    
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
                        auto res = ioctl(mFdept, data.ioctl_cmd, data.value);
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
    /*QString res;
    QByteArray br = message.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(br);
    QJsonObject obj = doc.object();
    QJsonArray arr = obj.value("value").toArray();
    foreach(const QJsonValue &v, arr){
        if(v.toObject().contains(propId)) {
           res = v.toObject().value(propId).toString();
       }
    }
    return res;*/
    QByteArray br = message.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(br);
    if(doc["value"].isObject() && doc["value"][propId].isBool())
    {
        return doc["value"][propId].toBool();
    }
    return "";
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
