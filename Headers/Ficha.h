#ifndef __FICHA_H__
#define __FICHA_H__

#include "Coordenada.h"
#include "Enums.h"

class Ficha{
    private:
        Coordenada posicion;
        TipoFichas tipo;

    public:
        Ficha(TipoFichas tipo, Coordenada posicion);
        TipoFichas getTipo();
        Coordenada getPosicion();
        void setPosicion(Coordenada posicion);
        virtual void interactuarConTesoro();
        virtual void interactuarConEspia();
        virtual void interactuarConVacio();
        virtual void interactuarConInactivo();
};

#endif