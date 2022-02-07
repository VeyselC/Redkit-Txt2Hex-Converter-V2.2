#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTimer>

#include "aboutdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *timer = new QTimer(this);

public slots:
    void timerSlot();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    AboutDialog aboutDialog;
    QString RusString, HexString;
    QString Husamettin_RusString, Husamettin_HexString;
};

#endif // MAINWINDOW_H
