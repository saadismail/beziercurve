#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "point.h"

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

    ui->p0x->setValue(4);
    ui->p1x->setValue(28);
    ui->p2x->setValue(50);
    ui->p3x->setValue(40);
    ui->p0y->setValue(1);
    ui->p1y->setValue(48);
    ui->p2y->setValue(42);
    ui->p3y->setValue(5);


    // Connect buttons
    connect(ui->q1, SIGNAL (released()), this, SLOT (handleq1()));
    connect(ui->q3, SIGNAL (released()), this, SLOT (handleq3()));
    connect(ui->q4, SIGNAL (released()), this, SLOT (handleq4()));

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
        x << (ui->p0x->value() * diff*diff*diff) + (3 * ui->p1x->value() * t * diff*diff) + (3 * ui->p2x->value() * t*t * diff) + (ui->p3x->value() * t*t*t);
        y << (ui->p0y->value() * diff*diff*diff) + (3 * ui->p1y->value() * t * diff*diff) + (3 * ui->p2y->value() * t*t * diff) + (ui->p3y->value() * t*t*t);
    }

    l1x << ui->p0x->value();
    l1x << ui->p1x->value();
    l1y << ui->p0y->value();
    l1y << ui->p1y->value();
    l2x << ui->p1x->value();
    l2x << ui->p2x->value();
    l2y << ui->p1y->value();
    l2y << ui->p2y->value();
    l3x << ui->p2x->value();
    l3x << ui->p3x->value();
    l3y << ui->p2y->value();
    l3y << ui->p3y->value();

    this->mainCurve->setData(x, y);
    ui->customPlot->graph(0)->setData(l1x, l1y);
    ui->customPlot->graph(1)->setData(l2x, l2y);
    ui->customPlot->graph(2)->setData(l3x, l3y);
    ui->customPlot->replot();
}

void MainWindow::handleq1() {
    ui->p0x->setValue(4);
    ui->p1x->setValue(28);
    ui->p2x->setValue(50);
    ui->p3x->setValue(40);
    ui->p0y->setValue(1);
    ui->p1y->setValue(48);
    ui->p2y->setValue(42);
    ui->p3y->setValue(5);
    this->reGraph();
}

void MainWindow::handleq3() {
    ui->p0x->setValue(4);
    ui->p1x->setValue(80);
    ui->p2x->setValue(50);
    ui->p3x->setValue(40);
    ui->p0y->setValue(1);
    ui->p1y->setValue(10);
    ui->p2y->setValue(42);
    ui->p3y->setValue(5);
    this->reGraph();
}
void MainWindow::handleq4() {
    ui->p0x->setValue(80);
    ui->p1x->setValue(20);
    ui->p2x->setValue(20);
    ui->p3x->setValue(80);
    ui->p0y->setValue(80);
    ui->p1y->setValue(90);
    ui->p2y->setValue(10);
    ui->p3y->setValue(20);
    this->reGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}
