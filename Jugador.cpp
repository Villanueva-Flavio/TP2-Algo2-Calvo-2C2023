#include "Headers/Jugador.h"

Jugador::Jugador(std::string nombre){
    this->nombre = nombre;
    this->mazo = new Mazo();
    this->fichas = new Lista<Ficha*>();
}

Jugador::~Jugador(){
    delete this->mazo;
}

std::string Jugador::getNombre(){
    return this->nombre;
}

int Jugador::getTesorosRestantes(){
    int contador = 0;
    for(int x = 0; x < fichas->getSize() - 1; x++){
        if(fichas->getLData(x)->getTipo() == TESORO){
            contador++;
        }
    }
    return contador;
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

Lista<Ficha*>* Jugador::getListaFichas(){
    //preguntar
    return this->fichas;
}

int Jugador::getLenFichas(){
    return fichas->getSize();
}

