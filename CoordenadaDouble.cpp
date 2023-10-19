#include "./Headers/CoordenadaDouble.h"

CoordenadaDouble::CoordenadaDouble(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

double CoordenadaDouble::getX(){
    return this->x;
}

double CoordenadaDouble::getY(){
    return this->y;
}

double CoordenadaDouble::getZ(){
    return this->z;
}

CoordenadaDouble CoordenadaDouble::getCoordenadaDouble(){
    return *this;
}

void CoordenadaDouble::setX(double x){
    this->x = x;
}

void CoordenadaDouble::setY(double y){
    this->y = y;
}

void CoordenadaDouble::setZ(double z){
    this->z = z;
}

void CoordenadaDouble::setCoordenadaDouble(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

std::ostream& operator<<(std::ostream& os, const CoordenadaDouble& c){
    os << "(" << c.x << ", " << c.y << c.z << ")";
    return os;
}

std::istream& operator>>(std::istream& is, CoordenadaDouble& c){
    is >> c.x >> c.y >> c.z;
    return is;
}

bool operator==(const CoordenadaDouble& c1, const CoordenadaDouble& c2){
    return c1.x == c2.x && c1.y == c2.y && c1.z == c2.z;
}

bool operator!=(const CoordenadaDouble& c1, const CoordenadaDouble& c2){
    return !(c1 == c2);
}