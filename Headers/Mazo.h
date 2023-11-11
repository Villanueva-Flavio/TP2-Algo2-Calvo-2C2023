#ifndef __MAZO_H__
#define __MAZO_H__

#include "../TDA/Lista.h"
#include "Carta.h"
#include <string>

class Mazo{
    private:
        Lista<Carta*>* mazo;
    public:
        Mazo();
        ~Mazo();
        void agregarCarta(TipoCartas tipo);
        void removerCarta(TipoCartas tipo);
        Carta* obtenerCarta(TipoCartas tipo);
        bool estaVacio();
        int obtenerCantidadCartas(TipoCartas tipo);
        Lista<Carta*>* obtenerMazo();
        void usarCarta(TipoCartas tipo);
        std::string tipoDeCartaGlobal(TipoCartas tipo);
};

#endif