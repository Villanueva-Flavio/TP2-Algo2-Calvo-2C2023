#include "./Headers/Mazo.h"

Mazo::Mazo(){
    this->mazo = new Lista<Carta*>();
}

Mazo::~Mazo(){
    delete this->mazo;
}

void Mazo::agregarCarta(TipoCartas tipo){
    for(int i = 0; i < this->mazo->getSize(); i++){
        if(this->mazo->getLData(i)->getTipo() == tipo){
            this->mazo->getLData(i)->agregarCarta();
        } else {
            this->mazo->add(new Carta(tipo));
        }
    }
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
        std::cout << "CardNotFoundException ("<< e <<")" << std::endl;
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
}

void Mazo::imprimirMazo(std::string jugador){
    std::string nombreArchivo = "./Mazo_" + jugador + ".txt";
    FILE* archivo = fopen(nombreArchivo.c_str(), "w"); 
    for(int i = 0; i < this->mazo->getSize(); i++){
        fprintf(archivo, "%d %d\n", this->mazo->getLData(i)->getTipo(), this->mazo->getLData(i)->getCantidad());
    }
    fclose(archivo);
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