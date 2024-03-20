#include <QCoreApplication>
#include <QDebug>
#include <QtCore>
#include "VisClient.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Working ...";

    QString url = argc > 1 ? argv[1] : "wss://wwwivi:8088";

    VisClient visClient(&a, url);
    visClient.connectTo();

    return a.exec();
}
