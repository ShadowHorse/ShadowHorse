#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

class ServerThread : public QThread
{
    Q_OBJECT

public:
    ServerThread(int socketDescriptor, const QString &client, QObject *parent);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
};

#endif // SERVERTHREAD_H
