#include <QtGui>
#include <QApplication>
//#include <QtGui/QApplication>
#include "mainwindow.h"
#include "EchoServer.h"

int shmid;
char *shmadd;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    EchoServer server;

    if(!server.listen(QHostAddress::Any, 8080)){
        printf("error\n");
        return 1;
    }

    return a.exec();
}
