#ifndef VISCLIENT_H
#define VISCLIENT_H

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
#include <QVariant>
#include <QSharedPointer>
#include "VisSocket.h"
#include "Consumers.h"

class VisClient: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speedValue READ speedValue NOTIFY speedValueChanged)
    Q_PROPERTY(int rpmValue READ rpmValue NOTIFY rpmValueChanged)
    Q_PROPERTY(int gearValue READ gearValue NOTIFY gearValueChanged)
    Q_PROPERTY(QString urlValue READ urlValue WRITE setUrlValue NOTIFY urlValueChanged)
    Q_PROPERTY(bool connectedValue READ connectedValue NOTIFY connectedValueChanged)
    Q_PROPERTY(int batteryValue READ batteryValue NOTIFY batteryValueChanged)
    Q_PROPERTY(int turnValue READ turnValue NOTIFY turnValueChanged)

public:
#ifndef CLUSTER_UNIT_TEST
    explicit VisClient(QObject *parent = nullptr);
#endif
    explicit VisClient(QSharedPointer<VisWebSocket> socket);
    ~VisClient();

    int speedValue()const;
    int rpmValue()const;
    QString urlValue()const;
    void setUrlValue(QString input);
    int gearValue()const;
    int batteryValue()const;
    int turnValue()const;

    bool connectedValue()const;
    void setConnectedValue(bool connected);

    Q_INVOKABLE void connectTo();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void sendMessage(const QString &message);

protected:
    void init_signals();

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
    QString getSubscriptionId(const QString &message)const;

private:
    bool isConnected;
    QString mUrl;
    QSharedPointer<VisWebSocket> mWebSocket;
    ConsumerDispatcher consumerDispatcher;
};

#endif // VISCLIENT_H
