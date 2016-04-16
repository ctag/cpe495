#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QtSql>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>
#include <QTextCursor>

namespace Ui {
class MainWindow;
}

class SQLWorker : public QObject
{
    Q_OBJECT
public:
    SQLWorker();
    ~SQLWorker();
public slots:
    void doWork(QString arg);
signals:
    void finished(QString *argv, int argc);
private:
    QSqlDatabase db;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SQLWorker *myWorker;
    QTextCursor *tc;
    //void keyPressEvent(QKeyEvent * event);

protected:
    bool eventFilter(QObject *target, QEvent *event);

private slots:
    void print(QString *argv, int argc);
    void press0();
    void press1();
    void press2();
    void press3();
    void press4();
    void pressE();
    void pressC();
    void mySlot();
};

#endif // MAINWINDOW_H
