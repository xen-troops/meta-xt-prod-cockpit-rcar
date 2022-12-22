#ifndef VISCLIENT_H
#define VISCLIENT_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QUuid>

class VisClient: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speedValue READ speedValue WRITE setSpeedValue NOTIFY speedValueChanged)
    Q_PROPERTY(int rpmValue READ rpmValue WRITE setRpmValue NOTIFY rpmValueChanged)
    Q_PROPERTY(int gearValue READ gearValue WRITE setGearValue NOTIFY gearValueChanged)
    Q_PROPERTY(QString urlValue READ urlValue WRITE setUrlValue NOTIFY urlValueChanged)
    Q_PROPERTY(bool connectedValue READ connectedValue WRITE setConnectedValue NOTIFY connectedValueChanged)
    Q_PROPERTY(int batteryValue READ batteryValue WRITE setBatteryValue NOTIFY batteryValueChanged)

public:

    enum SubscrState {
        StateInit = 0,
        StateGetValues = 1,
        StateSubscribe = 2,
        StateReady = 3
    };

    explicit VisClient(QObject *parent = nullptr);
    ~VisClient();

    int speedValue()const;
    void setSpeedValue(int speed);

    int rpmValue()const;
    void setRpmValue(int rpm);

    QString urlValue()const;
    void setUrlValue(QString url);

    int gearValue()const;
    void setGearValue(int rpm);

    int batteryValue()const;
    void setBatteryValue(int battery);

    bool connectedValue()const;
    void setConnectedValue(bool connected);

    Q_INVOKABLE void connectTo();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void sendMessage(const QString &message);
    //Q_INVOKABLE bool IsConnected()const;

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

signals:
    void batteryValueChanged();
    void speedValueChanged();
    void rpmValueChanged();
    void gearValueChanged();
    void urlValueChanged();
    void connectedValueChanged();

private: // methods
    enum GearPosition{
        PARK    	= 0,
        NEUTRAL 	= 2,
        DRIVE   	= 3,
        REVERSE 	= 5,
        GUNDEFINED 	= 10,
    };
    QString getSubscriptionId(const QString &message)const;
    int getSpeed(const QString &message)const;
    GearPosition getGearSelect(const QString &message)const;
    int getRpm(const QString & message)const;
    int getValue(const QString & propId, const QString & message)const;
    QString getStringValue(const QString & propId, const QString & message)const;
    int getBattery(const QString & message)const;

private:
    int battery;
    int speed;
    int rpm;
    int gear;
    bool isConnected;
    QString mUrl;
    QWebSocket mWebSocket;
    QUuid mID;
    SubscrState mState;
    QString mSubscriptionId;
};

#endif // VISCLIENT_H
