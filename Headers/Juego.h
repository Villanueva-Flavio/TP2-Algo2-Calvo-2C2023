#include <string>
#include "Coordenada.h"
#include "Tablero.h"
#include "Ficha.h"
#include "Jugador.h"
#include "Enums.h"

class Juego{
public:
    Juego(int jugadores);
    void iniciarJuego(int jugadores);
    void jugar();
    int mostrarEstadoPartida();

private:
    //Atributos
    Lista<Jugador*>* jugadores;
    Tablero<Ficha*>* tablero;
    int estadoPartida;
    ~Juego();

    //Iniciar juego
    void cargarTablero(); 
    void cargarTesoros();
    string preguntarNombre();
    void cargarJugadores(int jugadores);
    bool validarNombre(std::string nombre);
    bool coordenadaValida(Coordenada pos);
    bool validarLimitePosicion(Coordenada pos);
    
    //Jugar
    void jugarTurno();
    void checkEstadoPartida();

    //Carta
    void handlerCarta(int res);
    void handlerMazo();
    void preguntarDecisionMazo(Decision* decision);
    void jugarCartaDelMazo();
    void recibirCarta(int* res);
    void preguntarDecisionCarta(Decision* decision);
    void jugarCarta(int index);
    bool validarDecisionCarta(std::string decision);
    void imprimirMazo();
    
    //Fichas
    std::string getFichaTipoGlobal(TipoFichas tipo);
    void colocarFicha(TipoFichas tipo, Coordenada* pos);
    void handlerFicha(TipoFichas tipoSrc);
    bool validarNumeroFicha(int index);
    void preguntarCoordenada(Coordenada* pos);
    bool distanciaContigua(Coordenada* c1, Coordenada* c2);
    void colocarFicha(TipoFichas tipo, Coordenada* pos);
    void colocarFicha(TipoFichas tipo, Coordenada* pos, int jugadorNuevo);
    void seleccionarTesoro(int* fichaSeleccionada, Coordenada* auxSrc, Coordenada* auxDest);
    void imprimirFichas();
    void handlerMina(TipoFichas tipoDest, Coordenada* aux, bool* loopCheck);
    void handlerEspia(TipoFichas tipoDest, Coordenada* aux, bool* loopCheck);
    void handlerTesoro(bool* loopCheck);
    
    //Otro
    void mostrarTablero();
    void mostrarAlertas(std::string alerta, Jugador* jugadorActual);
    void limpiarArchivo(Jugador* jugadorActual);
    

};