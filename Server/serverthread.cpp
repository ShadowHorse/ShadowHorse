#include "serverthread.h"

#include <QtNetwork>

ServerThread::ServerThread(int socketDescriptor, const QString &client, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), text(client)
{

}

void ServerThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << text;

    tcpSocket.write(block);
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}
