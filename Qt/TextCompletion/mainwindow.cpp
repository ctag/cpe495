#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QThread *thread = new QThread();
    SQLWorker *myWorker = new SQLWorker;
    myWorker->moveToThread(thread);
    thread->start();
    connect(ui->lineEdit, SIGNAL (textChanged(QString)), myWorker, SLOT (doWork(QString)));
    connect(myWorker, SIGNAL(finished(QString*)), this, SLOT(print(QString*)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(press0()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(press1()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(press2()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(press3()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(press4()));
    connect(ui->pushButton_6, SIGNAL(clicked()), ui->lineEdit, SLOT(clear()));

    ui->lineEdit->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print(QString *argv)
{
    ui->pushButton->setText(argv[0]);
    ui->pushButton_2->setText(argv[1]);
    ui->pushButton_3->setText(argv[2]);
    ui->pushButton_4->setText(argv[3]);
    ui->pushButton_5->setText(argv[4]);
}

SQLWorker::SQLWorker()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
}

SQLWorker::~SQLWorker(){}

void SQLWorker::doWork(QString arg)
{
    if (!db.open())
        QMessageBox::warning(0, "Failed to open", "Failed to open");
    QString *out = new QString[5];
    QString sql = "SELECT WORD FROM dictionary WHERE WORD LIKE '" + arg + "%' ORDER BY COUNT DESC LIMIT 5;";
    QSqlQuery query(db);
    query.exec(sql);
    if (!query.isActive())
        QMessageBox::warning(0, "Bad Query", QString("Bad Query, It's inactive:%1").arg(query.lastError().text()));
    else
    {
        for (int i = 0; i < 5; i = i + 1)
        {
            query.next();
            out[i] = query.value(0).toString();
        }
        finished(out);
    }
    db.close();
}

void MainWindow::press0()
{
    ui->lineEdit->setText(ui->pushButton->text());
}

void MainWindow::press1()
{
    ui->lineEdit->setText(ui->pushButton_2->text());
}

void MainWindow::press2()
{
    ui->lineEdit->setText(ui->pushButton_3->text());
}

void MainWindow::press3()
{
    ui->lineEdit->setText(ui->pushButton_4->text());
}

void MainWindow::press4()
{
    ui->lineEdit->setText(ui->pushButton_5->text());
}

void MainWindow::pressE()
{
    ui->lineEdit->clear();
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->lineEdit) // This is the input line
    {
        if (event->type() == QEvent::KeyPress) // This is a keypress
        {
            QKeyEvent *key = static_cast<QKeyEvent*>(event);
            if (key->text() == "{")
            {
                qDebug() << "Here: " << key->key();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return QMainWindow::eventFilter(target, event);
    }
}
