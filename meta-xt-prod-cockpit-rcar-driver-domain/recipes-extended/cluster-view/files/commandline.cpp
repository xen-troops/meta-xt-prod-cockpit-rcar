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
