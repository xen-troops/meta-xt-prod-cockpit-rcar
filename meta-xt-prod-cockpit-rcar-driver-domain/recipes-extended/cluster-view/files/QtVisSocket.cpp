
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


QtVisSocket::QtVisSocket()
{
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
