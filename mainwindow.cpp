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

    ui->p0x->setValue(p[0].getX());
    ui->p1x->setValue(p[1].getX());
    ui->p2x->setValue(p[2].getX());
    ui->p3x->setValue(p[3].getX());
    ui->p0y->setValue(p[0].getY());
    ui->p1y->setValue(p[1].getY());
    ui->p2y->setValue(p[2].getY());
    ui->p3y->setValue(p[3].getY());

    // generate some data:
    QVector<double> x, y; // initialize with entries 0..100

    double diff;
    for (double t=0; t<=0.85; t=t+0.01) {
        diff = (double)1 - t;
        x << (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y << (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }

    QVector<double> x2, y2;
    for (double t=0.84; t<=1.01; t=t+0.01) {
        diff = (double)1 - t;
        x2 << (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y2 << (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }

    ui->p0x->setKeyboardTracking(false);
    connect(ui->p0x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[0].setX(d); this->reGraph(); });
    connect(ui->p0y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[0].setY(d); this->reGraph(); });
    connect(ui->p1x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[1].setX(d); this->reGraph(); });
    connect(ui->p1y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[1].setY(d); this->reGraph(); });
    connect(ui->p2x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[2].setX(d); this->reGraph(); });
    connect(ui->p2y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[2].setY(d); this->reGraph(); });
    connect(ui->p3x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[3].setX(d); this->reGraph(); });
    connect(ui->p3y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),[=](double d){ p[3].setY(d); this->reGraph(); });

    QVector<double> l1x(2), l1y(2), l2x(2), l2y(2), l3x(2), l3y(2);
    for (int i=0; i<2; i++) {
        l1x[i] = p[i].getX();
        l1y[i] = p[i].getY();
        l2x[i] = p[i+1].getX();
        l2y[i] = p[i+1].getY();
        l3x[i] = p[i+2].getX();
        l3y[i] = p[i+2].getY();
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot->graph(1)->setData(x2, y2);

    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QPen(Qt::green));
    ui->customPlot->graph(2)->setData(l1x, l1y);
    ui->customPlot->addGraph();
    ui->customPlot->graph(3)->setPen(QPen(Qt::yellow));
    ui->customPlot->graph(3)->setData(l2x, l2y);
    ui->customPlot->addGraph();
    ui->customPlot->graph(4)->setPen(QPen(Qt::black));
    ui->customPlot->graph(4)->setData(l3x, l3y);

    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->customPlot->replot();
    connect(ui->graph, SIGNAL (released()), this, SLOT (handleButton()));
}

void MainWindow::handleButton() {
    this->reGraph();
}

void MainWindow::reGraph() {
    QVector<double> x, y; // initialize with entries 0..100

    double diff;
    for (double t=0; t<=0.85; t=t+0.01) {
        diff = (double)1 - t;
        x << (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y << (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }

    QVector<double> x2, y2;
    for (double t=0.84; t<=1.01; t=t+0.01) {
        diff = (double)1 - t;
        x2 << (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y2 << (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->graph(1)->setData(x2, y2);
    ui->customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
