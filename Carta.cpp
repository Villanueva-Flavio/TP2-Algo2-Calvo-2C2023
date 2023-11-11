#include "./Headers/Carta.h"

Carta::Carta(TipoCartas tipo){
    this->tipo = tipo;
    this->cantidad = 1;
}

void Carta::agregarCarta(){
    this->cantidad += 1;
}

void Carta::removerCarta(){
    this->cantidad -= 1; 
}

TipoCartas Carta::getTipo(){
    return this->tipo;
}

int Carta::getCantidad(){
    return this->cantidad;
}

void Carta::efectoBlindaje(Jugador* jugador){
    //Protege las fichas del jugador.

    //preguntar
    Lista<Ficha*>* fichas = jugador->getListaFichas();
    for(int x = 0; x < jugador->getLenFichas(); x++){
        Ficha* ficha = fichas->getLData(x);
        if((ficha->getTipo() == TESORO) || (ficha->getTipo() == ESPIA)){
            ficha->setProtegido(true);
        }
    }
}

void Carta::duplicarTesoro(int x, int y, int z){
    
}