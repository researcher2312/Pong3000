#include <QGraphicsScene>
#include <QSerialPortInfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    device = new SerialConnector(this);
    ui->setupUi(this);
    ui->comboBoxDevices->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton1Player_clicked()
{
    Game* game;
    if(ui->comboBoxDevices->count() == 0) {
        game = new KeyboardPlayedGame(this);
    }
    else {
        game = new USBPlayedGame(ui->comboBoxDevices->currentText(), this);
    }

    ui->stackedWidget->insertWidget(2, game);
    ui->stackedWidget->setCurrentIndex(2);
}
