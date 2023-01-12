#ifndef VIS_CLIENT_H
#define VIS_CLIENT_H

#undef QT_NO_SSL
#include <linux/rpmsg.h>
#include <fcntl.h>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QUuid>

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
    VisClient(QObject *parent, const QString &url, const QString& rpmsg);
    virtual ~VisClient();

    static int getBool(const QString & propId, const QString & message);
    static int getTurnDirection(const QString & propId, const QString & message);
    static int getValue(const QString & propId, const QString & message);
    static int getTireStatus(const QString & propId, const QString & message);
    static int getBeltStatus(const QString & propId, const QString & message);

    static QString getStringValue(const QString & propId, const QString & message);
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
    int mFdept;
    QUuid mID;
    SubscrState mState;
    QString mSubscriptionId;
};    

#endif // VIS_CLIENT_H
