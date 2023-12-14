#include "Juego.h"
#include "Renderizador.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

using namespace std;

string IntToString(int a){
    ostringstream temp;
    temp << a;
    return temp.str();
}


Juego::Juego(int jugadores){
    int size = jugadores * 4;
    this->jugadores = new Lista<Jugador*>();
    this->tablero = new Tablero<Ficha*>(size, size, size);
    this->inactivas = new Lista<Ficha*>();
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
    if(this->estadoPartida > 0){
        cout << "El jugador " << this->jugadores->getLData(this->estadoPartida -1)->getNombre() << " ha ganado la partida" << endl;
    }
}

int Juego::mostrarEstadoPartida(){
    return this->estadoPartida;
}

Juego::~Juego(){
    delete this->jugadores;
    delete this->tablero;
    delete this->inactivas;
}

//Iniciar juego

string Juego::preguntarNombre(){
    string nombre;
    cout << COLOR_VERDE_NEGRITA << "Ingrese el nombre del jugador: " << COLOR_ROJO_NEGRITA;
    cin >> nombre;
    cout << RES_COLOR;
    while(!this->validarNombre(nombre)){
        cout << COLOR_ROJO_NEGRITA << "Nombre invalido, ingrese otro: " << COLOR_VERDE;
        cin >> nombre;
        cout << RES_COLOR;
    }
    return nombre;
}

void Juego::cargarJugadores(int jugadores){
    for(int i = 0; i < jugadores; i ++){
        cout << COLOR_ROJO << "Jugador " << i + 1 << endl << RES_COLOR ;
        std::string nombre = this->preguntarNombre();
        Jugador* jugador = new Jugador(nombre);
        this->jugadores->add(jugador);
        system("clear");
        this->cargarTesoros();
    }
}

void Juego::cargarTesoros(){
    Coordenada* aux = new Coordenada(0, 0, 0);
    cout << "Jugador " << this->jugadores->getLData(this->jugadores->getSize() - 1)->getNombre() << endl;
        cout << COLOR_VERDE_NEGRITA << "Tamaño de mapa: 1 a " << this->tablero->getTamanioX() << RES_COLOR << endl;
    for(int i = 0; i < 4; i++){    
        cout << "Ingrese la coordenada en el formato X Y Z del tesoro ( " << i+1 << "/4 ): ";
        cin >> *aux;
        cout << endl;
        (*aux) = (*aux) - 1;
        while(!this->validarLimitePosicion(aux) || !this->coordenadaValida(aux)){
            cout << COLOR_ROJO_NEGRITA << "Coordenada invalida, ingrese otra: " << RES_COLOR;
            cin >> *aux;
            cout << endl;
            (*aux) = (*aux) - 1;
        }
        this->tablero->getTDataC(aux)->setTipo(TESORO);
        this->tablero->getTDataC(aux)->setJugadorOwner(this->jugadores->getSize() - 1);
        this->jugadores->getLData(this->jugadores->getIter())->getListaFichas()->add(this->tablero->getTDataC(aux));
    }
    system("clear");
    delete aux; //REMINDER
}

bool Juego::validarNombre(string nombre){
    return nombre.length() > 0 || nombre.length() < 20;
}

bool Juego::coordenadaValida(Coordenada* pos){
    return (this->tablero->getTDataC(pos)->getTipo() != TESORO);
}

bool Juego::validarLimitePosicion(Coordenada* pos){
    return this->tablero->inRange(pos->getX(), pos->getY(), pos->getZ());
}

//   JJJJJJJ     UU    UU     EEEEEEEEE     GGGGGGGG      OOOOOOOO
//        JJ     UU    UU     EE           GG            OO      OO
//        JJ     UU    UU     EEEE         GG   GGG      OO      OO
//   JJ   JJ     UU    UU     EE           GG     GG     OO      OO
//   JJJJJ        UUUUUU      EEEEEEEEE     GGGGGGG       OOOOOOOO

bool Juego::validarDecisionCarta(string decision){
    return decision == "si" || decision == "no" || decision == "salir";
}

void Juego::preguntarDecisionCarta(Decision* decision){
    string aux;
    cout << COLOR_VERDE << "Desea jugar la carta? (si/no/salir): " << RES_COLOR;
    cin >> aux;
    while(!this->validarDecisionCarta(aux)){
        cout << COLOR_ROJO_NEGRITA << "Decision invalida, ingrese otra: " << RES_COLOR;
        cin >> aux;
    }
    if(aux == "si"){
        *decision = SI;
    } else if (aux == "no"){
        *decision = NO;
    } else if (aux == "salir"){
        *decision = SALIR;
        this->estadoPartida = -1;
    }
    system("clear");
}

/*=============================================================CARTAS============================================================================================*/

void Juego::blindaje(Jugador* jugador){
    int len = jugador->getLenFichas();
    for(int x = 0; x < len; x++){
        //suponiendo que solo se almacenen tesoros y espias.
        jugador->getListaFichas()->getLData(x)->setProtegido(true);
    }
}
/*RADAR:
*/

//x, y, z son las coordenadas donde se colocara el radar
void Juego::radar(Jugador* player){
    Coordenada* pos = new Coordenada(0,0,0);
    preguntarCoordenada(pos);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                Ficha* fichaActual = this->tablero->getTData(i, j, k);
                if(this->tablero->inRange(i, j, k) && fichaActual->getTipo() != VACIO && fichaActual->getJugadorOwner() != this->jugadores->getIter()){
                    string alerta = "Se ha encontrado una ficha " + this->getFichaTipoGlobal(fichaActual->getTipo()) + " en la posicion " + IntToString(i) + " " + IntToString(j) + " " + IntToString(k) + "\n";
                    this->mostrarAlertas(alerta, this->jugadores->getLData(this->jugadores->getIter()));
                } 
            }
        }
    }
    delete pos;
}

//Hace radar sobre todos los jugadores menos quien la usa.
void Juego::usoRadar(Jugador* p){
    for(int x = 0; x < jugadores->getSize(); x++){
        if(p->getNombre() != this->jugadores->getLData(x)->getNombre()){
            radar(this->jugadores->getLData(x));
        }
    }
}
/*END.
*/
//las coordenadas que se ingresan son donde se piensa colocar el tesoro.
void Juego::duplicarTesoro(Jugador* jugador){
    Coordenada* pos = new Coordenada(0,0,0);
    do{
        cout << "Ingrese las coordenadas donde desea colocar el tesoro: ";
        preguntarCoordenada(pos);
    }while(!this->coordenadaValida(pos));
    colocarFicha(TESORO, pos);
    delete pos;
}

void Juego::palaTunel(Jugador* jugador){
    Coordenada* pos = new Coordenada(0, 0, 0);
    Coordenada* aux = new Coordenada(0, 0, 0);
    this->imprimirFichas();
    do{
        cout << "Ingrese las coordenadas de la ficha que desea mover: ";
        preguntarCoordenada(pos);  
    } while(coordenadaValida(pos));
    
    do{
        cout << "Ingrese las coordenadas donde desea colocar la ficha: ";
        preguntarCoordenada(aux);
    } while(!coordenadaValida(aux));

    colocarFichaN(this->tablero->getTDataC(pos)->getTipo(), aux, this->jugadores->getIter());
    colocarFichaN(VACIO, pos, -1);
    delete aux, pos;
}

void Juego::agentesDurmientes(Jugador* jugador){
    for(int x = 0; x < this->jugadores->getSize(); x++){
        if(jugador->getNombre() != this->jugadores->getLData(x)->getNombre()){
            this->jugadores->getLData(x)->getListaFichas()->getLData(x)->setTurnosInactiva(1);  
        }
    }
}

void Juego::racimoBomba(Jugador* jugador){
    Coordenada* pos = new Coordenada(0, 0, 0);
    for(int mina = 0; mina < 5; mina++){
        cout << COLOR_VERDE << "Ingrese la posicion donde desea colocar la mina" << RES_COLOR << endl;
        preguntarCoordenada(pos);
        while((this->tablero->getTDataC(pos)->getTipo() != VACIO) || (!this->validarLimitePosicion(pos))){
            cout << COLOR_ROJO_NEGRITA << "Coordenada incorrecta." << RES_COLOR << endl;
            preguntarCoordenada(pos);
        }
        colocarFicha(MINA, pos);
    }
    delete pos; //REMINDER
}

void Juego::aplicarCarta(TipoCartas tipo){
    switch(tipo){
        case BLINDAJE:
            this->blindaje(this->jugadores->getLData(this->jugadores->getIter()));
            break;
        case RADAR:
            this->usoRadar(this->jugadores->getLData(this->jugadores->getIter()));
            break;
        case PARTIR_TESORO:
            this->duplicarTesoro(this->jugadores->getLData(this->jugadores->getIter()));
            break;
        case PALA_PARA_TUNEL:
            this->palaTunel(this->jugadores->getLData(this->jugadores->getIter()));
            break;
        case AGENTES_DURMIENTES:
            this->agentesDurmientes(this->jugadores->getLData(this->jugadores->getIter()));
            break;
        case BOMBA_DE_RACIMO:
            racimoBomba(this->jugadores->getLData(this->jugadores->getIter()));
            break;
    }
}

void Juego::handlerCarta(int res){
    Decision decision = NINGUNA;
    if(this->estadoPartida != -1){
        this->preguntarDecisionCarta(&decision);
        if(decision == SI){
            this->jugadores->getLData(this->jugadores->getIter())->getMazo()->usarCarta((TipoCartas)res);
            this->aplicarCarta((TipoCartas)res);
        } else if (decision == SALIR){
            this->estadoPartida = -1;
        }
    }
}

void Juego::jugarCartaDelMazo(){
    system("clear");
    int index = this->jugadores->getLData(this->jugadores->getIter())->getMazo()->obtenerMazo()->getSize();
    int aux = 0;
    cout << COLOR_VERDE << "Ingrese el numero de la carta que desea jugar o 0 si no desea ninguna: " << RES_COLOR;
    cin >> aux;
    aux--;
    cout << "Elegiste " << aux << "Con index: " << index << endl;
    while(aux >= index || aux < -1){
        cout << COLOR_ROJO_NEGRITA << "Numero de carta invalido, ingrese otro: " << RES_COLOR;
        cin >> aux;
        aux--;
    }
    if(aux != -1){
        this->jugadores->getLData(this->jugadores->getIter())->getMazo()->usarCarta((TipoCartas)aux);
        this->aplicarCarta((TipoCartas)aux);
    }
}


void Juego::preguntarDecisionMazo(Decision* decision){
    string aux;
    cout << COLOR_VERDE << "Desea ver el mazo? (si/no/salir): " << RES_COLOR;
    cin >> aux;
    while(!this->validarDecisionCarta(aux)){
        cout << COLOR_ROJO_NEGRITA << "Decision invalida, ingrese otra: " << RES_COLOR;
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

void Juego::imprimirMazo(){
    Jugador* jugador = this->jugadores->getLData(this->jugadores->getIter());
    string alerta;
    for(int i = 0; i < 6; i++){
        string cantidad = IntToString(jugador->getMazo()->obtenerCantidadCartas((TipoCartas)i));
        alerta = jugador->getMazo()->tipoDeCartaGlobal((TipoCartas)i) + ": " + cantidad + "\n";
        this->mostrarAlertas(alerta, jugador);
    }
}

void Juego::handlerMazo(){
    Decision decision = NINGUNA;
    if(estadoPartida != -1){
        this->preguntarDecisionMazo(&decision);
        if(decision == SI){
            this->imprimirMazo();
            this->jugarCartaDelMazo();
        } else if (decision == SALIR){
            this->estadoPartida = -1;
        }
    }
}

void Juego::recibirCarta(int* res){
    TipoCartas rng = (TipoCartas) (rand() % 6);
    *res = (int)rng;
    Mazo* mazoActual = this->jugadores->getLData(this->jugadores->getIter())->getMazo();
    mazoActual->agregarCarta(rng);
    cout << COLOR_VERDE_NEGRITA << "Se ha recibido la carta: " << mazoActual->tipoDeCartaGlobal(mazoActual->obtenerCarta(rng)->getTipo()) << RES_COLOR << endl;
}

string Juego::getFichaTipoGlobal(TipoFichas tipo){
    switch (tipo){
        case MINA:
            return "mina";
        case TESORO:
            return "tesoro";
        case ESPIA:
            return "espia";
        case TESORO_DESENTERRADO:
            return "tesoro desenterrado";
        case INACTIVO:
            return "inactivo";
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
        cout << COLOR_ROJO_NEGRITA << "Exception: No players left" << RES_COLOR << endl;
        this->estadoPartida == -1;
    }
}

void Juego::preguntarCoordenada(Coordenada* pos){
    cout << COLOR_VERDE_NEGRITA << "Tamaño de mapa: 1 a " << this->tablero->getTamanioX() << RES_COLOR << endl;
    cout << "Ingrese la coordenada en el formato X Y Z: ";
    cin >> *pos;
    (*pos) = (*pos) - 1;
    while(!this->validarLimitePosicion(pos)){
        cout << COLOR_ROJO_NEGRITA << "Coordenada invalida, ingrese otra: " << RES_COLOR;
        cin >> *pos;
        (*pos) = (*pos) - 1;
    }
}

void Juego::colocarFicha(TipoFichas tipo, Coordenada* pos){
    this->tablero->getTDataC(pos)->setTipo(tipo);
}

void Juego::colocarFichaN(TipoFichas tipo, Coordenada* pos, int jugadorNuevo){
    this->tablero->getTDataC(pos)->setTipo(tipo);
    this->tablero->getTDataC(pos)->setJugadorOwner(jugadorNuevo);
}

void Juego::handlerMina(TipoFichas tipoDest, Coordenada* aux, bool* loopCheck){
    int jugadorActual = this->jugadores->getIter();
    int jugadorDest = this->tablero->getTDataC(aux)->getJugadorOwner();
    switch(tipoDest){
        case MINA:
            this->mostrarAlertas("No se puede colocar una mina sobre otra mina\n", this->jugadores->getLData(jugadorActual));
            break;

        case TESORO:
        case TESORO_DESENTERRADO:
            if(jugadorActual != jugadorDest){
                this->mostrarAlertas("Tesoro encontrado, desenterrando\n", this->jugadores->getLData(jugadorActual));
                this->colocarFicha(TESORO_DESENTERRADO, aux);
                *loopCheck = true;
                break;
            }
            this->mostrarAlertas("No se puede atacar un tesoro propio\n", this->jugadores->getLData(jugadorActual));
            break;

        case ESPIA:
            if(jugadorActual != jugadorDest){
                this->mostrarAlertas("Espia eliminado\n", this->jugadores->getLData(jugadorActual));
                this->colocarFichaN(VACIO, aux, 0);
                *loopCheck = true;
                break;
            }
            this->mostrarAlertas("No se puede atacar un espia propio\n", this->jugadores->getLData(jugadorActual));
            break;

        case VACIO:
            this->colocarFichaN(MINA, aux, this->jugadores->getIter());
            *loopCheck = true;
            break;
    }
}

void Juego::handlerEspia(TipoFichas tipoDest, Coordenada* aux, bool* loopCheck){
    int jugadorActual = this->jugadores->getIter();
    int jugadorDest = this->tablero->getTDataC(aux)->getJugadorOwner();
    switch(tipoDest){
        case MINA:
            if(jugadorActual != jugadorDest){
                this->mostrarAlertas("Espia perdido en una mina\n", this->jugadores->getLData(jugadorActual));
                this->colocarFichaN(VACIO, aux, 0);
                *loopCheck = true;
                break;
            }
            this->mostrarAlertas("El espia pisaria tu propia mina\n", this->jugadores->getLData(jugadorActual));
            break;

        case TESORO:
        case TESORO_DESENTERRADO:
            if(this->tablero->getTDataC(aux)->getJugadorOwner() != this->jugadores->getIter()){
                this->mostrarAlertas("Tesoro encontrado, desenterrando\n", this->jugadores->getLData(jugadorActual));
                this->colocarFicha(TESORO_DESENTERRADO, aux);
                *loopCheck = true;
                break;
            }
            this->mostrarAlertas("No se puede atacar un tesoro propio\n", this->jugadores->getLData(jugadorActual));
            break;

        case ESPIA:
            if(jugadorActual != jugadorDest){
                this->mostrarAlertas("Espia eliminado\n", this->jugadores->getLData(jugadorActual));
                this->colocarFichaN(VACIO, aux, 0);
                *loopCheck = true;
                break;
            }
            this->mostrarAlertas("No se puede atacar un espia propio\n", this->jugadores->getLData(jugadorActual));
            break;

        case VACIO:
            this->colocarFichaN(ESPIA, aux, this->jugadores->getIter());
            *loopCheck = true;
            break;
    }
}

void Juego::imprimirFichas(){
    Jugador* jugadorActual = this->jugadores->getLData(this->jugadores->getIter());
    string alerta;
    for(int i = 0; i < jugadorActual->getLenFichas(); i++){
        Ficha* ficha = jugadorActual->getListaFichas()->getLData(i);
        string tipo = this->getFichaTipoGlobal(ficha->getTipo());
        cout << COLOR_BLANCO << "Ficha " << i + 1 << ": " << tipo << " en " << ficha->getPosicion() + 1 << RES_COLOR << endl;
    }

}

bool Juego::validarNumeroFicha(int index){
    return index >= 0 && index < this->jugadores->getLData(this->jugadores->getIter())->getTesorosRestantes();
}

bool Juego::distanciaContigua(Coordenada* c1, Coordenada* c2){
    int x = c1->getX() - c2->getX();
    int y = c1->getY() - c2->getY();
    int z = c1->getZ() - c2->getZ();
    return (x >= -1 && x <= 1 && y >= -1 && y <= 1 && z >= -1 && z <= 1);
}

void Juego::seleccionarTesoro(int* fichaSeleccionada, Coordenada* auxSrc, Coordenada* auxDest){
    this->imprimirFichas();
    cout << COLOR_VERDE << "Ingrese el numero de la ficha que desea seleccionar: " << RES_COLOR;
    cin >> *fichaSeleccionada;
    (*fichaSeleccionada) --;
    while(!this->validarNumeroFicha(*fichaSeleccionada)){
        cout << COLOR_ROJO_NEGRITA << "Numero de ficha invalido, ingrese otro: " << RES_COLOR;
        cin >> *fichaSeleccionada;
        (*fichaSeleccionada) --;
    }
    *auxSrc = this->jugadores->getLData(this->jugadores->getIter())->getListaFichas()->getLData(*fichaSeleccionada)->getPosicion();
    system("clear");
    preguntarCoordenada(auxDest);
    while(!distanciaContigua(auxSrc, auxDest)){
        cout << COLOR_ROJO_NEGRITA << "Las coordenadas no son contiguas a: " << (*auxSrc) + 1 <<", ingrese otras: " << RES_COLOR;
        preguntarCoordenada(auxDest);
    }
}

void Juego::handlerTesoro(bool* loopCheck){
    Coordenada* auxDest = new Coordenada(0, 0, 0);
    Coordenada* auxSrc = new Coordenada(0, 0, 0);
    int fichaSeleccionada = 0;
    this->seleccionarTesoro(&fichaSeleccionada, auxSrc, auxDest);
    int jugadorActual = this->jugadores->getIter();
    int jugadorDest = this->tablero->getTDataC(auxDest)->getJugadorOwner();
    TipoFichas tipoDest = this->tablero->getTDataC(auxDest)->getTipo();
    switch(tipoDest){
        case MINA:
            if(jugadorActual != jugadorDest){
                cout << COLOR_ROJO << "Moviste el tesoro sobre una mina, queda desenterrado" << RES_COLOR << endl;
                this->colocarFichaN(TESORO_DESENTERRADO, auxDest, jugadorActual);
                this->colocarFichaN(VACIO, auxSrc, 0);
                this->jugadores->getLData(jugadorDest)->getListaFichas()->getLData(fichaSeleccionada)->setPosicion(*auxDest);
                *loopCheck = true;
                break;
            }
            cout << COLOR_ROJO << "No podes llevar un tesoro propio sobre una mina propia" << RES_COLOR << endl;
            break;

        case TESORO:
            cout << COLOR_AMARILLO << "Hay un tesoro en esa ubicación" << RES_COLOR << endl;
            break;

        case ESPIA:
            if(jugadorActual != jugadorDest){
                cout << COLOR_ROJO << "Un espía encontro un tesoro" << RES_COLOR << endl;
                this->colocarFichaN(VACIO, auxDest, 0);
                this->colocarFichaN(VACIO, auxSrc, 0);
                this->jugadores->getLData(jugadorDest)->getListaFichas()->remove(fichaSeleccionada);
                *loopCheck = true;
                break;
            }
            cout << COLOR_ROJO << "No se puede superponer tu espía con tu tesoro" << RES_COLOR << endl;
            break;

        case VACIO:
            this->colocarFichaN(TESORO, auxDest, jugadorActual);
            this->colocarFichaN(VACIO, auxSrc, 0);
            this->jugadores->getLData(jugadorDest)->getListaFichas()->getLData(fichaSeleccionada)->setPosicion(*auxDest);
            *loopCheck = true;
            break;
    }
    delete auxSrc;
    delete auxDest;
}

void Juego::handlerCoordenadaFicha(Coordenada* aux, TipoFichas tipoSrc){
    cout << "Ficha: " << COLOR_VERDE_NEGRITA << this->getFichaTipoGlobal(tipoSrc) << RES_COLOR << endl;
    if(tipoSrc != TESORO){
        this->preguntarCoordenada(aux);
    }
}

void Juego::handlerFicha(TipoFichas tipoSrc){
    if(this->estadoPartida != -1){
        system("clear");
        Coordenada* aux = new Coordenada(0, 0, 0);
        this->handlerCoordenadaFicha(aux, tipoSrc);
        TipoFichas tipoDest = this->tablero->getTDataC(aux)->getTipo();
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
                case TESORO_DESENTERRADO:
                    handlerTesoro(&loopCheck);
                    break;
            }
            if(!loopCheck){
                system("clear");
                cout << COLOR_ROJO << "Reintentá nuevamente" << RES_COLOR << endl;
                this->handlerCoordenadaFicha(aux, tipoSrc);
                tipoDest = this->tablero->getTDataC(aux)->getTipo();
            }
        }
        delete aux;
    }
}

bool Juego::crearDirectorio(const char* path) {
    #ifdef _WIN32
    return _mkdir(path) == 0;
    #else
    return system(("mkdir -p " + std::string(path)).c_str()) == 0;
    #endif
}

void Juego::mostrarAlertas(string alerta, Jugador* jugadorActual){
    string fileName = "Partida/Alertas_" + jugadorActual->getNombre() + ".txt";
    if(!this->crearDirectorio("Partida")){
        cout << COLOR_ROJO_NEGRITA << "Error al crear el directorio" << RES_COLOR << endl;
        exit(1);
    }
    FILE* archivo = fopen(fileName.c_str(), "a");
    if(archivo != nullptr){
        fprintf(archivo, "%s\n", alerta.c_str());
        fclose(archivo);
    } else {
        cout << COLOR_ROJO_NEGRITA << "Error al abrir el archivo" << RES_COLOR << endl;
        exit(1);
    }
}

void Juego::limpiarArchivo(Jugador* jugadorActual){
    string fileName = "Partida/Alertas_" + jugadorActual->getNombre() + ".txt";
    FILE* archivo = fopen(fileName.c_str(), "w");
    fclose(archivo);
}


void Juego::sacarFoto(){
    Jugador* jugadorActual = this->jugadores->getLData(this->jugadores->getIter());
    Coordenada* imgSize = new Coordenada(this->tablero->getTamanioX() * 100, this->tablero->getTamanioY() * 70, 0);
    BMP* imagen = new BMP();
    imagen->SetSize(imgSize->getX(), imgSize->getY());
    imprimirBMP(imgSize, imagen, this->tablero, this->jugadores->getIter());
    string fileName = "Partida/Tablero_" + jugadorActual->getNombre() + ".bmp";
    if(this->crearDirectorio("Partida")){
        imagen->WriteToFile(fileName.c_str());
    } else {
        cout << COLOR_ROJO_NEGRITA << "Error al crear el directorio" << RES_COLOR << endl;
        exit(1);
    }
    delete imagen;
    delete imgSize;    
}

void Juego::jugarTurno(){
    int res;
    for(int i = 0; i < this->jugadores->getSize(); i++){
        this->jugadores->goTo(i);
        if(this->estadoPartida == 0 && this->jugadores->getLData(i)->getTesorosRestantes() > 0){
            this->sacarFoto();
            this->limpiarArchivo(this->jugadores->getLData(i));
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