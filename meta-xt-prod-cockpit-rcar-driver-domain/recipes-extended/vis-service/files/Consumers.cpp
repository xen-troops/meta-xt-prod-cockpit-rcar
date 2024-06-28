
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
#include <QSharedPointer>

#ifndef _TEST_
#include <linux/r_taurus_cluster_protocol.h>
#else
#define CLUSTER_SPEED                   0x1
#define CLUSTER_GEAR                    0x2
#define CLUSTER_RPM                     0x3
#define CLUSTER_TURN                    0x4
#define CLUSTER_DOOR_OPEN               0x5
#define CLUSTER_FOG_LIGHTS_BACK         0x6
#define CLUSTER_FOG_LIGHTS_FRONT        0x7
#define CLUSTER_HIGH_BEAMS_LIGHT        0x8
#define CLUSTER_HIGH_ENGINE_TEMPERATURE 0x9
#define CLUSTER_LOW_BATTERY             0xA
#define CLUSTER_LOW_BEAMS_LIGHTS        0xB
#define CLUSTER_LOW_FUEL                0xC
#define CLUSTER_LOW_OIL                 0xD
#define CLUSTER_LOW_TIRE_PRESSURE       0xE
#define CLUSTER_SEAT_BELT               0xF
#define CLUSTER_SIDE_LIGHTS             0x10
#define CLUSTER_BATTERY_ISSUE           0x11
#define CLUSTER_AUTO_LIGHTING_ON        0x12
#define CLUSTER_ACTIVE                  0xFF

struct taurus_cluster_data {
uint64_t   value;
uint16_t   ioctl_cmd;
};

#endif
#include <Consumers.h>

class TargetDevice
{
private:
    int device;
public:
    TargetDevice()
    {
        device = open("/dev/cluster-taurus", O_WRONLY);
        if(device < 0){
            throw std::invalid_argument("No device /dev/cluster-taurus");
        }
    }
    ~TargetDevice()
    {
        close(device);
    }
    void send(const taurus_cluster_data& data)
    {
        ioctl(device, data.ioctl_cmd, data.value);
    }
};

void BaseConsumer::onMessageReceived(const QString &message)
{
    onMessage(message);
}

void BaseConsumer::send(quint16 cmd, quint64 value)
{
    static TargetDevice tDevice;
    tDevice.send({value, cmd});
}

QVariant BaseConsumer::getQValue(const QString &msg, const QString& prop)
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
    return QVariant{};
}

void BaseConsumer::init(class ConsumerBroker& broker)
{
    connect(&broker, &ConsumerBroker::messageReceived, this, &BaseConsumer::onMessageReceived);
    connect(&broker, &ConsumerBroker::on, this, &BaseConsumer::on);
    connect(&broker, &ConsumerBroker::off, this, &BaseConsumer::off);
}

void SpeedConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Vehicle.Speed"};

    auto value = getQValue(message, propName);
    if(value.isValid())
    {
        send(CLUSTER_SPEED, value.toInt());
    }
}

void SpeedConsumer::off()
{
    send(CLUSTER_SPEED, 0);
}

void SpeedConsumer::on()
{
    send(CLUSTER_SPEED, 10);
}

void GearConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Drivetrain.Transmission.Gear"};

    auto value = getQValue(message, propName);
    if(value.isValid())
    {
        send(CLUSTER_GEAR, value.toInt());
    }
}

void GearConsumer::off()
{
    send(CLUSTER_GEAR, 2);
}

void GearConsumer::on()
{
    send(CLUSTER_GEAR, 3);
}

void RpmConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Drivetrain.InternalCombustionEngine.Engine.Speed"};

    auto value = getQValue(message, propName);
    if(value.isValid())
    {
        send(CLUSTER_RPM, value.toInt());
    }
}

void RpmConsumer::off()
{
    send(CLUSTER_RPM, 0);
}

void RpmConsumer::on()
{
    send(CLUSTER_RPM, 1000);
}

void TurnConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Traffic.Turn.Direction"};

    auto value = getQValue(message, propName);
    if(value.isValid())
    {
        send(CLUSTER_TURN, value.toInt());
    }
}

void TurnConsumer::off()
{
    send(CLUSTER_TURN, 0);
}

void TurnConsumer::on()
{
    send(CLUSTER_TURN, 1); // right
}

void DoorConsumer::onMessage(const QString &message)
{
    static const QVector<QString> props {
            "Signal.Cabin.Door.Row1.Left.IsOpen",
            "Signal.Cabin.Door.Row1.Right.IsOpen",
            "Signal.Cabin.Door.Row2.Left.IsOpen",
            "Signal.Cabin.Door.Row2.Right.IsOpen"
    };
    for(auto iter = props.begin();iter != props.end(); ++iter)
    {
        auto value = getQValue(message, *iter);
        if(value.isValid())
        {
            send(CLUSTER_DOOR_OPEN, value.toInt());
            break;
        }
    }
}

void DoorConsumer::off()
{
    send(CLUSTER_DOOR_OPEN, 0);
}

void DoorConsumer::on()
{
    send(CLUSTER_DOOR_OPEN, 1);
}

void TrunkConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Body.Trunk.IsOpen"};

    auto value = getQValue(message, propName);
    if(value.isValid())
    {
        send(CLUSTER_DOOR_OPEN, value.toInt());
    }
}

void TrunkConsumer::off()
{
    send(CLUSTER_DOOR_OPEN, 0);
}

void TrunkConsumer::on()
{
    send(CLUSTER_DOOR_OPEN, 1);
}

void BeltConsumer::onMessage(const QString &message)
{
    static const QVector<QString> props {
            "Signal.Cabin.Seat.Row1.Pos1.IsBelted",
            "Signal.Cabin.Seat.Row1.Pos2.IsBelted",
            "Signal.Cabin.Seat.Row2.Pos1.IsBelted",
            "Signal.Cabin.Seat.Row2.Pos2.IsBelted"
    };
    for(auto iter = props.begin();iter != props.end(); ++iter)
    {
        auto value = getQValue(message, *iter);
        if(value.isValid())
        {
            send(CLUSTER_SEAT_BELT, value.toInt());
            break;
        }
    }
}

void BeltConsumer::off()
{
    send(CLUSTER_SEAT_BELT, 0);
}

void BeltConsumer::on()
{
    send(CLUSTER_SEAT_BELT, 1);
}

void LightsConsumer::onMessage(const QString &message)
{
    static const QString propLowBean {"Signal.Body.Lights.IsLowBeamOn"};
    static const QString propHighBean {"Signal.Body.Lights.IsHighBeamOn"};
    static const QString propFrontFog {"Signal.Body.Lights.IsFrontFogOn"};
    static const QString propRearFog {"Signal.Body.Lights.IsRearFogOn"};

    auto value = getQValue(message, propLowBean);
    if(value.isValid())
    {
        send(CLUSTER_LOW_BEAMS_LIGHTS, value.toInt());
    }
    value = getQValue(message, propHighBean);
    if(value.isValid())
    {
        send(CLUSTER_HIGH_BEAMS_LIGHT, value.toInt());
    }
    value = getQValue(message, propFrontFog);
    if(value.isValid())
    {
        send(CLUSTER_FOG_LIGHTS_FRONT, value.toInt());
    }
    value = getQValue(message, propRearFog);
    if(value.isValid())
    {
        send(CLUSTER_FOG_LIGHTS_BACK, value.toInt());
    }
}

void LightsConsumer::off()
{
    send(CLUSTER_LOW_BEAMS_LIGHTS, 0);
    send(CLUSTER_HIGH_BEAMS_LIGHT, 0);
    send(CLUSTER_FOG_LIGHTS_FRONT, 0);
    send(CLUSTER_FOG_LIGHTS_BACK, 0);
}

void LightsConsumer::on()
{
    send(CLUSTER_LOW_BEAMS_LIGHTS, 1);
    send(CLUSTER_HIGH_BEAMS_LIGHT, 1);
    send(CLUSTER_FOG_LIGHTS_FRONT, 1);
    send(CLUSTER_FOG_LIGHTS_BACK, 1);
}

void TireConsumer::onMessage(const QString &message)
{
    static const QString propName {"Signal.Chassis.Axle.Row1.Wheel.Left.Tire.Pressure"};

    auto value = getQValue(message, propName);
    if(value.isValid())
    {
        send(CLUSTER_LOW_TIRE_PRESSURE, value.toInt());
    }
}

void TireConsumer::off()
{
    send(CLUSTER_LOW_TIRE_PRESSURE, 0);
}

void TireConsumer::on()
{
    send(CLUSTER_LOW_TIRE_PRESSURE, 1);
}

ConsumerBroker::ConsumerBroker()
{
    std::get<SpeedConsumer>(consumers).init(*this);
    std::get<RpmConsumer>(consumers).init(*this);
    std::get<GearConsumer>(consumers).init(*this);
    std::get<DoorConsumer>(consumers).init(*this);
    std::get<TrunkConsumer>(consumers).init(*this);
    std::get<BeltConsumer>(consumers).init(*this);
    std::get<LightsConsumer>(consumers).init(*this);
    std::get<TireConsumer>(consumers).init(*this);
}

void ConsumerBroker::onMessageReceived(const QString &message)
{
    messageReceived(message);
}
