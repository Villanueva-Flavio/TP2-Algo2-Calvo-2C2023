#include <string>
#include "Coordenada.h"
#include "Tablero.h"
#include "Ficha.h"

class {
public:
    Juego();
    void iniciarJuego();

    void jugar();

    int mostrarEstadoPartida();

private:
    //Atributos
    Lista<Jugador*>* jugadores;
    Tablero<Ficha*>* tablero;
    int estadoPartida;


    ~Juego();
    //Iniciar juego
    void preguntarJugadores();
    void cargarTablero();
    void cargarFichas();
    void preguntarNombres();
    void cargarJugadores();

    bool validarCantidadJugadores();
    bool validarNombre(std::string nombre);
    bool coordenadaValida(Coordenada pos);
    bool validarLimitePosicion(Coordenada pos);
    
    //Jugar
    void jugarTurno();

    //Carta
    void recibirCarta();
    void preguntarDecisionCarta();
    void jugarCartaRecibida();
    void guardarCarta();
    void mostrarCartas();
    void jugarCarta(int index);

    bool validarDecisionCarta(std::string decision);
    bool validarCarta(int index);
    
    //Fichas
    void handlerFichasDelTurno(TipoFichas tipo);
    void colocarFicha(TipoFichas tipo, Coordenada* pos);
    void preguntarPosicion(TipoFichas tipo, Coordenada* pos);
    void handlerFicha(TipoFichas tipo, Coordenada pos);

    bool validarNumeroFicha(int index);

    //Otro
    void mostrarTablero(int jugador);
    void mostrarAlertas(int jugador);
    

};