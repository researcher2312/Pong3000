#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "serialconnector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton1Player_clicked();

    void on_pushButtonTest_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

    void on_pushButton2Player_clicked();

private:
    Ui::MainWindow *ui;
    SerialConnector* device;
};
#endif // MAINWINDOW_H
