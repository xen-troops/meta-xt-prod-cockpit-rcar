#ifndef VISCLIENT_H
#define VISCLIENT_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QUuid>
#include <QVariant>
#include <QSharedPointer>
#include "VisSocket.h"

class VisClient: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speedValue READ speedValue WRITE setSpeedValue NOTIFY speedValueChanged)
    Q_PROPERTY(int rpmValue READ rpmValue WRITE setRpmValue NOTIFY rpmValueChanged)
    Q_PROPERTY(int gearValue READ gearValue WRITE setGearValue NOTIFY gearValueChanged)
    Q_PROPERTY(QString urlValue READ urlValue WRITE setUrlValue NOTIFY urlValueChanged)
    Q_PROPERTY(bool connectedValue READ connectedValue WRITE setConnectedValue NOTIFY connectedValueChanged)
    Q_PROPERTY(int batteryValue READ batteryValue WRITE setBatteryValue NOTIFY batteryValueChanged)
    Q_PROPERTY(int turnValue READ turnValue WRITE setTurnValue NOTIFY turnValueChanged)

public:

    enum SubscrState {
        StateInit = 0,
        StateGetValues = 1,
        StateSubscribe = 2,
        StateReady = 3
    };

    explicit VisClient(QObject *parent = nullptr);
    explicit VisClient(QSharedPointer<VisWebSocket> socket);
    ~VisClient();

    int speedValue()const;
    void setSpeedValue(QVariant input);

    int rpmValue()const;
    void setRpmValue(QVariant input);

    QString urlValue()const;
    void setUrlValue(QString input);

    int gearValue()const;
    void setGearValue(QVariant input);

    int batteryValue()const;
    void setBatteryValue(QVariant input);

    int turnValue()const;
    void setTurnValue(QVariant input);

    bool connectedValue()const;
    void setConnectedValue(bool connected);

    Q_INVOKABLE void connectTo();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void sendMessage(const QString &message);

Q_SIGNALS:
    void connected();
    void disconnected();
    void error(const QString &message);
    void messageReceived(const QString &message);

private Q_SLOTS:

    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString &message);

signals:
    void turnValueChanged();
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
    QVariant getQValue(const QString & propId, const QString & message)const;

private:
    int battery;
    int turn;
    int speed;
    int rpm;
    int gear;
    bool isConnected;
    QString mUrl;
    QSharedPointer<VisWebSocket> mWebSocket;
    QUuid mID;
    SubscrState mState;
    QString mSubscriptionId;
};

#endif // VISCLIENT_H
