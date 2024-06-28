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


VisClient::VisClient(QObject *parent, const QString &url):QObject(parent),
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
    // initialize consumers to get the messages
    connect(this, &VisClient::messageReceived, &broker, &ConsumerBroker::onMessageReceived);
    // hide the icons at the dispaly
    broker.off();

    qDebug() << "Create VIS client - send 0 to reset";
}

VisClient::~VisClient()
{
    qDebug() << "Delete VIS client";
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
                messageReceived(message);
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
