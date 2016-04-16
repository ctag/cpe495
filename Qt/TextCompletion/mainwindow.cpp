#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QThread *thread = new QThread();
    myWorker = new SQLWorker;
    myWorker->moveToThread(thread);
    thread->start();
    tc = new QTextCursor;
    //connect(ui->plainTextEdit, SIGNAL (textChanged()), myWorker, SLOT (doWork()));
    connect(ui->plainTextEdit, SIGNAL(cursorPositionChanged()), this, SLOT(mySlot()));
    connect(myWorker, SIGNAL(finished(QString*, int)), this, SLOT(print(QString*, int)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(press0()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(press1()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(press2()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(press3()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(press4()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(pressE()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(pressC()));

    //ui->lineEdit->installEventFilter(this);

    myWorker->doWork("");
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

void MainWindow::mySlot()
{
    *tc = ui->plainTextEdit->textCursor();
    tc->select(QTextCursor::WordUnderCursor);
    myWorker->doWork(tc->selectedText());
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
    const char *str = arg.toStdString().c_str();
    bool trm = false;
    for (int i = 0; i < arg.length(); i=i+1)
    {
        switch (str[i])
        {
        case '\'':
            qDebug("Boom");
            break;
        }

    }
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
        //ui->lineEdit->setText(ui->pushButton->text());
        tc->insertText(ui->pushButton->text());
    ui->plainTextEdit->setFocus();
}

void MainWindow::press1()
{
    if (ui->pushButton_2->text() != "")
        //ui->lineEdit->setText(ui->pushButton_2->text());
        tc->insertText(ui->pushButton_2->text());
    ui->plainTextEdit->setFocus();
}

void MainWindow::press2()
{
    if (ui->pushButton_3->text() != "")
        //ui->lineEdit->setText(ui->pushButton_3->text());
        tc->insertText(ui->pushButton_3->text());
    ui->plainTextEdit->setFocus();
}

void MainWindow::press3()
{
    if (ui->pushButton_4->text() != "")
        //ui->lineEdit->setText(ui->pushButton_4->text());
        tc->insertText(ui->pushButton_4->text());
    ui->plainTextEdit->setFocus();
}

void MainWindow::press4()
{
    if (ui->pushButton_5->text() != "")
        //ui->lineEdit->setText(ui->pushButton_5->text());
        tc->insertText(ui->pushButton_5->text());
    ui->plainTextEdit->setFocus();
}

void MainWindow::pressE()
{
    ui->plainTextEdit->clear();
}

void MainWindow::pressC()
{
    QClipboard *temp = QApplication::clipboard();
    temp->setText(ui->plainTextEdit->toPlainText());
    ui->plainTextEdit->clear();
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
            case 39:

                break;
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
