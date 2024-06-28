#ifndef VISSOCKET_H
#define VISSOCKET_H

#include <QObject>
#include <QUrl>
#include <QString>

class VisWebSocket: public QObject
{
    Q_OBJECT
public:
    void open(const QUrl &url);
    void close();
    void sendTextMessage(const QString &message);

Q_SIGNALS:
    void connected();
    void disconnected();
    void textMessageReceived(const QString &message);

protected Q_SLOTS:

    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString &message);

protected:
    virtual void onOpen(const QUrl &url) = 0;
    virtual void onClose() = 0;
    virtual void onSendTextMessage(const QString &message)= 0;
    virtual void onTextMessage(const QString &message) = 0;
};



#endif // VISSOCKET_H
