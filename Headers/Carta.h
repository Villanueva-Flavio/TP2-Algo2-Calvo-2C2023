
#ifndef __CARTA_H__
#define __CARTA_H__
#include "Enums.h"
#include "Jugador.h"
#include "../TDA/Tablero.h"

class Carta {
    private:
        TipoCartas tipo;
        int cantidad;
    
    public:
        Carta(TipoCartas tipo); 
        ~Carta();
        void agregarCarta();
        void removerCarta();
        TipoCartas getTipo();
        int getCantidad();
        void efectoBlindaje(Jugador* jugador);
        void duplicarTesoro(int x, int y, int z);
};

#endif

