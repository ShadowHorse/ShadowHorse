#include <QtWidgets>
#include <QtNetwork>
#include <QWidget>

#include <stdlib.h>

#include "mainwindow.h"
#include "server.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    statusLabel = new QLabel;
    statusLabel->setWordWrap(true);
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);


    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty()) {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    if (!server.listen(QHostAddress(ipAddress), server.getPort())) {
        QMessageBox::critical(this, tr("DarkHorse"),
                              tr("Unable to start the server: %1.")
                              .arg(server.errorString()));
        close();
        return;
    }

    statusLabel->setText(tr("The rat is running on\n\nIP: %1\nport: %2\n\n").arg(ipAddress).arg(server.serverPort()));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QWidget *layoutWidget = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    layoutWidget->setLayout(mainLayout);

    this->setCentralWidget(layoutWidget);

    setWindowTitle(tr("DarkHorse Control Panel"));

}
