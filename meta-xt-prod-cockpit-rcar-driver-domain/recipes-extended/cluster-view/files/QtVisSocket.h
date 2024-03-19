#ifndef QTVISSOCKET_H
#define QTVISSOCKET_H


#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QUuid>
#include <QVariant>

#include "VisSocket.h"
#include "QtVisSocket.h"

class QtVisSocket : public VisWebSocket
{
public:
    QtVisSocket();
    ~QtVisSocket();

private Q_SLOTS:
    void onError(QAbstractSocket::SocketError error);
    void onSslErrors(const QList<QSslError> &errors);

protected:
    void onOpen(const QUrl &url) override;
    void onClose() override;
    void onSendTextMessage(const QString &message) override;

private:
    QWebSocket mWebSocket;
};

#endif // QTVISSOCKET_H
