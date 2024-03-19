#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QTimer>
#include <limits>

#include <QList>
#include <functional>
#include "visclient.h"
#include "QtVisSocket.h"

QT_USE_NAMESPACE

const unsigned long visClientTimeout = 1000;

const int not_defined_value = std::numeric_limits<int>::max();

typedef std::function<void (VisClient * visClient, QVariant value)> set_func_type;

struct PropertyMapper {
    QString propName;
    set_func_type set;
};

static const QList<PropertyMapper> requiredProperties ({
    {"Signal.Vehicle.Speed", [](VisClient * visClient, QVariant value ){visClient->setSpeedValue(value);}},
    {"Signal.Drivetrain.Transmission.Gear", [](VisClient * visClient, QVariant value ){visClient->setGearValue(value);}},
    {"Signal.Drivetrain.InternaCombustionEngine.Engine.Speed", [](VisClient * visClient, QVariant value ){visClient->setRpmValue(value);}},
    {"Signal.Drivetrain.BatteryManagement.BatteryCapacity", [](VisClient * visClient, QVariant value ){visClient->setBatteryValue(value);}},
    {"Signal.Traffic.Turn.Direction", [](VisClient * visClient, QVariant value ){visClient->setTurnValue(value);}},
});

VisClient::VisClient(QObject *parent):
    QObject(parent),
    battery(100),
    turn(-1),
    speed(0),
    rpm(0),
    gear(0),
    isConnected(false),
    mWebSocket(new QtVisSocket),
    mState(SubscrState::StateInit)
{
    connect(mWebSocket.data(), &VisWebSocket::connected, this, &VisClient::onConnected);
    connect(mWebSocket.data(), &VisWebSocket::disconnected, this, &VisClient::onDisconnected);
    connect(mWebSocket.data(), &VisWebSocket::textMessageReceived, this, &VisClient::onTextMessageReceived);
}
VisClient::VisClient(QSharedPointer<VisWebSocket> socket):
    QObject(nullptr),
    battery(100),
    turn(-1),
    speed(0),
    rpm(0),
    gear(0),
    isConnected(false),
    mWebSocket(socket),
    mState(SubscrState::StateInit)
{
    connect(mWebSocket.data(), &VisWebSocket::connected, this, &VisClient::onConnected);
    connect(mWebSocket.data(), &VisWebSocket::disconnected, this, &VisClient::onDisconnected);
    connect(mWebSocket.data(), &VisWebSocket::textMessageReceived, this, &VisClient::onTextMessageReceived);
}
VisClient::~VisClient()
{
    mWebSocket->close();
}

void VisClient::connectTo()
{
    qDebug() << "Connect to:" << mUrl;

    mWebSocket->open(QUrl(mUrl));
}

void VisClient::disconnect()
{
    qDebug() << "Disconnect";

    mWebSocket->close();
}

void VisClient::sendMessage(const QString &message)
{
    qDebug() << "Send message:" << message;

    mWebSocket->sendTextMessage(message);
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

void VisClient::onTextMessageReceived(const QString &message)
{
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
              for(auto &prop: requiredProperties)
              {
                  auto v = getQValue(prop.propName, message);
                  if(v.isValid())
                  {
                      prop.set(this, v);
                  }
              };
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

int VisClient::turnValue()const
{
    return turn;
}

void VisClient::setTurnValue(QVariant input)
{
    if(!input.canConvert<QString>())
        return; // skip value

    static const QString values[] = {"right", "left", "end"};
    auto value = input.toString();
    int turn = -1;
    const QString *p= &values[0];
    QString tmp {input.toString()};
    do
    {
        if(*p == tmp)
        {
            turn = p - values + 1;
            break;
        }
        ++p;
    }
    while((*p != "end"));

    if(this->turn != turn && turn != -1)
    {
        this->turn = turn;
        emit turnValueChanged();
    }
}

QVariant VisClient::getQValue(const QString & propId, const QString & message)const
{
    QString res;
    QByteArray br = message.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(br);
    QJsonObject obj = doc.object();
    QJsonArray arr = obj.value("value").toArray();
    foreach(const QJsonValue &v, arr){
        if(v.toObject().contains(propId)) {
           return v.toObject().value(propId);
       }
    }
    return QVariant{};
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
void VisClient::setSpeedValue(QVariant input)
{
    if(!input.canConvert<int>())
        return; // skip value

    auto speed {input.toInt()/1000};
    if(this->speed == speed)
        return;
    this->speed = speed;
    emit speedValueChanged();
}
int VisClient::rpmValue()const
{
    return rpm;
}
void VisClient::setRpmValue(QVariant input)
{
    if(!input.canConvert<int>())
        return; // skip value

    auto rpm {input.toInt()};

    if(this->rpm == rpm)
        return;
    this->rpm = rpm;
    emit rpmValueChanged();
}
int VisClient::gearValue()const
{
    return gear;
}
void VisClient::setGearValue(QVariant input)
{
    if(!input.canConvert<int>())
        return; // skip value

    auto tmp {input.toInt()};

    GearPosition gear = GearPosition::GUNDEFINED;
    switch(tmp)
    {
    case 0:
    gear = GearPosition::PARK;
    break;
    case 2:
    gear = GearPosition::NEUTRAL;
    break;
    case 3:
    gear = GearPosition::DRIVE;
    break;
    case -1:
    gear = GearPosition::REVERSE;
    break;
    }

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

void VisClient::setBatteryValue(QVariant input)
{
    if(!input.canConvert<int>())
        return; // skip value

    auto tmp {input.toInt()};

    if(this->battery == tmp)
        return;

    this->battery = tmp;
    emit batteryValueChanged();
}

int VisClient::batteryValue()const
{
    return battery;
}
