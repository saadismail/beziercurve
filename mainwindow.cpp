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

    // create graph and assign data to it:
    this->mainCurve = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
    this->mainCurve->setPen(QPen(Qt::blue));
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::red));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::green));
    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QPen(Qt::gray));
    ui->customPlot->xAxis->setRange(-10, 100);
    ui->customPlot->yAxis->setRange(-10, 100);

    ui->p0x->setValue(p[0].getX());
    ui->p1x->setValue(p[1].getX());
    ui->p2x->setValue(p[2].getX());
    ui->p3x->setValue(p[3].getX());
    ui->p0y->setValue(p[0].getY());
    ui->p1y->setValue(p[1].getY());
    ui->p2y->setValue(p[2].getY());
    ui->p3y->setValue(p[3].getY());

    double diff;
    for (double t=0; t<=1.01; t=t+0.01) {
        diff = (double)1 - t;
        x << (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y << (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }
    for (int i=0; i<2; i++) {
        l1x << p[i].getX();
        l1y << p[i].getY();
        l2x << p[i+1].getX();
        l2y << p[i+1].getY();
        l3x <<  p[i+2].getX();
        l3y << p[i+2].getY();
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

    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    this->mainCurve->setData(x, y);
    ui->customPlot->graph(0)->setData(l1x, l1y);
    ui->customPlot->graph(1)->setData(l2x, l2y);
    ui->customPlot->graph(2)->setData(l3x, l3y);
    ui->customPlot->replot();
}

void MainWindow::reGraph() {
    x.clear();
    y.clear();
    l1x.clear();
    l1y.clear();
    l2x.clear();
    l2y.clear();
    l3x.clear();
    l3y.clear();

    double diff;
    for (double t=0; t<=1.01; t=t+0.01) {
        diff = (double)1 - t;
        x << (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y << (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }

    for (int i=0; i<2; i++) {
        l1x << p[i].getX();
        l1y << p[i].getY();
        l2x << p[i+1].getX();
        l2y << p[i+1].getY();
        l3x <<  p[i+2].getX();
        l3y << p[i+2].getY();
    }

    this->mainCurve->setData(x, y);
    ui->customPlot->graph(0)->setData(l1x, l1y);
    ui->customPlot->graph(1)->setData(l2x, l2y);
    ui->customPlot->graph(2)->setData(l3x, l3y);
    ui->customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
