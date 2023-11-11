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
        bool protegido;

    public:
        Ficha(TipoFichas tipo, Coordenada posicion, int jugadorOwner, int turnosInactiva, bool protegido);
        TipoFichas getTipo();
        Coordenada getPosicion();
        void setPosicion(Coordenada posicion);
        void setTipo (TipoFichas tipo);
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
        void setTurnosInactiva(int turnosInactiva);
        bool estaInactiva();
        void restarTurnoInactiva();
        bool estaProtegido();
        void setProtegido(bool estado);
};

#endif