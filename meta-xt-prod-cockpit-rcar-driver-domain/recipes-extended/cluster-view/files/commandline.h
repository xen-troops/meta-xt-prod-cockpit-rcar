#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>
#include <QString>

class CommandLine: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString urlValue READ urlValue WRITE setUrlValue NOTIFY urlValueChanged)
public:
    CommandLine();

    Q_INVOKABLE QString getUrl() const;

    QString urlValue();
    void setUrlValue(QString url);

signals:
    void urlValueChanged();

private:
    QString mUrl;
};

#endif // COMMANDLINE_H
