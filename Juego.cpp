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

void Juego::cargarTablero(){
    for(int i = 0; i < this->tablero->getTamanioX(); i++){
        for(int j = 0; j < this->tablero->getTamanioY(); j++){
            for(int k = 0; k < this->tablero->getTamanioZ(); k++){
                this->tablero->getTData(i, j, k)->setTipo(VACIO);
            }
        }
    }
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





//   JJJJJJJ     UU    UU     EEEEEEEEE    GGGGGGGGG      OOOOOOOO
//        JJ     UU    UU     EE           GG            OO      OO
//        JJ     UU    UU     EEEE         GG   GGGG     OO      OO
//   JJ   JJ     UU    UU     EE           GG     GG     OO      OO
//   JJJJJ        UUUUUU      EEEEEEEEE     GGGGGGGG      OOOOOOOO


bool Juego::validarDecisionCarta(string decision){
    return decision == "si" || decision == "no" || decision == "salir";
}

void Juego::handlerCarta(int res){
    Decision decision = NINGUNA;
    this->preguntarDecisionCarta(&decision);
    if(decision == SI){
        this->jugarCarta(res);
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


void Juego::preguntarDecisionMazo(Decision* decision){
    string aux;
    cout << "Desea ver el mazo? (si/no/salir): ";
    cin >> aux;
    while(!this->validarDecisionCarta(aux)){
        cout << "Decision invalida, ingrese otra: ";
        cin >> aux;
    }
    if(aux == "si"){
        *decision = SI;
    } else if (aux == "no"){
        *decision = NO;
    } else if (aux == "salir"){
        *decision = SALIR;
    }
}

void Juego::handlerMazo(){
    Jugador* jugadorActual = this->jugadores->getLData(this->jugadores->getIter());
    Decision decision = NINGUNA;
    this->preguntarDecisionMazo(&decision);
    if(decision == SI){
        jugadorActual->getMazo()->imprimirMazo(jugadorActual->getNombre());
        this->jugarCartaDelMazo();
    } else if (decision == SALIR){
        this->estadoPartida = -1;
    }
}

void Juego::recibirCarta(int* res){
    TipoCartas rng = (TipoCartas) (rand() % 6);
    *res = (int)rng;
    Jugador* jugadorActual = this->jugadores->getLData(this->jugadores->getIter());
    jugadorActual->getMazo()->agregarCarta(rng);
    cout << "Se ha recibido la carta: " << jugadorActual->getMazo()->obtenerCarta(rng)->getTipo() << endl;
}

void Juego::mostrarTablero(){
    cout << "ToDo tablero" << endl;
}

string Juego::getFichaTipoGlobal(TipoFichas tipo){
    switch (tipo){
        case MINA:
            return "mina";
        case TESORO:
            return "tesoro";
        case ESPIA:
            return "espia";
        default:
            return "vacio";
    }
}

void Juego::checkEstadoPartida(){
    int jugadoresVivos = 0;
    int ultimoJugadorVivo = 1;
    if(this->estadoPartida == 0){
        for(int i = 0; i < this->jugadores->getSize(); i++){
            if(this->jugadores->getLData(i)->getTesorosRestantes() > 0){
                jugadoresVivos++;
                ultimoJugadorVivo = i+1;
            }
        }
    }

    if(jugadoresVivos == 1){
        this->estadoPartida == ultimoJugadorVivo;
    }

    if(jugadoresVivos == 0){
        cout << "Exception: No players left" << endl;
        this->estadoPartida == -1;
    }
}

void Juego::preguntarCoordenada(Coordenada* pos){
    cout << "Ingrese la coordenada en el formato X Y Z: ";
    cin >> *pos;
    while(!this->validarLimitePosicion(*pos)){
        cout << "Coordenada invalida, ingrese otra: ";
        cin >> *pos;
    }
}

void Juego::colocarFicha(TipoFichas tipo, Coordenada* pos){
    this->tablero->getTData(*pos)->setTipo(tipo);
}

void Juego::colocarFicha(TipoFichas tipo, Coordenada* pos, int jugadorNuevo){
    this->tablero->getTData(*pos)->setTipo(tipo);
    this->tablero->getTData(*pos)->setJugadorOwner(jugadorNuevo);
}

void Juego::handlerMina(TipoFichas tipoDest, Coordenada* aux, bool* loopCheck){
    int jugadorActual = this->jugadores->getIter();
    int jugadorDest = this->tablero->getTData(*aux)->getJugadorOwner();
    switch(tipoDest){
        case MINA:
            cout << "No se puede colocar una mina sobre otra mina" << endl;
            break;

        case TESORO:
            if(jugadorActual != jugadorDest){
                cout << "Tesoro encontrado, desenterrando" << endl;
                this->colocarFicha(TESORO_DESENTERRADO, aux);
                *loopCheck = true;
                break;
            } 
            cout << "No se puede atacar un tesoro propio" << endl;
            break;

        case ESPIA:
            if(jugadorActual != jugadorDest){
                cout << "Espia eliminado" << endl;
                this->colocarFicha(VACIO, aux, 0);
                *loopCheck = true;
                break;
            }
            cout << "No se puede atacar un espia propio" << endl;
            break;

        case VACIO:
            this->colocarFicha(MINA, aux, this->jugadores->getIter());
            *loopCheck = true;
            break;
    }
}

void Juego::handlerEspia(TipoFichas tipoDest, Coordenada* aux, bool* loopCheck){
    int jugadorActual = this->jugadores->getIter();
    int jugadorDest = this->tablero->getTData(*aux)->getJugadorOwner();
    switch(tipoDest){
        case MINA:
            if(jugadorActual != jugadorDest){
                cout << "Espía perdido en una mina" << endl;
                this->colocarFicha(VACIO, aux, 0);
                *loopCheck = true;
                break;
            }
            cout << "El espía pisaría tu propia mina" << endl;
            break;

        case TESORO:
            if(this->tablero->getTData(*aux)->getJugadorOwner() != this->jugadores->getIter()){
                cout << "Tesoro encontrado, desenterrando" << endl;
                this->colocarFicha(TESORO_DESENTERRADO, aux);
                *loopCheck = true;
                break;
            }
            cout << "No se puede atacar un tesoro propio" << endl;
            break;

        case ESPIA:
            if(jugadorActual != jugadorDest){
                cout << "Espia eliminado" << endl;
                this->colocarFicha(VACIO, aux, 0);
                *loopCheck = true;
                break;
            }
            cout << "No se puede atacar un espia propio" << endl;
            break;

        case VACIO:
            this->colocarFicha(ESPIA, aux, this->jugadores->getIter());
            *loopCheck = true;
            break;
    }
}

void Juego::imprimirFichas(){
    int i = 0;
    while(i < this->jugadores->getLData(this->jugadores->getIter())->getTesorosRestantes()){
        cout << "Ficha " << i+1 << ": ";
        for(int j = 0; j < this->tablero->getTamanioX(); j++){
            for(int k = 0; k < this->tablero->getTamanioY(); k++){
                for(int l = 0; l < this->tablero->getTamanioZ(); l++){
                    if(this->tablero->getTData(j, k, l)->getTipo() == TESORO && this->tablero->getTData(j, k, l)->getJugadorOwner() == this->jugadores->getIter()){
                        cout << j << " " << k << " " << l << endl;
                        j = this->tablero->getTamanioX();
                        k = this->tablero->getTamanioY();
                        l = this->tablero->getTamanioZ();
                        i++;
                    }
                }
            }
        }
    }
}

bool Juego::validarNumeroFicha(int index){
    return index > 0 && index <= this->jugadores->getLData(this->jugadores->getIter())->getTesorosRestantes();
}

bool Juego::distanciaContigua(Coordenada* c1, Coordenada* c2){
    int x = c1->getX() - c2->getX();
    int y = c1->getY() - c2->getY();
    int z = c1->getZ() - c2->getZ();
    return (x >= -1 && x <= 1 && y >= -1 && y <= 1 && z >= -1 && z <= 1);
}

void Juego::seleccionarTesoro(int* fichaSeleccionada, Coordenada* auxSrc, Coordenada* auxDest){
    this->imprimirFichas();
    cout << "Ingrese el numero de la ficha que desea seleccionar: ";
    cin >> *fichaSeleccionada;
    while(!this->validarNumeroFicha(*fichaSeleccionada)){
        cout << "Numero de ficha invalido, ingrese otro: ";
        cin >> *fichaSeleccionada;
    }
    preguntarCoordenada(auxSrc);
    preguntarCoordenada(auxDest);
    while(!this->distanciaContigua(auxSrc, auxDest)){
        cout << "Las coordenadas no son contiguas, ingrese otras: ";
        preguntarCoordenada(auxDest);
    }
}

void Juego::handlerTesoro(bool* loopCheck){
    Coordenada* auxSrc = new Coordenada(0, 0, 0);
    Coordenada* auxDest = new Coordenada(0, 0, 0);
    int fichaSeleccionada = 0;
    this->seleccionarTesoro(&fichaSeleccionada, auxSrc, auxDest);
    int jugadorActual = this->jugadores->getIter();
    int jugadorDest = this->tablero->getTData(*auxDest)->getJugadorOwner();
    TipoFichas tipoSrc = this->tablero->getTData(*auxSrc)->getTipo();
    TipoFichas tipoDest = this->tablero->getTData(*auxDest)->getTipo();
    switch(tipoDest){
        case MINA:
            if(jugadorActual != jugadorDest){
                cout << "Moviste el tesoro sobre una mina, queda desenterrado" << endl;
                this->colocarFicha(TESORO_DESENTERRADO, auxDest, jugadorActual);
                this->colocarFicha(VACIO, auxSrc, 0);
                *loopCheck = true;
                break;
            }
            cout << "No podes llevar un tesoro propio sobre una mina propia" << endl;
            break;

        case TESORO:
            cout << "Hay un tesoro en esa ubicación" << endl;
            break;

        case ESPIA:
            if(jugadorActual != jugadorDest){
                cout << "Un espía encontro tu tesoro" << endl;
                this->colocarFicha(VACIO, auxDest, 0);
                this->colocarFicha(VACIO, auxSrc, 0);
                *loopCheck = true;
                break;
            }
            cout << "No se puede superponer tu espía con tu tesoro" << endl;
            break;

        case VACIO:
            this->colocarFicha(tipoSrc, auxDest, jugadorActual);
            this->colocarFicha(VACIO, auxSrc, 0);
            *loopCheck = true;
            break;
    }
}

void Juego::handlerFicha(TipoFichas tipoSrc){
    Coordenada* aux = new Coordenada(0, 0, 0);
    cout << "Ficha: " << this->getFichaTipoGlobal(tipoSrc) << endl;
    if(tipoSrc != TESORO){
        this->preguntarCoordenada(aux);
    }
    TipoFichas tipoDest = this->tablero->getTData(*aux)->getTipo();
    bool loopCheck = false;
    while(!loopCheck){
        switch(tipoSrc){
            case MINA:
                handlerMina(tipoDest, aux, &loopCheck);
                break;
            case ESPIA:
                handlerEspia(tipoDest, aux, &loopCheck);
                break;
            case TESORO:
                handlerTesoro(&loopCheck);
                break;
        }
    }
    delete aux;
}

void Juego::jugarTurno(){
    Decision decision = NINGUNA;
    int res;
    for(int i = 0; i < this->jugadores->getSize(); i++){
        if(this->estadoPartida == 0 && this->jugadores->getLData(i)->getTesorosRestantes() > 0){
            this->mostrarTablero();
            this->recibirCarta(&res);
            this->handlerCarta(res);
            this->handlerMazo();
            this->handlerFicha(MINA);
            this->handlerFicha(ESPIA);
            this->handlerFicha(TESORO);
            this->checkEstadoPartida();
        }
    }
}