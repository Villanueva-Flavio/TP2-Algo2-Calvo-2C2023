#include "Ficha.h"

Ficha::Ficha(TipoFichas tipo, Coordenada posicion){
    this->tipo = tipo;
    this->posicion = posicion;
}

TipoFichas Ficha::getTipo(){
    return this->tipo;
}

Coordenada Ficha::getPosicion(){
    return this->posicion;
}

void Ficha::setPosicion(Coordenada posicion){
    this->posicion = posicion;
}