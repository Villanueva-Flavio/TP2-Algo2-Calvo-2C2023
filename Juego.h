#ifndef __JUEGO_H__
#define __JUEGO_H__

#include <string>
#include "Tablero.h"
#include "Jugador.h"

class Juego{
public:
    Juego(int jugadores);
    void iniciarJuego(int jugadores);
    void jugar();
    int mostrarEstadoPartida();
    ~Juego();

private:
    //Atributos
    Lista<Jugador*>* jugadores;
    Tablero<Ficha*>* tablero;
    Lista<Ficha*>* inactivas;
    int estadoPartida;

    //Iniciar juego
    bool crearDirectorio(const char* path);
    void cargarTablero(); 
    void cargarTesoros();
    std::string preguntarNombre();
    void cargarJugadores(int jugadores);
    bool validarNombre(std::string nombre);
    bool coordenadaValida(Coordenada* pos);
    bool validarLimitePosicion(Coordenada* pos);
    
    //Jugar
    void jugarTurno();
    void checkEstadoPartida();

    //Carta
    void handlerCarta(int res);
    void handlerMazo();
    void preguntarDecisionMazo(Decision* decision);
    void jugarCartaDelMazo();
    void recibirCarta(int* res);
    void aplicarCarta(TipoCartas tipo);
    void preguntarDecisionCarta(Decision* decision);
    bool validarDecisionCarta(std::string decision);
    void imprimirMazo();
    void blindaje(Jugador* jugador);
    void radar(Jugador* jugador);
    void usoRadar(Jugador* p);
    void duplicarTesoro(Jugador* jugador);
    void palaTunel(Jugador* jugador);
    void agentesDurmientes(Jugador* jugador);
    void racimoBomba(Jugador* jugador);
    
    //Fichas
    std::string getFichaTipoGlobal(TipoFichas tipo);
    void handlerCoordenadaFicha(Coordenada* aux, TipoFichas tipoSrc);
    void handlerFicha(TipoFichas tipoSrc);
    bool validarNumeroFicha(int index);
    void preguntarCoordenada(Coordenada* pos);
    bool distanciaContigua(Coordenada* c1, Coordenada* c2);
    void colocarFicha(TipoFichas tipo, Coordenada* pos);
    void colocarFichaN(TipoFichas tipo, Coordenada* pos, int jugadorNuevo);
    void seleccionarTesoro(int* fichaSeleccionada, Coordenada* auxSrc, Coordenada* auxDest);
    void imprimirFichas();
    void handlerMina(TipoFichas tipoDest, Coordenada* aux, bool* loopCheck);
    void handlerEspia(TipoFichas tipoDest, Coordenada* aux, bool* loopCheck);
    void handlerTesoro(bool* loopCheck);
    
    //Otro
    void mostrarAlertas(std::string alerta, Jugador* jugadorActual);
    void limpiarArchivo(Jugador* jugadorActual);
    void sacarFoto();

};



/*
Carta Radar: Para implementar el efecto de esta carta, necesitarás: 
una forma de buscar en el tablero las fichas que están a una distancia de 3 casillas de una posición dada. 
Esto podría hacerse con un método en la clase Tablero que devuelva una lista de todas las fichas dentro de ese rango. 
Luego, en el método aplicarEfecto de la clase Carta, puedes llamar a este método y mostrar al jugador las fichas encontradas.

Carta Duplicar Tesoro: Para implementar esta carta, puedes: 
añadir un método en la clase Jugador que duplique una de sus fichas de tesoro. 
En el método aplicarEfecto de la clase Carta, puedes llamar a este método.

Para ambas cartas, necesitarás: 
añadir los nuevos tipos de cartas al enum TipoCartas y modificar el método aplicarEfecto de la clase Carta para manejar estos nuevos tipos.

Espero que esto te ayude a implementar las nuevas cartas. ¡Buena suerte con tu proyecto! 😊
*/

#endif