#include "./Headers/Jugador.h"

Jugador::Jugador(std::string nombre){
    this->nombre = nombre;
    this->mazo = new Mazo();
    this->tesorosRestantes = 0;
}

Jugador::~Jugador(){
    delete this->mazo;
}

std::string Jugador::getNombre(){
    return this->nombre;
}

int Jugador::getTesorosRestantes(){
    return this->tesorosRestantes;
}

Mazo* Jugador::getMazo(){
    return this->mazo;
}

void Jugador::agregarCarta(TipoCartas tipo){
    this->mazo->agregarCarta(tipo);
}

void Jugador::removerCarta(TipoCartas tipo){
    this->mazo->removerCarta(tipo);
}