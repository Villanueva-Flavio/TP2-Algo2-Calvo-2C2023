#ifndef __COORDENADADOUBLE_H__
#define __COORDENADADOUBLE_H__
#include <iostream>

class CoordenadaDouble{
    private:
    double x;
    double y;
    double z;

    public:
    CoordenadaDouble(double x, double y, double z);

    double getX();
    double getY();
    double getZ();
    CoordenadaDouble getCoordenadaDouble();

    void setX(double x);
    void setY(double y);
    void setZ(double Z);
    void setCoordenadaDouble(double x, double y, double z);

    friend std::ostream& operator<<(std::ostream& os, const CoordenadaDouble& c);
    friend std::istream& operator>>(std::istream& is, CoordenadaDouble& c);
    friend bool operator==(const CoordenadaDouble& c1, const CoordenadaDouble& c2);
    friend bool operator!=(const CoordenadaDouble& c1, const CoordenadaDouble& c2);

};

#endif