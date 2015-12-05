#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
//#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QPointer>
#include <QFont>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPointer<QSerialPort> usbPort;

 public slots:
    void doRead();

private:
    Ui::MainWindow *ui;
    //QSerialPortInfo portInfo;

};

#endif // MAINWINDOW_H
