#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtGui>
#include <QVariant>
#include <string.h>
#include <qqml.h>
#include <functional>
#include "Model.h"
#include "ActivatedEvent.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qDebug() << "Command line " << argc;
    if(argc > 1)
    {
        qDebug() << "Arg: " << argv[1];
    }
    QQmlApplicationEngine engine;

    Model model;

    if(argc > 1)
    {
        model.setUrlValue(argv[1]);
    }
    else
    {
        model.setUrlValue("wss://wwwivi:443");
    }
    model.setModeValue((argc > 2 && !strcmp(argv[2], "2"))?2:1);
    engine.rootContext()->setContextProperty("model", &model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    std::invoke( []() { ActivatedEvent();} );
        
    return app.exec();
}

