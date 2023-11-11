#include "Juego.h"

void preguntarCantidadJugadores(int* jugadores){
    std::cout << "Ingrese la cantidad de jugadores (2-10): ";
    std::cin >> *jugadores;
    while(*jugadores < 2 || *jugadores > 10){
        std::cout << "Cantidad de jugadores invalida. Ingrese nuevamente: ";
        std::cin >> *jugadores;
    }
}

int main(){
    int jugadores = 0;
    preguntarCantidadJugadores(&jugadores);
    Juego* juego = new Juego(jugadores);
    juego->iniciarJuego(jugadores);
    juego->jugar();
    return 0;
}