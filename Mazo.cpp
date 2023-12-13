#include "Mazo.h"
using namespace std;

Mazo::Mazo(){
    this->mazo = new Lista<Carta*>();
}

Mazo::~Mazo(){
    delete this->mazo;
}

void Mazo::agregarCarta(TipoCartas tipo){
    for(int i = 0; i < this->mazo->getSize(); i++){
        if(this->mazo->getLData(i)->getTipo() == tipo){
            this->mazo->add(new Carta(tipo));
        }
    }
    this->mazo->add(new Carta(tipo));
}

void Mazo::removerCarta(TipoCartas tipo){
    for(int i = 0; i < this->mazo->getSize(); i++){
        if(this->mazo->getLData(i)->getTipo() == tipo){
            this->mazo->remove(i);
        }
    }
}

Carta* Mazo::obtenerCarta(TipoCartas tipo){
    try{
        for(int i = 0; i < this->mazo->getSize(); i++){
            if(this->mazo->getLData(i)->getTipo() == tipo){
                return this->mazo->getLData(i);
            }
        }
        throw tipo;
    } catch (TipoCartas e) {
        std::cout << "CardNotFoundException ("<< this->tipoDeCartaGlobal(e) <<")" << std::endl;
        exit(1);
    }
}

bool Mazo::estaVacio(){
    return this->mazo->getSize() == 0;
}

int Mazo::obtenerCantidadCartas(TipoCartas tipo){
    for(int i = 0; i < this->mazo->getSize(); i++){
        if(this->mazo->getLData(i)->getTipo() == tipo){
            return this->mazo->getLData(i)->getCantidad();
        }
    }
    return 0;
}

Lista<Carta*>* Mazo::obtenerMazo(){
    return this->mazo;
}

void Mazo::usarCarta(TipoCartas tipo){
    switch(tipo){
        case BLINDAJE:
            
            this->removerCarta(BLINDAJE);
            break;
        case RADAR:
            this->removerCarta(RADAR);
            break;
        case PARTIR_TESORO:
            this->removerCarta(PARTIR_TESORO);
            break;
        case AGENTES_DURMIENTES:
            this->removerCarta(AGENTES_DURMIENTES);
            break;
        case PALA_PARA_TUNEL:
            this->removerCarta(PALA_PARA_TUNEL);
            break;
        case BOMBA_DE_RACIMO:
            this->removerCarta(BOMBA_DE_RACIMO);
            break;
    }
}

string Mazo::tipoDeCartaGlobal(TipoCartas tipo){
    switch(tipo){
        case BLINDAJE:
            return "Blindaje";
        case RADAR:
            return "Radar";
        case PARTIR_TESORO:
            return "Partir tesoro";
        case AGENTES_DURMIENTES:
            return "Agentes durmientes";
        case PALA_PARA_TUNEL:
            return "Pala para tunel";
        case BOMBA_DE_RACIMO:
            return "Bomba de racimo";
    }
    return "";
}