#include "commandline.h"

CommandLine::CommandLine()
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

Q_INVOKABLE int CommandLine::getMode() const {
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
