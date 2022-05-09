#include <QCoreApplication>
#include <QDebug>
#include <QtCore>
#include "VisClient.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString rpmsg("/dev/rpmsg0");
    if(argc > 2){
	rpmsg = argv[2];
    }

    qDebug() << "Working ...";

    QString url = argc > 1 ? argv[1] : "wss://wwwivi:8088";

    VisClient visClient(&a, url, rpmsg);
    visClient.connectTo();

    return a.exec();
}
