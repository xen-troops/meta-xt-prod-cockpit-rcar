#include "commandline.h"
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <QDebug>

static void setStartMarker(int started)
{
    QFile file("/tmp/clusterview.started");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&file);
    stream << started << endl;
    file.close();
}

CommandLine::CommandLine()
{
    mFirstStart = (int)!QFile::exists("/tmp/clusterview.started");
    setStartMarker(1);
}

CommandLine::~CommandLine()
{
}

Q_INVOKABLE QString CommandLine::getUrl() const {
    return mUrl;
}

QString CommandLine::urlValue()
{
    return mUrl;
}
void CommandLine::setUrlValue(QString url)
{
    if(mUrl == url)
    {
        return;
    }

    mUrl = url;

    emit urlValueChanged();
}

Q_INVOKABLE int CommandLine::getMode() const
{
    return mMode;
}


int CommandLine::modeValue()
{
    return mMode;
}
void CommandLine::setModeValue(int mode)
{
    if(mMode == mode)
    {
        return;
    }

    mMode = mode;

    emit modeValueChanged();
}

Q_INVOKABLE int CommandLine::getFirstStart() const
{
    qDebug() << "Get firstStart " << mFirstStart;
    return mFirstStart;
}
int CommandLine::firstStart()
{
    return mFirstStart;
}
void CommandLine::setFirstStart(int started)
{
    if(mFirstStart)
    {
        setStartMarker(started);
        mFirstStart = 0;
    }
}
