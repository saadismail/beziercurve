#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "point.h"
#include <iostream>

Point p[4] = {Point(4,1), Point(28,48), Point(50,42), Point(40,5)};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Bezier Curves");

    // generate some data:
    QVector<double> x(100), y(100); // initialize with entries 0..100

    int i=0;
    double diff;
    for (double t=0; t<=1; t=t+0.01, i++) {
        diff = (double)1 - t;
        x[i] = (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y[i] = (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }

//    ui->p0x->setKeyboardTracking(false);
//    connect(ui->p0x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[0].setX(d); });
//    connect(ui->p0y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[0].setY(d); });
//    connect(ui->p1x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[1].setX(d); });
//    connect(ui->p1y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[1].setY(d); });
//    connect(ui->p2x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[2].setX(d); });
//    connect(ui->p2y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[2].setY(d); });
//    connect(ui->p3x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[3].setX(d); });
//    connect(ui->p3y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[3].setY(d); });

//    QVector<double> l1x(2), l1y(2), l2x(2), l2y(2), l3x(2), l3y(2);
//    for (int i=0; i<2; i++) {
//        l1x[i] = p[i].getX();
//        l1y[i] = p[i].getY();
//        l2x[i] = p[i+1].getX();
//        l2y[i] = p[i+1].getY();
//        l3x[i] = p[i+2].getX();
//        l3y[i] = p[i+2].getY();
//    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes to autoscale, so we see all data:
    ui->customPlot->xAxis->setRange(0,100);
    ui->customPlot->yAxis->setRange(0,100);


    ui->customPlot->replot();
    connect(ui->graph, SIGNAL (released()), this, SLOT (handleButton()));
}

void MainWindow::handleButton() {
    int i=0;
    double diff;
    QVector<double> x(101), y(101);
    for (double t=0; t<=1; t=t+0.01, i++) {
        diff = (double)1 - t;
        x[i] = (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y[i] = (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->replot();
    std::cout<<"Yay"<<std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
