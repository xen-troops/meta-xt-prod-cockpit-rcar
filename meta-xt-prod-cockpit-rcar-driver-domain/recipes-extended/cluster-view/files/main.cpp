#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtGui>
#include <string.h>
//#include <QtQuick3D/qquick3d.h>
#include <qqml.h>
#include "visclient.h"

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

    if(argc > 1 && !strcmp(argv[1], "1"))
        engine.load(QUrl(QStringLiteral("qrc:/sport.qml")));
    else
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
