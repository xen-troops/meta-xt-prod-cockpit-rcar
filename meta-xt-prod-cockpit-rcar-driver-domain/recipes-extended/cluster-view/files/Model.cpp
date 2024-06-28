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
#include "Model.h"

#ifndef CLUSTER_UNIT_TEST
#include "QtVisSocket.h"
#endif

QT_USE_NAMESPACE

#ifndef CLUSTER_UNIT_TEST
Model::Model(QObject *parent):
    QObject(parent),
    isConnected(false),
    mMode(1),
    mFirstStart(true),
    mWebSocket(new QtVisSocket)
{
    init_signals();
}
#endif
Model::Model(QSharedPointer<VisWebSocket> socket):
    QObject(nullptr),
    isConnected(false),
    mMode(1),
    mFirstStart(true),
    mWebSocket(socket)
{
    init_signals();
}

Model::~Model()
{
    mWebSocket->close();
}

void Model::init_signals()
{
    connect(mWebSocket.data(), &VisWebSocket::connected, this, &Model::onConnected);
    connect(mWebSocket.data(), &VisWebSocket::disconnected, this, &Model::onDisconnected);
    connect(mWebSocket.data(), &VisWebSocket::textMessageReceived, this, &Model::onTextMessageReceived);

    connect(this, &Model::messageReceived, &consumerBroker, &ConsumerBroker::onMessageReceived);

    connect(&consumerBroker, &ConsumerBroker::turnValueChanged, this, &Model::turnValueChanged);
    connect(&consumerBroker, &ConsumerBroker::batteryValueChanged, this, &Model::batteryValueChanged);
    connect(&consumerBroker, &ConsumerBroker::speedValueChanged, this, &Model::speedValueChanged);
    connect(&consumerBroker, &ConsumerBroker::rpmValueChanged, this, &Model::rpmValueChanged);
    connect(&consumerBroker, &ConsumerBroker::gearValueChanged, this, &Model::gearValueChanged);
}
void Model::connectTo()
{
    qDebug() << "Connect to:" << mUrl;

    mWebSocket->open(QUrl(mUrl));
}

void Model::disconnect()
{
    qDebug() << "Disconnect";

    mWebSocket->close();
}

void Model::sendMessage(const QString &message)
{
    qDebug() << "Send message:" << message;

    mWebSocket->sendTextMessage(message);
}

void Model::onConnected()
{
    setConnectedValue(true);
}

void Model::onDisconnected()
{
    Q_EMIT Model::disconnected();
    setConnectedValue(false);
}

void Model::onTextMessageReceived(const QString &message)
{
    qDebug() << "message: " << message;
    messageReceived(message);
}

int Model::turnValue()const
{
    return consumerBroker.getValue<TurnConsumer>().toInt();
}

QString Model::getSubscriptionId(const QString &message)const
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

int Model::speedValue()const
{
    return consumerBroker.getValue<SpeedConsumer>().toInt();
}

int Model::rpmValue()const
{
    return consumerBroker.getValue<RpmConsumer>().toInt();
}

int Model::gearValue()const
{
    return consumerBroker.getValue<GearConsumer>().toInt();
}

QString Model::urlValue()const
{
    return mUrl;
}

void Model::setUrlValue(QString url)
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

bool Model::connectedValue()const
{
    return isConnected;
}

void Model::setConnectedValue(bool connected)
{
    if(this->isConnected == connected)
        return;
    this->isConnected = connected;
    emit connectedValueChanged();
}

int Model::batteryValue()const
{
    return consumerBroker.getValue<BatteryConsumer>().toInt();
}

int Model::modeValue()const
{
    return mMode;
}

void Model::setModeValue(bool mode)
{
    if(mMode == mode)
    {
        return;
    }

    mMode = mode;

    emit modeValueChanged();
}

bool Model::isFirstStart() const
{
    qDebug() << "Get firstStart " << mFirstStart;
    return mFirstStart;
}

void Model::setFirstStart(bool started)
{
    if(started != mFirstStart)
    {
        mFirstStart = started;
        firstStartChanged();
        if(mFirstStart)
        {
            QFile file("/tmp/clusterview.started");
            file.open(QIODevice::ReadWrite | QIODevice::Text);
            QTextStream stream(&file);
            stream << started << endl;
            file.close();
        }
    }
}
