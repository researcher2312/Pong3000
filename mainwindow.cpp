#include <QGraphicsScene>
#include <QSerialPortInfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxDevices->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->comboBoxDevices->addItem(info.portName()+ " " + info.description());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton1Player_clicked()
{
    Game* game = new Game(ui->comboBoxDevices->currentText(), this);
    ui->stackedWidget->insertWidget(2, game);
    ui->stackedWidget->setCurrentIndex(2);
}
