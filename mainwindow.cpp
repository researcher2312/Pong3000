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
    chartView->setRenderHint(QPainter::Antialiasing);

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
