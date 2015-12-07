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
    connect(myWorker, SIGNAL(finished(QString*, int)), this, SLOT(print(QString*, int)));
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

void MainWindow::print(QString *argv, int argc)
{
    ui->pushButton->setText("");
    ui->pushButton_2->setText("");
    ui->pushButton_3->setText("");
    ui->pushButton_4->setText("");
    ui->pushButton_5->setText("");
    switch(argc)
    {
    case 5:
    ui->pushButton_5->setText(argv[4]);
    case 4:
    ui->pushButton_4->setText(argv[3]);
    case 3:
    ui->pushButton_3->setText(argv[2]);
    case 2:
    ui->pushButton_2->setText(argv[1]);
    case 1:
    ui->pushButton->setText(argv[0]);
    }
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
        int i = 0;
        while (query.next())
        {
            out[i] = query.value(0).toString();
            i = i + 1;
        }
        finished(out, i);
    }
    db.close();
}

void MainWindow::press0()
{
    if (ui->pushButton->text() != "")
        ui->lineEdit->setText(ui->pushButton->text());
}

void MainWindow::press1()
{
    if (ui->pushButton_2->text() != "")
        ui->lineEdit->setText(ui->pushButton_2->text());
}

void MainWindow::press2()
{
    if (ui->pushButton_3->text() != "")
        ui->lineEdit->setText(ui->pushButton_3->text());
}

void MainWindow::press3()
{
    if (ui->pushButton_4->text() != "")
        ui->lineEdit->setText(ui->pushButton_4->text());
}

void MainWindow::press4()
{
    if (ui->pushButton_5->text() != "")
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
            switch(key->key())
            {
            case 123:
                press0();
                return true;
                break;
            case 124:
                press1();
                return true;
                break;
            case 125:
                press2();
                return true;
                break;
            case 126:
                press3();
                return true;
                break;
            case 127:
                press4();
                return true;
                break;
            default:
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
