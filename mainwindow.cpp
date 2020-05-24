#include <QGraphicsScene>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Game* game = new Game(this);
    ui->setupUi(this);
    ui->graphicsView->setScene(game);
    ui->graphicsView->setFixedSize(808, 606);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton1Player_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}
