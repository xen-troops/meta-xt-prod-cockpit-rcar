
#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QUuid>
#include <QVariant>

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QTimer>
#include <limits>
#include <QList>

#include "QtVisSocket.h"


QtVisSocket::QtVisSocket():
        mState(SubscrState::StateInit)
{
    connect(&mWebSocket, &QWebSocket::sslErrors, this, &QtVisSocket::onSslErrors);
    connect(&mWebSocket, &QWebSocket::connected, this, &QtVisSocket::onConnected);
    connect(&mWebSocket, &QWebSocket::disconnected, this, &QtVisSocket::onDisconnected);
    connect(&mWebSocket, &QWebSocket::textMessageReceived, this, &QtVisSocket::onTextMessageReceived);
}

QtVisSocket::~QtVisSocket()
{
    mWebSocket.close();
}

void QtVisSocket::onOpen(const QUrl &url)
{
    mWebSocket.open(QUrl(url));
}

void QtVisSocket::onClose()
{
    mWebSocket.close();
}

void QtVisSocket::onSendTextMessage(const QString &message)
{
    mWebSocket.sendTextMessage(message);
}

void QtVisSocket::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)

    qDebug() << "Error:" << mWebSocket.errorString();

    close();
}

void QtVisSocket::onSslErrors(const QList<QSslError> &errors)
{
    Q_FOREACH (QSslError error, errors) {
        if (error.error() == QSslError::SelfSignedCertificate
            || error.error() == QSslError::SelfSignedCertificateInChain) {
            mWebSocket.ignoreSslErrors();
            return;
        }
    };
}

void QtVisSocket::onConnected()
{
    auto sId = mID.createUuid().toString().replace("{","").replace("}","");
    qDebug() << "onConnected, state SubscrState::StateGetValues";
    sendTextMessage("{\"action\": \"get\", \"path\": \"*\", \"requestId\": \"" + sId + "\"}");
    mState = SubscrState::StateGetValues;
    emit connected();
}

void QtVisSocket::onDisconnected()
{
    mState = SubscrState::StateInit;
    emit disconnected();
}

void QtVisSocket::onTextMessage(const QString &message)
{
    qDebug() << "mState: " << mState;

    switch(mState)
    {
       case SubscrState::StateGetValues:
       {
          auto sId = mID.createUuid().toString().replace("{","").replace("}","");
          mState = SubscrState::StateSubscribe;
          qDebug() << "onConnected, send subscription";
          sendTextMessage("{\"action\": \"subscribe\", \"path\": \"*\", \"requestId\": \"" + sId + "\"}");
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
              emit textMessageReceived(message);
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

QString QtVisSocket::getSubscriptionId(const QString &message)const
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
