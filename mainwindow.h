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
    void reGraph();

private:
    Ui::MainWindow *ui;
    QCPCurve *mainCurve;
    QVector <double> x, y, l1x, l1y, l2x, l2y, l3x, l3y;
};

#endif // MAINWINDOW_H
