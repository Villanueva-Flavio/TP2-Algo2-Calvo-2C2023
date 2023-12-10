#include "Juego.h"
#include <cstdlib>
#include <ctime>

void preguntarCantidadJugadores(int* jugadores){
    std::cout << "Ingrese la cantidad de jugadores (2-10): ";
    std::cin >> *jugadores;
    while(*jugadores < 2 || *jugadores > 10){
        std::cout << "Cantidad de jugadores invalida. Ingrese nuevamente: ";
        std::cin >> *jugadores;
    }
    system("clear");
}

int main(){
    srand(time(NULL));
    int jugadores = 0;
    preguntarCantidadJugadores(&jugadores);
    Juego* juego = new Juego(jugadores);
    juego->jugar();
    return 0;
}