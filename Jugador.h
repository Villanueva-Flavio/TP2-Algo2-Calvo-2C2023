#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <string>
#include "Mazo.h"
#include "Ficha.h"

class Jugador{
    private:
        std::string nombre;
        Mazo* mazo;
        Lista<Ficha*>* fichas;
    
    public:
        Jugador(std::string nombre);
        ~Jugador();
        std::string getNombre();
        int getTesorosRestantes();
        Lista<Ficha*>* getListaFichas();
        Mazo* getMazo();
        int getLenFichas();
        
        void agregarCarta(TipoCartas tipo);
        void removerCarta(TipoCartas tipo);
};

#endif