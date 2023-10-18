#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <string>
#include "Mazo.h"

class Jugador{
    private:
        std::string nombre;
        Mazo *mazo;
        int tesorosRestantes;
    
    public:
        Jugador(std::string nombre);
        ~Jugador();
        std::string getNombre();
        int getTesorosRestantes();
        Mazo* getMazo();
        
        void agregarCarta(TipoCartas tipo);
        void removerCarta(TipoCartas tipo);
};

#endif