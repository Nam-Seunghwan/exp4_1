#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <QTcpServer>
#include "ui_mainwindow.h"
#include "mainwindow.h"

class EchoServer : public QTcpServer{
    Q_OBJECT
public:
    EchoServer(QObject *parent=0);

private:
    //overload
    void incomingConnection(int socketId);// if client connect request then call
};

#endif // ECHOSERVER_H
