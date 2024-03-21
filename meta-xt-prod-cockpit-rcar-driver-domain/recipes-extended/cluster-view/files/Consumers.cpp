#include <linux/rpmsg.h>
#include <QSharedPointer>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

#include "Consumers.h"

void BaseConsumer::onMessageReceived(const QString &message)
{
    onMessage(message);
}

QVariant BaseConsumer::getQValue(const QString &msg, const QString& prop, const QVariant &defValue)
{
    QString res;
    QByteArray br = msg.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(br);
    QJsonObject obj = doc.object();
    QJsonArray arr = obj.value("value").toArray();
    foreach(const QJsonValue &v, arr){
        if(v.toObject().contains(prop)) {
           return v.toObject().value(prop);
       }
    }
    return defValue;
}

void SpeedConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Vehicle.Speed"};

    auto value = getQValue(message, propName, getValue());
    if(value.isValid() && getValue() != value)
    {
        setValue(value.toInt()/1000);
        emit speedValueChanged();
    }
}

void GearConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Drivetrain.Transmission.Gear"};

    auto value = getQValue(message, propName, getValue());
    if(value.isValid())
    {
        GearPosition gear = GearPosition::GUNDEFINED;
        switch(value.toInt())
        {
        case 0:
        gear = GearPosition::PARK;
        break;
        case 2:
        gear = GearPosition::NEUTRAL;
        break;
        case 3:
        gear = GearPosition::DRIVE;
        break;
        case -1:
        gear = GearPosition::REVERSE;
        break;
        }
        if(getValue() != (int)gear)
        {
            setValue((int)gear);
            emit gearValueChanged();
        }
    }
}

void RpmConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Drivetrain.InternalCombustionEngine.Engine.Speed"};

    auto value = getQValue(message, propName, getValue());
    if(value.isValid() && getValue() != value)
    {
        setValue(value);
        emit rpmValueChanged();
    }
}

void TurnConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Traffic.Turn.Direction"};
    static const QString values[] = {"right", "left", "end"};

    auto value = getQValue(message, propName, getValue());

    if(value.isValid() && value.canConvert<QString>())
    {
        int turn = -1;
        const QString *p= &values[0];
        QString tmp {value.toString()};
        do
        {
            if(*p == tmp)
            {
                turn = p - values + 1;
                break;
            }
            ++p;
        }
        while((*p != "end"));

        if(turn != -1 && getValue() != turn)
        {
            setValue(QVariant{turn});
            emit turnValueChanged();
        };
    }
}

void BatteryConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Drivetrain.BatteryManagement.BatteryCapacity"};

    auto value = getQValue(message, propName, getValue());
    if(value.isValid() && getValue() != value)
    {
        setValue(value);
        emit batteryValueChanged();
    }
}

ConsumerDispatcher::ConsumerDispatcher()
{
    connect(this, &ConsumerDispatcher::messageReceived, &std::get<SpeedConsumer>(consumers), &SpeedConsumer::onMessageReceived);
    connect(this, &ConsumerDispatcher::messageReceived, &std::get<GearConsumer>(consumers), &GearConsumer::onMessageReceived);
    connect(this, &ConsumerDispatcher::messageReceived, &std::get<RpmConsumer>(consumers), &RpmConsumer::onMessageReceived);
    connect(this, &ConsumerDispatcher::messageReceived, &std::get<TurnConsumer>(consumers), &TurnConsumer::onMessageReceived);
    connect(this, &ConsumerDispatcher::messageReceived, &std::get<BatteryConsumer>(consumers), &BatteryConsumer::onMessageReceived);

    connect(&std::get<SpeedConsumer>(consumers), &SpeedConsumer::speedValueChanged, this, &ConsumerDispatcher::speedValueChanged);
    connect(&std::get<GearConsumer>(consumers), &GearConsumer::gearValueChanged, this, &ConsumerDispatcher::gearValueChanged);
    connect(&std::get<RpmConsumer>(consumers), &RpmConsumer::rpmValueChanged, this, &ConsumerDispatcher::rpmValueChanged);
    connect(&std::get<TurnConsumer>(consumers), &TurnConsumer::turnValueChanged, this, &ConsumerDispatcher::turnValueChanged);
    connect(&std::get<BatteryConsumer>(consumers), &BatteryConsumer::batteryValueChanged, this, &ConsumerDispatcher::batteryValueChanged);
}

void ConsumerDispatcher::onMessageReceived(const QString &message)
{
    messageReceived(message);
}
