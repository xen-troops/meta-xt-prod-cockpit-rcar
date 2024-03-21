#include <QUrl>
#include "VisSocket.h"

void VisWebSocket::open(const QUrl &url)
{
    onOpen(url);
}

void VisWebSocket::close()
{
    onClose();
}

void VisWebSocket::sendTextMessage(const QString &message)
{
    onSendTextMessage(message);
}

void VisWebSocket::onConnected()
{
    emit connected();
}

void VisWebSocket::onDisconnected()
{
    emit disconnected();
}

void VisWebSocket::onTextMessageReceived(const QString &message)
{
    onTextMessage(message);
    emit textMessageReceived(message);
}
