#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <sys/shm.h>

class ClientSocket : public QTcpSocket {
    Q_OBJECT
public:
    ClientSocket(QObject *parent=0);
   // friend class MainWindow;

private slots:
    void readClient();
private:
    quint16 nextBlockSize;
};

#endif // CLIENTSOCKET_H
