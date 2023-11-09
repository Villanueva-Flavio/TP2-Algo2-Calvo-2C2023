#ifndef __FICHA_H__
#define __FICHA_H__

#include "Coordenada.h"
#include "Enums.h"

class Ficha{
    private:
        Coordenada posicion;
        TipoFichas tipo;
        int jugadorOwner;
        int turnosInactiva;

    public:
        Ficha(TipoFichas tipo, Coordenada posicion, int jugadorOwner, int turnosInactiva);
        TipoFichas getTipo();
        Coordenada getPosicion();
        void setPosicion(Coordenada posicion);
        void setTipo (TipoFichas tipo);
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
        void setTurnosInactiva(int turnosInactiva);
        bool estaInactiva();
        void restarTurnoInactiva();
};

#endif