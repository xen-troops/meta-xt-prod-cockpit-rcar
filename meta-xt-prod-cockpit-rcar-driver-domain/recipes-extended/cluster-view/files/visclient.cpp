#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QTimer>
#include <limits>

#include "visclient.h"

QT_USE_NAMESPACE

const unsigned long visClientTimeout = 1000;

const int not_defined_value = std::numeric_limits<int>::max();

VisClient::VisClient(QObject *parent):
    QObject(parent),
    speed(0),
    rpm(0),
    gear(0),
    isConnected(false),
    mState(SubscrState::StateInit)
{
    connect(&mWebSocket,
    QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this,
            &VisClient::onError);
    connect(&mWebSocket, &QWebSocket::sslErrors, this, &VisClient::onSslErrors);
    connect(&mWebSocket, &QWebSocket::connected, this, &VisClient::onConnected);
    connect(&mWebSocket, &QWebSocket::disconnected, this, &VisClient::onDisconnected);
    connect(&mWebSocket, &QWebSocket::textMessageReceived, this, &VisClient::onTextMessageReceived);
}
VisClient::~VisClient()
{
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
/*
bool VisClient::isConnected()const
{
    return (mWebSocket.state() == QAbstractSocket::ConnectedState);
}*/

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
    setConnectedValue(true);
}

void VisClient::onDisconnected()
{
    Q_EMIT VisClient::disconnected();
    mState = SubscrState::StateInit;
    setConnectedValue(false);
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

    if(connectedValue())
    {
        disconnect();
    }

    Q_EMIT VisClient::error(mWebSocket.errorString());
}

void VisClient::onTextMessageReceived(const QString &message)
{
    qDebug() << "Receive message:" << message;

    QFile file("/var/vis-response-3.txt");

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
             auto value = getSpeed(message);
             qDebug() << " getSpeed " << value;

             if(value != not_defined_value)
             {
                setSpeedValue(value);
             }
             else
             {
                qDebug() << "No speed value in the message";
             }

             value = getGearSelect(message);
             qDebug() << " getGear " << value;
             if(value != GearPosition::GUNDEFINED)
             {
                setGearValue((int)value);
             }
             else
             {
                qDebug() << "No Gear value in the message";
             }
             value = getRpm(message);
             qDebug() << " getRpm " << value;
             if(value != not_defined_value)
             {
                 setRpmValue(value);
             }
             else
             {
                qDebug() << "No RPM value in the message";
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

VisClient::GearPosition VisClient::getGearSelect(const QString & message)const
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
    case -1:
    res = GearPosition::REVERSE;
    break;
    }
    return res;
}

int VisClient::getRpm(const QString & message)const
{
    return getValue("Signal.Drivetrain.InternalCombustionEngine.Engine.Speed", message);
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

int VisClient::speedValue()const
{
    return speed;
}
void VisClient::setSpeedValue(int speed)
{
    if(this->speed == speed)
        return;
    this->speed = speed;
    emit speedValueChanged();
}
int VisClient::rpmValue()const
{
    return rpm;
}
void VisClient::setRpmValue(int rpm)
{
    if(this->rpm == rpm)
        return;
    this->rpm = rpm;
    emit rpmValueChanged();
}
int VisClient::gearValue()const
{
    return gear;
}
void VisClient::setGearValue(int gear)
{
    qDebug() << "Gear position " << gear;
    if(this->gear == gear)
        return;
    this->gear = gear;
    emit gearValueChanged();
}
QString VisClient::urlValue()const
{
    return mUrl;
}
void VisClient::setUrlValue(QString url)
{
    qDebug() << "NEW URL " << url;
    if(this->mUrl == url || url.isEmpty())
        return;
    
    this->mUrl = url;
    emit urlValueChanged();

    if(connectedValue()){
        disconnect();
    }
    connectTo();
}
bool VisClient::connectedValue()const
{
    return isConnected;
}
void VisClient::setConnectedValue(bool connected)
{
    if(this->isConnected == connected)
        return;
    this->isConnected = connected;
    emit connectedValueChanged();
}
