#include "./Headers/Coordenada.h"

Coordenada::Coordenada(int x, int y){
    this->x = x;
    this->y = y;
}

int Coordenada::getX(){
    return this->x;
}

int Coordenada::getY(){
    return this->y;
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

void Coordenada::setCoordenada(int x, int y){
    this->x = x;
    this->y = y;
}

bool Coordenada::operator==(const Coordenada& c) const{
    return (this->x == c.x && this->y == c.y);
}

bool Coordenada::operator!=(const Coordenada& c) const{
    return (this->x != c.x || this->y != c.y);
}

void Coordenada::operator>>(Coordenada& c){
    c.x = this->x;
    c.y = this->y;
}

void Coordenada::operator<<(Coordenada& c){
    this->x = c.x;
    this->y = c.y;
}