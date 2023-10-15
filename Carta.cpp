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