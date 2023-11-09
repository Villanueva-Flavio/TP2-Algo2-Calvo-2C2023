#include "../Headers/Ficha.h"

Ficha::Ficha(TipoFichas tipo, Coordenada posicion, int jugadorOwner, int turnosInactiva) : posicion(posicion), tipo(tipo), jugadorOwner(0), turnosInactiva(turnosInactiva) {}

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

int Ficha::getJugadorOwner(){
    return this->jugadorOwner;
}

void Ficha::setJugadorOwner(int jugadorOwner){
    this->jugadorOwner = jugadorOwner;
}

void Ficha::setTurnosInactiva(int turnosInactiva){
    this->turnosInactiva = turnosInactiva;
}

bool Ficha::estaInactiva(){
    return this->turnosInactiva > 0;
}

void Ficha::restarTurnoInactiva(){
    this->turnosInactiva--;
}