#include "./Headers/Coordenada.h"
#include <iostream>

Coordenada::Coordenada(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
}

int Coordenada::getX(){
    return this->x;
}

int Coordenada::getY(){
    return this->y;
}

int Coordenada::getZ(){
    return this->z;
}

Coordenada Coordenada::getCoordenada(){
    return *this;
}

void Coordenada::setX(int x){
    this->x = x;
}

void Coordenada::setY(int y){
    this->y = y;
}

void Coordenada::setZ(int z){
    this->z = z;
}

void Coordenada::setCoordenada(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
}

std::ostream& operator<<(std::ostream& os, const Coordenada& c){
    os << "(" << c.x << ", " << c.y << ", "<< c.z << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Coordenada& c){
    is >> c.x >> c.y >> c.z;
    return is;
}

bool operator==(const Coordenada& c1, const Coordenada& c2){
    return c1.x == c2.x && c1.y == c2.y && c1.z == c2.z;
}

bool operator!=(const Coordenada& c1, const Coordenada& c2){
    return !(c1 == c2);
}