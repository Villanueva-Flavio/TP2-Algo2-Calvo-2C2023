#include "Headers/Jugador.h"

Jugador::Jugador(std::string nombre){
    this->nombre = nombre;
    this->mazo = new Mazo();
    this->fichas = new Lista<Ficha*>();
}

Jugador::~Jugador(){
    delete this->mazo;
    delete this->fichas;
}

std::string Jugador::getNombre(){
    return this->nombre;
}

int Jugador::getTesorosRestantes(){
    int res = 0;
    for(int i = 0; i < this->fichas->getSize(); i++){
        Ficha* ficha = this->fichas->getLData(i);
        if(ficha->getTipo() == TESORO || ficha->getTipo() == TESORO_DESENTERRADO){
            res++;
        }
    }
    return res;
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

