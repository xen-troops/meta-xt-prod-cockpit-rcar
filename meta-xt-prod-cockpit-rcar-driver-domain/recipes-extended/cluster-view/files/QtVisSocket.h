#ifndef QTVISSOCKET_H
#define QTVISSOCKET_H


#include <QObject>
#include <QString>
#ifndef CLUSTER_UNIT_TEST
#include <qqml.h>
#endif
#include <QtCore/QObject>
#ifndef CLUSTER_UNIT_TEST
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#endif
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
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    void onSslErrors(const QList<QSslError> &errors);

protected:
    enum SubscrState {
        StateInit = 0,
        StateGetValues = 1,
        StateSubscribe = 2,
        StateReady = 3
    };
    void onOpen(const QUrl &url) override;
    void onClose() override;
    void onSendTextMessage(const QString &message) override;
    void onTextMessage(const QString &message) override;

    QString getSubscriptionId(const QString &message)const;

private:
    QWebSocket mWebSocket;
    SubscrState mState;
    QUuid mID;
    QString mSubscriptionId;
};

#endif // QTVISSOCKET_H
