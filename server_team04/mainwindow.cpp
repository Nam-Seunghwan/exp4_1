#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QByteArray>
#include "ClientSocket.h"


//MainWindow *form = new MainWindow();
//Ui::MainWindow *ui;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow::setTextEdit(const QString &str) {
     ui->textEdit1->setText(str);
 }

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

 /*
    struct shmid_ds st;
    if(shmctl(shmid,IPC_STAT,&st)== -1){
        printf("shmctl error\n");
        return;
    }
    else{
        printf("shmctl success\n");
    }
*/

    QByteArray temp;
    temp = strRead.toLatin1();
    shmadd = temp.data();

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
