#ifndef VIS_CLIENT_H
#define VIS_CLIENT_H

#undef QT_NO_SSL
#include <linux/rpmsg.h>
#include <fcntl.h>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QUuid>
#include <QVariant>

#include "Consumers.h"

enum SubscrState {
	StateInit = 0,
	StateGetValues = 1,
	StateSubscribe = 2,
	StateReady = 3
};

class VisClient : public QObject
{
    Q_OBJECT
public:
    VisClient(QObject *parent, const QString &url);
    virtual ~VisClient();
    QVariant getQValue(const QString &message);
    static QString getSubscriptionId(const QString &message);

    Q_INVOKABLE void connectTo();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void sendMessage(const QString &message);
    Q_INVOKABLE bool IsConnected()const;

Q_SIGNALS:
    void connected();
    void disconnected();
    void error(const QString &message);
    void messageReceived(const QString &message);

private Q_SLOTS:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    void onSslErrors(const QList<QSslError> &errors);
    void onTextMessageReceived(const QString &message);

private:
    QString mUrl;
    QWebSocket mWebSocket;
    QUuid mID;
    SubscrState mState;
    QString mSubscriptionId;
    ConsumerBroker broker;
};    

#endif // VIS_CLIENT_H
