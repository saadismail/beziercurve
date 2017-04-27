#ifndef POINT_H
#define POINT_H

class Point {
private:
    double x;
    double y;
public:
    Point(double, double);
    void setX(double);
    void setY(double);
    void setXY(double, double);
    double getX();
    double getY();
};

#endif // POINT_H
