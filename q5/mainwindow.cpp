#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "point.h"

Point p[7] = {Point(60,72), Point(24,84), Point(24,36), Point(48,42), Point(72,48), Point(72,0), Point(36,12)};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("S using Bezier Curves");

    ui->p0x->setValue((int)p[0].getX());
    ui->p1x->setValue((int)p[1].getX());
    ui->p2x->setValue((int)p[2].getX());
    ui->p3x->setValue((int)p[3].getX());
    ui->p4x->setValue((int)p[4].getX());
    ui->p5x->setValue((int)p[5].getX());
    ui->p6x->setValue((int)p[6].getX());
    ui->p0y->setValue((int)p[0].getY());
    ui->p1y->setValue((int)p[1].getY());
    ui->p2y->setValue((int)p[2].getY());
    ui->p3y->setValue((int)p[3].getY());
    ui->p4y->setValue((int)p[4].getY());
    ui->p5y->setValue((int)p[5].getY());
    ui->p6y->setValue((int)p[6].getY());


    connect(ui->p0x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[0].setX(d); this->reGraph(); });
    connect(ui->p0y, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[0].setY(d); this->reGraph(); });
    connect(ui->p1x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[1].setX(d); this->reGraph(); });
    connect(ui->p1y, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[1].setY(d); this->reGraph(); });
    connect(ui->p2x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[2].setX(d); this->reGraph(); });
    connect(ui->p2y, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[2].setY(d); this->reGraph(); });
    connect(ui->p3x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[3].setX(d); this->reGraph(); });
    connect(ui->p3y, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[3].setY(d); this->reGraph(); });
    connect(ui->p4x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[4].setX(d); this->reGraph(); });
    connect(ui->p4y, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[4].setY(d); this->reGraph(); });
    connect(ui->p5x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[5].setX(d); this->reGraph(); });
    connect(ui->p5y, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[5].setY(d); this->reGraph(); });
    connect(ui->p6x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[6].setX(d); this->reGraph(); });
    connect(ui->p6y, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int d){ p[6].setY(d); this->reGraph(); });

    // create graph and assign data to it:
    this->curve1 = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
    this->curve2 = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setRange(-10, 100);
    ui->customPlot->yAxis->setRange(-10, 100);

    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    double diff;
    for (double t=0; t<=1.01; t=t+0.01) {
        diff = (double)1 - t;
        x1 << (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y1 << (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }

    for (double t=0; t<=1.01; t=t+0.01) {
        diff = (double)1 - t;
        x2 << (p[3].getX() * diff*diff*diff) + (3 * p[4].getX() * t * diff*diff) + (3 * p[5].getX() * t*t * diff) + (p[6].getX() * t*t*t);
        y2 << (p[3].getY() * diff*diff*diff) + (3 * p[4].getY() * t * diff*diff) + (3 * p[5].getY() * t*t * diff) + (p[6].getY() * t*t*t);
    }
    l1x << p[2].getX();
    l1x << p[3].getX();
    l1x << p[4].getX();
    l1y << p[2].getY();
    l1y << p[3].getY();
    l1y << p[4].getY();
    this->curve1->setData(x1, y1);
    this->curve2->setData(x2, y2);
    ui->customPlot->graph(0)->setData(l1x, l1y);
    ui->customPlot->replot();
}

void MainWindow::reGraph() {
    x1.clear();
    y1.clear();
    x2.clear();
    y2.clear();
    l1x.clear();
    l1y.clear();

    double diff;
    for (double t=0; t<=1.01; t=t+0.01) {
        diff = (double)1 - t;
        x1 << (p[0].getX() * diff*diff*diff) + (3 * p[1].getX() * t * diff*diff) + (3 * p[2].getX() * t*t * diff) + (p[3].getX() * t*t*t);
        y1 << (p[0].getY() * diff*diff*diff) + (3 * p[1].getY() * t * diff*diff) + (3 * p[2].getY() * t*t * diff) + (p[3].getY() * t*t*t);
    }

    for (double t=0; t<=1.01; t=t+0.01) {
        diff = (double)1 - t;
        x2 << (p[3].getX() * diff*diff*diff) + (3 * p[4].getX() * t * diff*diff) + (3 * p[5].getX() * t*t * diff) + (p[6].getX() * t*t*t);
        y2 << (p[3].getY() * diff*diff*diff) + (3 * p[4].getY() * t * diff*diff) + (3 * p[5].getY() * t*t * diff) + (p[6].getY() * t*t*t);
    }
    l1x << p[2].getX();
    l1x << p[3].getX();
    l1x << p[4].getX();
    l1y << p[2].getY();
    l1y << p[3].getY();
    l1y << p[4].getY();
    this->curve1->setData(x1, y1);
    this->curve2->setData(x2, y2);
    ui->customPlot->graph(0)->setData(l1x, l1y);
    ui->customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
