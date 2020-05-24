#include <QGraphicsScene>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Paddle.h"
#include "Ball.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene();
    Paddle* paddle = new Paddle(0, scene->height()/2);
    scene->addItem(paddle);
    paddle->setFlag(QGraphicsItem::ItemIsFocusable);
    paddle->setFocus();
    Ball* ball = new Ball();
    ball->setPos(20, 20);
    scene->addItem(ball);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(800, 600);
    scene->setSceneRect(0,0, 800, 600);
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
