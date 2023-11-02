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
    void cargarTablero(); //
    void cargarTesoros();//
    string preguntarNombre();//
    void cargarJugadores(int jugadores);//

    bool validarNombre(std::string nombre); //
    bool coordenadaValida(Coordenada pos); // De aca para abajo
    bool validarLimitePosicion(Coordenada pos);//
    
    //Jugar
    void jugarTurno();

    //Carta
    void handlerCarta();
    void handlerMazo();
    void preguntarDecisionMazo(Decision* decision);
    void jugarCartaDelMazo();


    void recibirCarta();
    void preguntarDecisionCarta(Decision* decision);
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
    void mostrarTablero();
    void mostrarAlertas();
    

};