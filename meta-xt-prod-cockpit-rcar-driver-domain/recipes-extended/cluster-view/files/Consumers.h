#ifndef MSGPRODUCER_H
#define MSGPRODUCER_H

#include <QObject>
#include <QString>
#include <QVariant>

#include <tuple>

class BaseConsumer;
class SpeedConsumer;
class RpmConsumer;
class GearConsumer;
class BatteryConsumer;
class TurnConsumer;
class ConsumerDispatcher;


class BaseConsumer: public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void onMessageReceived(const QString &message);

    QVariant getValue()const{return mValue;};

public:
    static QVariant getQValue(const QString &msg, const QString& prop, const QVariant &defValue);

protected:
    virtual void onMessage(const QString &message)= 0;

    void setValue(QVariant value){mValue= value;}

private:
    QVariant mValue;
};

class SpeedConsumer: public BaseConsumer
{
    Q_OBJECT
public:
    void onMessage(const QString &message) override;
signals:
    void speedValueChanged();
};

class GearConsumer: public BaseConsumer
{
    Q_OBJECT
public:
    enum GearPosition{
        PARK    	= 0,
        NEUTRAL 	= 2,
        DRIVE   	= 3,
        REVERSE 	= 5,
        GUNDEFINED 	= 10,
    };
    void onMessage(const QString &message) override;
signals:
    void gearValueChanged();
};

class RpmConsumer: public BaseConsumer
{
    Q_OBJECT
public:
    void onMessage(const QString &message) override;
signals:
    void rpmValueChanged();
};

class TurnConsumer: public BaseConsumer
{
    Q_OBJECT
public:
    void onMessage(const QString &message) override;
signals:
    void turnValueChanged();
};

class BatteryConsumer: public BaseConsumer
{
    Q_OBJECT
public:
    void onMessage(const QString &message) override;
signals:
    void batteryValueChanged();
};

class ConsumerDispatcher: public QObject
{
    Q_OBJECT
public:
     ConsumerDispatcher();

     template<typename T>
     QVariant getValue()const
     {
         return std::get<T>(consumers).getValue();
     }

Q_SIGNALS:
    void turnValueChanged();
    void batteryValueChanged();
    void speedValueChanged();
    void rpmValueChanged();
    void gearValueChanged();

public Q_SLOTS:
    void onMessageReceived(const QString &message);

Q_SIGNALS:
    void messageReceived(const QString &message);

private:
    std::tuple<SpeedConsumer, RpmConsumer, GearConsumer, BatteryConsumer, TurnConsumer> consumers;
};

#endif // MSGPRODUCER_H
