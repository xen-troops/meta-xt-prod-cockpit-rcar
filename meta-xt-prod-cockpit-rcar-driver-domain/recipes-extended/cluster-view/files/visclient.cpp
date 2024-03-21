#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QTimer>
#include <limits>
#include <QDebug>
#include <QList>
#include <functional>
#include "visclient.h"

#ifndef CLUSTER_UNIT_TEST
#include "QtVisSocket.h"
#endif

QT_USE_NAMESPACE

#ifndef CLUSTER_UNIT_TEST
VisClient::VisClient(QObject *parent):
    QObject(parent),
    isConnected(false),
    mWebSocket(new QtVisSocket)
{
    init_signals();
}
#endif
VisClient::VisClient(QSharedPointer<VisWebSocket> socket):
    QObject(nullptr),
    isConnected(false),
    mWebSocket(socket)
{
    init_signals();
}

VisClient::~VisClient()
{
    mWebSocket->close();
}

void VisClient::init_signals()
{
    connect(mWebSocket.data(), &VisWebSocket::connected, this, &VisClient::onConnected);
    connect(mWebSocket.data(), &VisWebSocket::disconnected, this, &VisClient::onDisconnected);
    connect(mWebSocket.data(), &VisWebSocket::textMessageReceived, this, &VisClient::onTextMessageReceived);

    connect(this, &VisClient::messageReceived, &consumerDispatcher, &ConsumerDispatcher::onMessageReceived);

    connect(&consumerDispatcher, &ConsumerDispatcher::turnValueChanged, this, &VisClient::turnValueChanged);
    connect(&consumerDispatcher, &ConsumerDispatcher::batteryValueChanged, this, &VisClient::batteryValueChanged);
    connect(&consumerDispatcher, &ConsumerDispatcher::speedValueChanged, this, &VisClient::speedValueChanged);
    connect(&consumerDispatcher, &ConsumerDispatcher::rpmValueChanged, this, &VisClient::rpmValueChanged);
    connect(&consumerDispatcher, &ConsumerDispatcher::gearValueChanged, this, &VisClient::gearValueChanged);
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
    setConnectedValue(true);
}

void VisClient::onDisconnected()
{
    Q_EMIT VisClient::disconnected();
    setConnectedValue(false);
}

void VisClient::onTextMessageReceived(const QString &message)
{
    qDebug() << "message: " << message;
    messageReceived(message);
}

int VisClient::turnValue()const
{
    return consumerDispatcher.getValue<TurnConsumer>().toInt();
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
    return consumerDispatcher.getValue<SpeedConsumer>().toInt();
}

int VisClient::rpmValue()const
{
    return consumerDispatcher.getValue<RpmConsumer>().toInt();
}

int VisClient::gearValue()const
{
    return consumerDispatcher.getValue<GearConsumer>().toInt();
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

int VisClient::batteryValue()const
{
    return consumerDispatcher.getValue<BatteryConsumer>().toInt();
}
