#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fetch()));
    timer->start(150);

    m_manager = new QNetworkAccessManager(this);

    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
         this, SLOT(replyFinished(QNetworkReply*)));

    //fetch();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fetch()
{
    m_manager->get(QNetworkRequest(QUrl("http://localhost:3002/")));
}

void MainWindow::replyFinished(QNetworkReply* pReply)
{

    QByteArray data=pReply->readAll();
    QString str(data);
    qDebug() << str;
    if (str == "")
        return;
    ui->label->setText(str);
    //fetch();
}










