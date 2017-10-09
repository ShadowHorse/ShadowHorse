#include "server.h"
#include "serverthread.h"

#include <QCoreApplication>
#include <QSettings>
#include <stdlib.h>

Server::Server(QObject *parent) : QTcpServer(parent)
{
    //load the saved Network configuration
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    settings->beginGroup(QLatin1String("Network"));
    port = QVariant(this->settings->value("port", 1337)).toInt();
    broadcast = QVariant(this->settings->value("broadcast", true)).toBool();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QString client = clients.at(qrand() % clients.size());
    ServerThread *thread = new ServerThread(socketDescriptor, client, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

int Server::getPort() {
    return this->port;
}

bool Server::doBroadcast() {
    return this->broadcast;
}
