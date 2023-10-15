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
        } else{
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
    } catch (int e){
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