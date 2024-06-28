#include <QtTest>
#include <QObject>
#include <QSharedPointer>
#include "../Model.h"
#include "../VisSocket.h"

class UnitTestSocket : public VisWebSocket
{
public:
    void receivedText(const QString & message)
    {
        emit textMessageReceived(message);
    }
protected:
    void onTextMessage(const QString&) override
    {

    }
    void onOpen(const QUrl &url) override{
        Q_UNUSED(url);
        connected();
    };
    void onClose() override{
        disconnected();
    };
    void onSendTextMessage(const QString &message) override{
        Q_UNUSED(message);
    };
};

// add necessary includes here

class cluster_view_input : public QObject
{
    Q_OBJECT

public:
    cluster_view_input();
    ~cluster_view_input();
protected:
    void resetSlotState();
private Q_SLOTS:
    void turnValueChanged();
    void batteryValueChanged();
    void speedValueChanged();
    void rpmValueChanged();
    void gearValueChanged();
    void urlValueChanged();

private slots:
    void test_set_speed();
    void test_set_gear();
    void test_set_rpm();
    void test_set_battery();
    void test_set_turn();
    void test_set_all();
    void test_slots();

private:
    bool turnChanged;
    bool batteryChanged;
    bool speedChanged;
    bool rpmChanged;
    bool gearChanged;
    bool urlChanged;
};

static const QString msg_subscr = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[] \
                                }";
static const QString msg_speed = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Vehicle.Speed\":21000}] \
                                }";
static const QString msg_gear = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Drivetrain.Transmission.Gear\":3}] \
                                }";
static const QString msg_gear_rev = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Drivetrain.Transmission.Gear\":-1}] \
                                }";
static const QString msg_gear_park = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Drivetrain.Transmission.Gear\":0}] \
                                }";
static const QString msg_gear_neutral = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Drivetrain.Transmission.Gear\":2}] \
                                }";
static const QString msg_rpm = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Drivetrain.InternalCombustionEngine.Engine.Speed\":3000}] \
                                }";
static const QString msg_battery = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Drivetrain.BatteryManagement.BatteryCapacity\":70}] \
                                }";
static const QString msg_turn_left = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Traffic.Turn.Direction\":\"left\"}] \
                                }";
static const QString msg_turn_right = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Traffic.Turn.Direction\":\"right\"}] \
                                }";
static const QString msg_all = "{ \
                                  \"action\":\"subscription\", \
                                  \"subscriptionId\":\"1\", \
                                  \"value\":[{\"Signal.Traffic.Turn.Direction\":\"right\"}, \
                                  {\"Signal.Drivetrain.BatteryManagement.BatteryCapacity\":70}, \
                                  {\"Signal.Drivetrain.InternalCombustionEngine.Engine.Speed\":3000}, \
                                  {\"Signal.Drivetrain.Transmission.Gear\":3}, \
                                  {\"Signal.Vehicle.Speed\":21000} \
                                  ] \
                                }";
cluster_view_input::cluster_view_input()
{
        resetSlotState();
}

cluster_view_input::~cluster_view_input()
{

}

void cluster_view_input::test_set_speed()
{
    QSharedPointer<UnitTestSocket> socket(new UnitTestSocket());
    Model model(socket);
    model.setUrlValue("http://fake.com");
    socket->receivedText(msg_subscr);// just initial communication
    socket->receivedText(msg_subscr);
    socket->receivedText(msg_speed);
    auto speed = model.speedValue();
    QCOMPARE(speed, 21);
    socket->close();
}

void cluster_view_input::cluster_view_input::test_set_gear()
{
    QSharedPointer<UnitTestSocket> socket(new UnitTestSocket());
    Model model(socket);
    model.setUrlValue("http://fake.com");
    socket->receivedText(msg_subscr);// just initial communication
    socket->receivedText(msg_subscr);
    socket->receivedText(msg_gear);

    auto gear = model.gearValue();
    QCOMPARE(gear, 3);

    socket->receivedText(msg_gear_park);
    gear = model.gearValue();
    QCOMPARE(gear, 0);

    socket->receivedText(msg_gear_neutral);
    gear = model.gearValue();
    QCOMPARE(gear, 2);

    socket->receivedText(msg_gear_rev);
    gear = model.gearValue();
    QCOMPARE(gear, 5);

    socket->close();
}

void cluster_view_input::test_set_rpm()
{
    QSharedPointer<UnitTestSocket> socket(new UnitTestSocket());
    Model model(socket);
    model.setUrlValue("http://fake.com");
    socket->receivedText(msg_subscr);// just initial communication
    socket->receivedText(msg_subscr);
    socket->receivedText(msg_rpm);

    auto rpm = model.rpmValue();
    QCOMPARE(rpm, 3000);
    socket->close();
}

void cluster_view_input::test_set_battery()
{
    QSharedPointer<UnitTestSocket> socket(new UnitTestSocket());
    Model model(socket);
    model.setUrlValue("http://fake.com");
    socket->receivedText(msg_subscr);// just initial communication
    socket->receivedText(msg_subscr);
    socket->receivedText(msg_battery);

    auto battery = model.batteryValue();
    QCOMPARE(battery, 70);
    socket->close();
}

void cluster_view_input::test_set_turn()
{
    // 1: right
    // 2: left
    QSharedPointer<UnitTestSocket> socket(new UnitTestSocket());
    Model model(socket);
    model.setUrlValue("http://fake.com");
    socket->receivedText(msg_subscr);// just initial communication
    socket->receivedText(msg_subscr);
    socket->receivedText(msg_turn_left);

    auto turn = model.turnValue();
    QCOMPARE(turn, 2);

    socket->receivedText(msg_turn_right);
    turn = model.turnValue();
    QCOMPARE(turn, 1);

    socket->close();
}

void cluster_view_input::test_set_all()
{
    QSharedPointer<UnitTestSocket> socket(new UnitTestSocket());
    Model model(socket);
    model.setUrlValue("http://fake.com");
    socket->receivedText(msg_subscr);// just initial communication
    socket->receivedText(msg_subscr);
    socket->receivedText(msg_all);

    auto turn = model.turnValue();
    QCOMPARE(turn, 1);

    auto battery = model.batteryValue();
    QCOMPARE(battery, 70);

    auto gear = model.gearValue();
    QCOMPARE(gear, 3);

    auto rpm = model.rpmValue();
    QCOMPARE(rpm, 3000);

    auto speed = model.speedValue();
    QCOMPARE(speed, 21);
    socket->close();
}
void cluster_view_input::test_slots()
{
        QSharedPointer<UnitTestSocket> socket(new UnitTestSocket());
        Model model(socket);
        connect(&model, &Model::turnValueChanged, this, &cluster_view_input::turnValueChanged);
        connect(&model, &Model::batteryValueChanged, this, &cluster_view_input::batteryValueChanged);
        connect(&model, &Model::speedValueChanged, this, &cluster_view_input::speedValueChanged);
        connect(&model, &Model::rpmValueChanged, this, &cluster_view_input::rpmValueChanged);
        connect(&model, &Model::gearValueChanged, this, &cluster_view_input::gearValueChanged);
        connect(&model, &Model::urlValueChanged, this, &cluster_view_input::urlValueChanged);

        resetSlotState();
        model.setUrlValue("http://fake.com");
        socket->receivedText(msg_subscr);// just initial communication
        socket->receivedText(msg_subscr);
        socket->receivedText(msg_all);

        QVERIFY(speedChanged);

        QVERIFY(turnChanged);
        QVERIFY(batteryChanged);
        QVERIFY(rpmChanged);
        QVERIFY(gearChanged);
        QVERIFY(urlChanged);
}
void cluster_view_input::resetSlotState()
{
        turnChanged= false;
        batteryChanged= false;
        speedChanged= false;
        rpmChanged= false;
        gearChanged= false;
        urlChanged= false;
}
void cluster_view_input::turnValueChanged()
{
        turnChanged= true;
}
void cluster_view_input::batteryValueChanged()
{
        batteryChanged= true;
}
void cluster_view_input::speedValueChanged()
{
        speedChanged= true;
}
void cluster_view_input::rpmValueChanged()
{
        rpmChanged= true;
}
void cluster_view_input::gearValueChanged()
{
        gearChanged= true;
}
void cluster_view_input::urlValueChanged()
{
        urlChanged= true;
}

void cluster_view_input::test_slots()
{
        QSharedPointer<UnitTestSocket> socket(new UnitTestSocket());
        VisClient client(socket);
        connect(&client, &VisClient::turnValueChanged, this, &cluster_view_input::turnValueChanged);
        connect(&client, &VisClient::batteryValueChanged, this, &cluster_view_input::batteryValueChanged);
        connect(&client, &VisClient::speedValueChanged, this, &cluster_view_input::speedValueChanged);
        connect(&client, &VisClient::rpmValueChanged, this, &cluster_view_input::rpmValueChanged);
        connect(&client, &VisClient::gearValueChanged, this, &cluster_view_input::gearValueChanged);
        connect(&client, &VisClient::urlValueChanged, this, &cluster_view_input::urlValueChanged);

        resetSlotState();
        client.setUrlValue("http://fake.com");
        socket->receivedText(msg_subscr);// just initial communication
        socket->receivedText(msg_subscr);
        socket->receivedText(msg_all);

        QVERIFY(speedChanged);

        QVERIFY(turnChanged);
        QVERIFY(batteryChanged);
        QVERIFY(rpmChanged);
        QVERIFY(gearChanged);
        QVERIFY(urlChanged);
}

void cluster_view_input::resetSlotState()
{
        turnChanged= false;
        batteryChanged= false;
        speedChanged= false;
        rpmChanged= false;
        gearChanged= false;
        urlChanged= false;
}

void cluster_view_input::turnValueChanged()
{
        turnChanged= true;
}

void cluster_view_input::batteryValueChanged()
{
        batteryChanged= true;
}

void cluster_view_input::speedValueChanged()
{
        speedChanged= true;
}

void cluster_view_input::rpmValueChanged()
{
        rpmChanged= true;
}

void cluster_view_input::gearValueChanged()
{
        gearChanged= true;
}

void cluster_view_input::urlValueChanged()
{
        urlChanged= true;
}

QTEST_APPLESS_MAIN(cluster_view_input)

#include "tst_cluster_view_input.moc"
