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
    enum GearPosition{
    	PARK        = 0,
    	NEUTRAL     = 2,
    	DRIVE       = 3,
    	REVERSE     = 4,
    	GUNDEFINED  = 5,
    };
    QString getSubscriptionId(const QString &message)const;
    int getSpeed(const QString &message)const;
    GearPosition getGearSelect(const QString &message)const;
    int getRpm(const QString & message)const;
    int getTurnDirection(const QString & message)const;
    int getValue(const QString & propId, const QString & message)const;
    QString getStringValue(const QString & propId, const QString & message)const;
private:
    QString mUrl;
    QWebSocket mWebSocket;
    int mFd;
    int mFdept;
    QUuid mID;
    struct rpmsg_endpoint_info mEptInfo;
    SubscrState mState;
    QString mSubscriptionId;
};    

#endif // VIS_CLIENT_H
