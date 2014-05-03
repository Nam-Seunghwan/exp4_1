#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
  //  void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QTcpSocket tcpSocket;
    quint16 nextBlockSize;

private slots:
    void connectToServer();
    void onConnectServer();
    void sendRequest();
    void readMessage();
    void connectionClosedByServer();
    void error();

};

#endif // MAINWINDOW_H
