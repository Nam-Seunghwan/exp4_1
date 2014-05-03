#include "mainwindow.h"
#include "ui_mainwindow.h"
 #include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //conect signal and slot
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(onConnectServer()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendRequest()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
}

void MainWindow::connectToServer() {
    //request the connection to server
    tcpSocket.connectToHost(QHostAddress::LocalHost, 8080);
}

void MainWindow::onConnectServer(){
    ui->textEdit->setText(tr("connect Complete"));
}

void MainWindow::sendRequest(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    //전송될 메시지의 사이즈 입력
    //사이즈는 가변이므로 일단 0으로
    out<<quint16(0);

    //전송될 메시지 읽음
    out<<ui->lineEdit->text();

    //사이즈를 생성
    //스트림에 포인터를 맨 앞으로
    out.device()->seek(0);

    //사이즈 입력
    out<<quint16(block.size() - sizeof(quint16));

    //소켓으로 전송
    tcpSocket.write(block);

    ui->lineEdit->setText("");
}

void MainWindow::readMessage(){
    QDataStream in(&tcpSocket);

    while(true){
         //nextBlcokSize 가 0 이면 아직 데이터를 못받은것
        if(nextBlockSize == 0){
            //수신된 데이터가 nextBlockSize 바이트보다 큰지 확인
            if(tcpSocket.bytesAvailable() < sizeof(quint16))
                ;
            else
                in>>nextBlockSize;
            continue;
        }
        //nextBlcokSize가 도착하면 사이즈만큼 데이터가 도착했는지 확인
       else if(tcpSocket.bytesAvailable() < nextBlockSize)
            continue;

        //데이터를 표시
       else if(tcpSocket.bytesAvailable() >= nextBlockSize){
            QString strBuf;
            in>>strBuf;
            ui->textEdit->append(strBuf);
            this->nextBlockSize = 0;

            break;
        }
    }
}

void MainWindow::connectionClosedByServer(){
    tcpSocket.close();
}

void MainWindow::error(){
    ui->textEdit->setText(tcpSocket.errorString());
}

MainWindow::~MainWindow()
{
    delete ui;
}
