#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    usbPort = new QSerialPort;
    usbPort->close();
    QString name = "ttyACM0";
    usbPort->setPortName(name);

    if (usbPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "opened.";
    }
    else
    {
        qDebug() << "open failed.";
    }

    connect(usbPort, SIGNAL(readyRead()), this, SLOT(doRead()));

//    QFont newFont;
//    newFont.setPixelSize(20);
//    ui->checkBox_1->setFont(newFont);
//    ui->checkBox_2->setFont(newFont);
//    ui->checkBox_3->setFont(newFont);
//    ui->checkBox_4->setFont(newFont);
//    ui->checkBox_5->setFont(newFont);
//    ui->checkBox_6->setFont(newFont);

//    int numRead = 0, numReadTotal = 0;
//    char buffer[50];

//    forever {
//        numRead  = serial.read(buffer, 50);

//        // Do whatever with the array

//        numReadTotal += numRead;
//        if (numRead == 0 && !serial.waitForReadyRead())
//            break;
//    }

}

void MainWindow::doRead()
{
    char buffer[50];
    int numRead = 0;

    if (usbPort->bytesAvailable())
    {
        numRead = usbPort->read(buffer, 10);
        qDebug() << "Data: " << buffer;
        if (buffer[1] == '-')
        {
            // Reset screen
            ui->checkBox_1->setText("ABCDEF");
            ui->checkBox_2->setText("GHIJKL");
            ui->checkBox_3->setText("MNOPQR");
            ui->checkBox_4->setText("STUVWX");
            ui->checkBox_5->setText("YZ1234");
            ui->checkBox_6->setText("567890");
        }
        else
        {
            if (buffer[1] == '0')
            {
                ui->checkBox_1->setText("A");
                ui->checkBox_2->setText("B");
                ui->checkBox_3->setText("C");
                ui->checkBox_4->setText("D");
                ui->checkBox_5->setText("E");
                ui->checkBox_6->setText("F");
            }
            else if (buffer[1] == '1')
            {
                ui->checkBox_1->setText("G");
                ui->checkBox_2->setText("H");
                ui->checkBox_3->setText("I");
                ui->checkBox_4->setText("J");
                ui->checkBox_5->setText("K");
                ui->checkBox_6->setText("L");
            }
            else if (buffer[1] == '2')
            {
                ui->checkBox_1->setText("M");
                ui->checkBox_2->setText("N");
                ui->checkBox_3->setText("O");
                ui->checkBox_4->setText("P");
                ui->checkBox_5->setText("Q");
                ui->checkBox_6->setText("R");
            }
            else if (buffer[1] == '3')
            {
                ui->checkBox_1->setText("S");
                ui->checkBox_2->setText("T");
                ui->checkBox_3->setText("U");
                ui->checkBox_4->setText("V");
                ui->checkBox_5->setText("W");
                ui->checkBox_6->setText("X");
            }
            else if (buffer[1] == '4')
            {
                ui->checkBox_1->setText("Y");
                ui->checkBox_2->setText("Z");
                ui->checkBox_3->setText("1");
                ui->checkBox_4->setText("2");
                ui->checkBox_5->setText("3");
                ui->checkBox_6->setText("4");
            }
            else if (buffer[1] == '5')
            {
                ui->checkBox_1->setText("5");
                ui->checkBox_2->setText("6");
                ui->checkBox_3->setText("7");
                ui->checkBox_4->setText("8");
                ui->checkBox_5->setText("9");
                ui->checkBox_6->setText("0");
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
