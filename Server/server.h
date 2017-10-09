#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>

class QSettings;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    void incomingConnection(qintptr socketDescriptor) override;
    int getPort();
    bool doBroadcast();

private:
    QSettings *settings;
    QStringList clients;
    int port;
    bool broadcast;
};


#endif // SERVER_H
