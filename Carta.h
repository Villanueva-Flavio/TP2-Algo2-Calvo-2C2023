#ifndef __CARTA_H__
#define __CARTA_H__

#include "Enums.h"


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
};

#endif

