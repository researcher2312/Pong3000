#include <QGraphicsScene>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton1Player_clicked()
{
    Game* game = new Game(this);
    ui->stackedWidget->insertWidget(2, game);
    ui->stackedWidget->setCurrentIndex(2);
}
