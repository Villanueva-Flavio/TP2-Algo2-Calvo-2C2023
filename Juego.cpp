#include "./Headers/Juego.h"
#include <string>
#include "./Headers/Enums.h"

using namespace std;

Juego::Juego(int jugadores){
    int size = jugadores * 4;
    this->jugadores = new Lista<Jugador*>();
    this->tablero = new Tablero<Ficha*>(size, size, size);
    this->estadoPartida = 0;
    this->iniciarJuego(jugadores);
}

void Juego::iniciarJuego(int jugadores){
    this->cargarTablero();
    this->cargarJugadores(jugadores);
}

void Juego::jugar(){
    while(this->estadoPartida == 0){
        this->jugarTurno();
    }
}

int Juego::mostrarEstadoPartida(){
    return this->estadoPartida;
}

Juego::~Juego(){
    delete this->jugadores;
    delete this->tablero;
}

//Iniciar juego

string Juego::preguntarNombre(){
    string nombre;
    cout << "Ingrese el nombre del jugador: ";
    cin >> nombre;
    while(!this->validarNombre(nombre)){
        cout << "Nombre invalido, ingrese otro: ";
        cin >> nombre;
    }
    return nombre;
}

void Juego::cargarJugadores(int jugadores){
    for(int i = 0; i < jugadores; i ++){
        this->jugadores->add(new Jugador(this->preguntarNombre()));
        for(int j = 0; j < 4; j ++){
            this->cargarTesoros();
        }
    }
}

void Juego::cargarTesoros(){
    Coordenada* aux = new Coordenada(0, 0, 0);
    for(int i = 0; i < 4; i++){
        cout << "Jugador " << this->jugadores->getLData(this->jugadores->getSize() - 1)->getNombre() << endl;
        cout << "Ingrese la coordenada en el formato X Y Z del tesoro: ";
        cin >> *aux;
        cout << endl;
        while(!this->validarLimitePosicion(*aux)){
            cout << "Coordenada invalida, ingrese otra: ";
            cin >> *aux;
            cout << endl;
        }
        this->tablero->getTData(*aux)->setTipo(TESORO);
    }
}

bool Juego::validarNombre(string nombre){
    return nombre.length() > 0 || nombre.length() < 20;
}

bool Juego::coordenadaValida(Coordenada pos){
    bool resultado = true;
    if(this->tablero->getTData(pos)->getTipo() == TESORO){
        resultado = false;
    }
}

bool Juego::validarLimitePosicion(Coordenada pos){
    int size = this->tablero->getTamanioX();
    return 
    pos.getX() >= 0   && 
    pos.getX() < size && 
    pos.getY() >= 0   && 
    pos.getY() < size && 
    pos.getZ() >= 0   && 
    pos.getZ() < size;
}

void Juego::handlerCarta(){
    Decision decision = NINGUNA;
    this->preguntarDecisionCarta(&decision);
    if(decision == SI){
        this->jugarCartaRecibida();
    } else if (decision == NO){
        this->guardarCarta();
    } else if (decision == SALIR){
        this->estadoPartida = -1;
    }
}

void Juego::jugarCarta(int indice){
    Mazo* mazo = this->jugadores->getLData(this->jugadores->getIter())->getMazo();
    TipoCartas tipo = mazo->obtenerMazo()->getLData(indice)->getTipo();
    mazo->usarCarta(tipo);
}

void Juego::jugarCartaDelMazo(){
    int index = this->jugadores->getLData(this->jugadores->getIter())->getMazo()->obtenerMazo()->getSize();
    int aux = 0;
    cout << "Ingrese el numero de la carta que desea jugar: ";
    cin >> aux;
    while(aux > index || aux < 0){
        cout << "Numero de carta invalido, ingrese otro: ";
        cin >> aux;
    }
    this->jugarCarta(aux);
}

void Juego::handlerMazo(){
    Decision decision = NINGUNA;
    this->preguntarDecisionMazo(&decision);
    if(decision == SI){
        this->jugadores->getLData(this->jugadores->getIter())->getMazo()->imprimirMazo(this->jugadores->getLData(this->jugadores->getIter())->getNombre());
        this->jugarCartaDelMazo();
    } else if (decision == SALIR){
        this->estadoPartida = -1;
    }
}

void Juego::jugarTurno(){
    Decision decision = NINGUNA;
    for(int i = 0; i < this->jugadores->getSize(); i++){
        if(this->estadoPartida == 0){
            this->mostrarTablero();
            this->recibirCarta();
            this->handlerCarta();
            this->handlerMazo();           

        }
    }
}