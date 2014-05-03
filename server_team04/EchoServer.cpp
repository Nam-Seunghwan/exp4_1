#include "EchoServer.h"
#include "ClientSocket.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

EchoServer::EchoServer(QObject *parent)
    :QTcpServer(parent){
    extern int shmid;
   // extern char *shmadd;
    shmid=shmget((key_t)1234,1024,0666|IPC_CREAT);
    if(shmid == -1){
        printf("shmget error!!\n");
        return;
    }
    else{
        printf("shmget success!!\n");
    }
}

void EchoServer::incomingConnection(int socketId){
    ClientSocket *socket = new ClientSocket(this);

    socket->setSocketDescriptor(socketId);
}

