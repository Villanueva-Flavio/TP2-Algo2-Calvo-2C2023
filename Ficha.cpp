#include "Ficha.h"

Ficha::Ficha(TipoFichas tipo, Coordenada posicion, int jugadorOwner, int turnosInactiva, bool protrgido) : posicion(posicion), tipo(tipo), jugadorOwner(0), turnosInactiva(turnosInactiva) , protegido(false){}

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
void Ficha::setProtegido(bool estado){
    this->protegido = estado;
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

TipoTerreno Ficha::getTipoTerreno(){
    return this->tipoTerreno;
}

void Ficha::setTipoTerreno(TipoTerreno tipo){
    this->tipoTerreno = tipo;
}


bool Ficha::estaProtegido(){
    return this->protegido;
}