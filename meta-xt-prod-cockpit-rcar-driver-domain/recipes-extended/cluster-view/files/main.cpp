#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtGui>
#include <string.h>
//#include <QtQuick3D/qquick3d.h>
#include <qqml.h>

#include "visclient.h"
#include "commandline.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat());
    qDebug() << "Command line " << argc;
    if(argc > 1)
    {
        qDebug() << "Arg: " << argv[1];
    }
    QQmlApplicationEngine engine;

    qmlRegisterType<VisClient>("VisClient", 1, 0, "VisClient");

    CommandLine cmd;
    cmd.setUrlValue("wss://wwwivi:443");
    cmd.setModeValue((argc > 2 && !strcmp(argv[2], "2"))?2:1);

    if(argc > 1){
        cmd.setUrlValue(argv[1]);
    }

    engine.rootContext()->setContextProperty("cmdLine", &cmd);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
