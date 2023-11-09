#ifndef __FICHA_H__
#define __FICHA_H__

#include "Coordenada.h"
#include "Enums.h"

class Ficha{
    private:
        Coordenada posicion;
        TipoFichas tipo;
        int jugadorOwner;

    public:
        Ficha(TipoFichas tipo, Coordenada posicion, int jugadorOwner);
        TipoFichas getTipo();
        Coordenada getPosicion();
        void setPosicion(Coordenada posicion);
        void setTipo (TipoFichas tipo);
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
};

#endif