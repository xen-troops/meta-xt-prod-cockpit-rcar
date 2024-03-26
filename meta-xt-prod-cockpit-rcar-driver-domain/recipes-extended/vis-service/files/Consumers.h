#ifndef MSGPRODUCER_H
#define MSGPRODUCER_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <tuple>

class ConsumerDispatcher;

class BaseConsumer: public QObject
{
    Q_OBJECT

public:
    virtual void init(class ConsumerDispatcher& );
public Q_SLOTS:
    void onMessageReceived(const QString &message);
    virtual void off() = 0;
    virtual void on()= 0;
public:
    static QVariant getQValue(const QString &msg, const QString& prop);
protected:
    virtual void onMessage(const QString &message)= 0;
    void send(quint16 cmd, quint64 value);
};

class SpeedConsumer: public BaseConsumer
{
public:
    void onMessage(const QString &message) override;
    void off() override;
    void on() override;
};

class GearConsumer: public BaseConsumer
{
public:
    void onMessage(const QString &message) override;
    void off() override;
    void on() override;
};

class RpmConsumer: public BaseConsumer
{
public:
    void onMessage(const QString &message) override;
    void off() override;
    void on() override;
};

class TurnConsumer: public BaseConsumer
{
public:
    void onMessage(const QString &message) override;
    void off() override;
    void on() override;
};

class DoorConsumer: public BaseConsumer
{
public:
    void onMessage(const QString &message) override;
    void off() override;
    void on() override;
};

class TrunkConsumer: public BaseConsumer
{
public:
    void onMessage(const QString &message) override;
    void off() override;
    void on() override;
};

class BeltConsumer: public BaseConsumer
{
public:
    void onMessage(const QString &message) override;
    void off() override;
    void on() override;
};

class LightsConsumer: public BaseConsumer
{
public:
    void onMessage(const QString &message) override;
    void off() override;
    void on() override;
};

class TireConsumer: public BaseConsumer
{
public:
    void onMessage(const QString &message) override;
    void off() override;
    void on() override;
};

class ConsumerDispatcher: public QObject
{
    Q_OBJECT
public:
    ConsumerDispatcher();
public Q_SLOTS:
    void onMessageReceived(const QString &message);

Q_SIGNALS:
    void messageReceived(const QString &message);
    void on();
    void off();

private:
    std::tuple<SpeedConsumer,
            RpmConsumer,
            GearConsumer,
            TurnConsumer,
            DoorConsumer,
            TrunkConsumer,
            BeltConsumer,
            LightsConsumer,
            TireConsumer> consumers;
};

#endif // MSGPRODUCER_H
