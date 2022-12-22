#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>
#include <QString>

class CommandLine: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString urlValue READ urlValue WRITE setUrlValue NOTIFY urlValueChanged)
    Q_PROPERTY(int modeValue READ modeValue WRITE setModeValue NOTIFY modeValueChanged)
    Q_PROPERTY(int firstStart READ firstStart WRITE setFirstStart NOTIFY firstStartChanged)
public:
    CommandLine();
    ~CommandLine();

    Q_INVOKABLE QString getUrl() const;
    Q_INVOKABLE int     getMode() const;
    Q_INVOKABLE int     getFirstStart() const;

    QString urlValue();
    void setUrlValue(QString url);

    int modeValue();
    void setModeValue(int mode);

    int firstStart();
    void setFirstStart(int started);

signals:
    void urlValueChanged();
    void modeValueChanged();
    void firstStartChanged();

private:
    QString mUrl;
    int mMode;
    int mFirstStart;
};

#endif // COMMANDLINE_H
