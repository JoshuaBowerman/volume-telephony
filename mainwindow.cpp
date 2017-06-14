#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>
#include <QTimer>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::ifstream input;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->lineEdit->setText("Please Dial In Your Volume");
    QTimer *timer = new QTimer(qApp);
    connect(timer, SIGNAL(timeout()), this, SLOT(volume()));
            timer->start(50);

}


void MainWindow::volume(){
    char ch = 1;
input.open("/dev/ttyACM0", std::ios::in);
        input.get(ch);
        input.close();
        switch(ch){
        case '1': ui->lcdNumber->display(1);
            break;
        case '2': ui->lcdNumber->display(2);
            break;
        case '3': ui->lcdNumber->display(3);
            break;
        case '4': ui->lcdNumber->display(4);
            break;
        case '5': ui->lcdNumber->display(5);
            break;
        case '6': ui->lcdNumber->display(6);
            break;
        case '7': ui->lcdNumber->display(7);
            break;
        case '8': ui->lcdNumber->display(8);
            break;
        case '9': ui->lcdNumber->display(9);
            break;
        case '0': ui->lcdNumber->display(0);
            break;
        case 'd': ui->lineEdit->setText("Please Dial In Your Volume");
            break;
        case 'c':
            if(ui->lineEdit->text() == "Please Dial In Your Volume"){
                ui->progressBar->setValue(0);
                ui->lineEdit->setText("");
            }
            if(ui->lcdNumber->intValue() != 0){
                ui->lineEdit->setText(QString::fromStdString(" + " + std::to_string(ui->lcdNumber->intValue()) + ui->lineEdit->text().toStdString()));
                ui->progressBar->setValue(ui->lcdNumber->intValue() + ui->progressBar->value());
                system(("pactl set-sink-volume 1 " + std::to_string(ui->progressBar->value()) + "%").c_str());
                ui->lcdNumber->display(0);
            }

}


}

MainWindow::~MainWindow()
{
    input.close();
    delete ui;
}
