#include "ClientSocket.h"
#include <QByteArray>
#include "ui_mainwindow.h"
#include "mainwindow.h"


ClientSocket::ClientSocket(QObject *parent)
    :QTcpSocket(parent){
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater())
    );
}

//클라이언트 요청을 읽고 메아리로 돌려줌
void ClientSocket::readClient(){
    QDataStream in(this);

    extern char *shmadd;
    extern int shmid;
    extern Ui::MainWindow *ui;

    shmadd = (char *)shmat(shmid,0,0);
    if(shmadd == (char*)-1){
        printf("shmat error \n");
        return;
    }
    else{
        printf("shmat success \n");
    }

    if(nextBlockSize == 0){
        if(this->bytesAvailable() < sizeof(quint16));
        else
            in>>nextBlockSize;
    }
    else if(this->bytesAvailable() < nextBlockSize)
        return;

    QString strRead;
    in>>strRead;
    //this->textEdit->append(strRead);
    //w.ui->textEdit->append(strRead);
    ui->textEdit->append(strRead);
    struct shmid_ds st;
    if(shmctl(shmid,IPC_STAT,&st)== -1){
        printf("shmctl error\n");
        return;
    }
    else{
        printf("shmctl success\n");
    }


    //sprintf(shmadd, "%s", strRead);
    //shmadd = strRead;

    //cin>>string
    this->nextBlockSize = 0;

    strRead.insert(0,"EHCO : ");

    printf("%s\n",shmadd);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out<<quint16(0);
    out<<strRead;
    out.device()->seek(0);
    out<<quint16(block.size() - sizeof(quint16));
    this->write(block);

    shmdt(shmadd);
}

