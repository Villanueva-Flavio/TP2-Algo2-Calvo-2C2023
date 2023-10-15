#include <string>
#include "Coordenada.h"

class {
public:
    Juego();
    void iniciarJuego();

    void jugar();
private:
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
    
    //Mina
    void colocarMina();
    void preguntarPosicionMina(Coordenada* Pos);
    void handlerMina(Coordenada pos);//Redundante?

    //Espia
    void colocarEspia();
    void preguntarPosicionEspia(Coordenada* Pos);
    void handlerEspia(Coordenada pos);//Redundante?

    //Tesoro
    void moverTesoro();
    void preguntarTesoro(int* index);
    void preguntarPosicionTesoro(Coordenada* Pos);
    void handlerTesoro(Coordenada pos);//Redundante?
}