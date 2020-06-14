#include <QGraphicsScene>
#include <QSerialPortInfo>
#include <QChartView>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include "chart.h"

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
    int difficulty = 0;
    auto difficulty_text = ui->comboBoxDifficulty->currentText();
    if (difficulty_text == "Łatwy")
        difficulty = 1;
    else if (difficulty_text == "Średni")
        difficulty = 3;
    else if (difficulty_text == "Trudny")
        difficulty = 5;

    Game* game;
    if(!device->isOpen()) {
        game = new KeyboardPlayedGame(this, true, difficulty);
    }
    else {
        game = new USBPlayedGame(device, this, true, difficulty);
    }

    ui->stackedWidget->insertWidget(2, game);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton2Player_clicked()
{
    Game* game;
    if(!device->isOpen()) {
        game = new KeyboardPlayedGame(this);
    }
    else {
        game = new USBPlayedGame(device, this);
    }

    ui->stackedWidget->insertWidget(2, game);
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButtonTest_clicked()
{
    QChartView *chartView = new QChartView(this);
    Chart *chart = new Chart(device, 0);
    chartView->setChart(chart);

    QChartView *chartView1 = new QChartView(this);
    Chart *chart1 = new Chart(device, 1);
    chartView1->setChart(chart1);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(chartView);
    layout->addWidget(chartView1);

    QWidget* widget = new QWidget(this);
    widget->setLayout(layout);
    ui->stackedWidget->insertWidget(3, widget);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButtonConnect_clicked()
{
    if (ui->comboBoxDevices->count() > 0){
        if (device->connect(ui->comboBoxDevices->currentText())){
            ui->pushButtonConnect->setDisabled(true);
            ui->pushButtonDisconnect->setDisabled(false);
        }
    }
    ui->comboBoxDevices->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->comboBoxDevices->addItem(info.portName());
    }
}

void MainWindow::on_pushButtonDisconnect_clicked()
{
    device->close();
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);
}
