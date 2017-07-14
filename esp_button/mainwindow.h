#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <qdebug.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFont>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void fetch();
    void replyFinished(QNetworkReply*);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QNetworkAccessManager* m_manager;

};

#endif // MAINWINDOW_H
