#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

private:
    Ui::MainWindow *ui;
    QCPCurve *curve1, *curve2;
    QVector <double> x1, y1, x2, y2, l1x, l1y;
    void reGraph();
};

#endif // MAINWINDOW_H
