#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>
#include <QString>

class CommandLine: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString urlValue READ urlValue WRITE setUrlValue NOTIFY urlValueChanged)
    Q_PROPERTY(int modeValue READ modeValue WRITE setModeValue NOTIFY modeValueChanged)
public:
    CommandLine();

    Q_INVOKABLE QString getUrl() const;
    Q_INVOKABLE int     getMode() const;

    QString urlValue();
    void setUrlValue(QString url);

    int modeValue();
    void setModeValue(int mode);

signals:
    void urlValueChanged();
    void modeValueChanged();

private:
    QString mUrl;
    int mMode;
};

#endif // COMMANDLINE_H
