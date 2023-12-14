#include "Juego.h"
#include "Enums.h"
#include <cstdlib>
#include <ctime>

void preguntarCantidadJugadores(int* jugadores){
    std::cout << COLOR_AMARILLO "Ingrese la cantidad de jugadores (2-10): " << COLOR_VERDE;
    std::cin >> *jugadores;
    std::cout << RES_COLOR;
    while(*jugadores < 2 || *jugadores > 10){
        std::cout << COLOR_AMARILLO << "Cantidad de jugadores invalida. Ingrese nuevamente: " << COLOR_VERDE;
        std::cin >> *jugadores;
        std::cout << RES_COLOR;
    }
    system("clear");
}

int main(){
    srand(time(NULL));
    int jugadores = 0;
    preguntarCantidadJugadores(&jugadores);
    Juego* juego = new Juego(jugadores);
    juego->jugar();
    delete juego;
    return 0;
}