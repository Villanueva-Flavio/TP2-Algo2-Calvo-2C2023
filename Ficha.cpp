#include "../Headers/Ficha.h"

Ficha::Ficha(TipoFichas tipo, Coordenada posicion) : posicion(posicion), tipo(tipo) {}

TipoFichas Ficha::getTipo(){
    return this->tipo;
}

Coordenada Ficha::getPosicion(){
    return this->posicion;
}

void Ficha::setPosicion(Coordenada posicion){
    this->posicion = posicion;
}

void Ficha::setTipo(TipoFichas tipo){
    this->tipo = tipo;
}