#include "./Headers/Juego.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include "./Headers/Enums.h"
#include "./Headers/Renderizador.h"

using namespace std;

string IntToString(int a)
{
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
    this->~Juego();
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
        while(!this->validarLimitePosicion(aux)){
            cout << "Coordenada invalida, ingrese otra: ";
            cin >> *aux;
            cout << endl;
        }
        this->tablero->getTDataC(aux)->setTipo(TESORO);
    }
}

bool Juego::validarNombre(string nombre){
    return nombre.length() > 0 || nombre.length() < 20;
}

bool Juego::coordenadaValida(Coordenada* pos){
    bool resultado = true;
    if(this->tablero->getTDataC(pos)->getTipo() == TESORO){
        resultado = false;
    }
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
    cout << "Desea jugar la carta? (si/no/salir): ";
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

/*=============================================================CARTAS============================================================================================*/

/*ABOMINACION EN PROCESO*/

void Juego::radar(int x, int y, int z){
    while (!this->tablero->inRange(x,y,z))
    {
        //se hace aca si no esta en rango.
    }
    int casillaX = tablero->getTamanioX();
    int casillaY = tablero->getTamanioY();
    int casillaZ = tablero->getTamanioZ();
    
    int realX = x - casillaX;   //resta la coordenada actual con el borde del tablero
    int realY = y - casillaY;
    int realZ = z - casillaZ;

    if((realX >= 3) && (realY >= 3) && (realZ >= 3)){
        //incluyendo hasta el borde.
        Ficha* casillaActual = tablero->getTData(x,y,z);
        //ver si la condicion es menor o menor o igual
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    if((casillaActual->getTipo() == TESORO) && (!casillaActual->estaProtegido())){
                        cout << "HAY UN TESORO EN LAS COORDENADAS: " << x << " " << y << " " << z << " " << endl;
                    }
                }
            }
        }
    }
    else if (realX < 3){
        Ficha* casillaActual = tablero->getTData(x,y,z);
        //ver si la condicion es menor o menor o igual
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    if((casillaActual->getTipo() == TESORO) && (!casillaActual->estaProtegido())){
                        cout << "HAY UN TESORO EN LAS COORDENADAS: " << x << " " << y << " " << z << " " << endl;
                    }
                }
            }
        }
    }
    else if (realY < 2){
        Ficha* casillaActual = tablero->getTData(x,y,z);
        //ver si la condicion es menor o menor o igual
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 2; j++){
                for(int k = 0; k < 3; k++){
                    if((casillaActual->getTipo() == TESORO) && (!casillaActual->estaProtegido())){
                        cout << "HAY UN TESORO EN LAS COORDENADAS: " << x << " " << y << " " << z << " " << endl;
                    }
                }
            }
        }
    }
    else if (realZ < 3){
        Ficha* casillaActual = tablero->getTData(x,y,z);
        //ver si la condicion es menor o menor o igual
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    if((casillaActual->getTipo() == TESORO) && (!casillaActual->estaProtegido())){
                        cout << "HAY UN TESORO EN LAS COORDENADAS: " << x << " " << y << " " << z << " " << endl;
                    }
                }
            }
        }
    }
}

//las coordenadas que se ingresan son donde se piensa colocar el tesoro.
void Juego::duplicarTesoro(int x, int y, int z, Jugador* jugador){
    while((this->tablero->getTData(x,y,z)->getTipo() == TESORO)){
        cout << "Error! hay un tesoro en esa posicion. Ingrese una nueva coordenada.\n" << endl;
        cin >> x >> y >> z;
    }
    Coordenada* pos = new Coordenada(x,y,z);
    colocarFicha(TESORO, pos);
    Ficha* nFicha = this->tablero->getTData(x,y,z);
    jugador->getListaFichas()->add(nFicha);
    //ver como se incrementa el numero de tesoros y si hay confilicto con mas de 4 
}

//x, y, z son las coordenadas de la ficha que se desea mover (solo valido para minas, tesoros, espias)
void Juego::palaTunel(int x, int y, int z, Jugador* jugador){
    Ficha* fichaPos = this->tablero->getTData(x,y,z);
    while((fichaPos->getTipo() != TESORO) || (fichaPos->getTipo() != ESPIA) || fichaPos->getTipo() != MINA){
        cout<<"Error, ficha no valida para movimiento, intente con otra ficha.\n" << endl;
        cout<<"Ingrese las coordenadas de la ficha deseada en formato x, y, z\n" << endl;
        cin >> x >> y >> z;
        fichaPos = this->tablero->getTData(x,y,z);
    }
    int i, j, k;
    cout<< "Ingrese la coordenada donde desea mover la ficha en formato x, y ,z\n" << endl;
    cin >> i >> j >> k;
    ///preguntar
    Ficha* vacio = this->tablero->getTData(i,j,k);
    while(vacio->getTipo() != VACIO){
        cout << "Error! esa casilla no esta vacia, por favor ingrese otras coordenadas,\n" << endl;
        cin >> i >> j >> k;
        vacio = this->tablero->getTData(i,j,k);
    }
    Coordenada* pos = new Coordenada(i,j,k);
    //como se mueve la ficha, supongo que no hace falta eliminarla del tablero.
    colocarFicha(fichaPos->getTipo(), pos);
    //actualiza la ficha a vacio
    this->tablero->setTData(x,y,z,vacio);

    //hara falta revisar las interacciones si un tesoro va donde un enemigo, espia en espia, mina en tesoro, etc...
}

void Juego::agentesDurmientes(Jugador* jugador){
    string name = jugador->getNombre();
    string aux;
    int lenJugadores = jugadores->getSize();
    for(int x = 0; x < lenJugadores - 1; x++){
        Jugador* jugadorActual = this->jugadores->getLData(x);
        //Lista<Ficha*>* fichas = jugadorActual->getListaFichas();
        aux = jugadorActual->getNombre();
        if(name != aux){
            jugadorActual->getListaFichas()->getLData(x)->setTurnosInactiva(1);  
        }
    }
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

void Juego::imprimirMazo(){
    Jugador* jugador = this->jugadores->getLData(this->jugadores->getIter());
    string alerta;
    for(int i = 0; i < 6; i++){
        string cantidad = to_string(jugador->getMazo()->obtenerCantidadCartas((TipoCartas)i));
        alerta = jugador->getMazo()->tipoDeCartaGlobal((TipoCartas)i) + ": " + cantidad + "\n";
        this->mostrarAlertas(alerta, jugador);
    }
    
}

void Juego::handlerMazo(){
    Jugador* jugadorActual = this->jugadores->getLData(this->jugadores->getIter());
    Decision decision = NINGUNA;
    this->preguntarDecisionMazo(&decision);
    if(decision == SI){
        this->imprimirMazo();
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
        cout << "Exception: No players left" << endl;
        this->estadoPartida == -1;
    }
}

void Juego::preguntarCoordenada(Coordenada* pos){
    cout << "Ingrese la coordenada en el formato X Y Z: ";
    cin >> *pos;
    while(!this->validarLimitePosicion(pos)){
        cout << "Coordenada invalida, ingrese otra: ";
        cin >> *pos;
    }
}

void Juego::colocarFicha(TipoFichas tipo, Coordenada* pos){
    this->tablero->getTDataC(pos)->setTipo(tipo);
}

void Juego::colocarFicha(TipoFichas tipo, Coordenada* pos, int jugadorNuevo){
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
                this->colocarFicha(VACIO, aux, 0);
                *loopCheck = true;
                break;
            }
            this->mostrarAlertas("No se puede atacar un espia propio\n", this->jugadores->getLData(jugadorActual));
            break;

        case VACIO:
            this->colocarFicha(MINA, aux, this->jugadores->getIter());
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
                this->colocarFicha(VACIO, aux, 0);
                *loopCheck = true;
                break;
            }
            this->mostrarAlertas("El espia pisaria tu propia mina\n", this->jugadores->getLData(jugadorActual));
            break;

        case TESORO:
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
                this->colocarFicha(VACIO, aux, 0);
                *loopCheck = true;
                break;
            }
            this->mostrarAlertas("No se puede atacar un espia propio\n", this->jugadores->getLData(jugadorActual));
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
    int jugadorDest = this->tablero->getTDataC(auxDest)->getJugadorOwner();
    TipoFichas tipoSrc = this->tablero->getTDataC(auxSrc)->getTipo();
    TipoFichas tipoDest = this->tablero->getTDataC(auxDest)->getTipo();
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
    delete auxSrc;
    delete auxDest;
}

void Juego::handlerCoordenadaFicha(Coordenada* aux, TipoFichas tipoSrc){
    cout << "Ficha: " << this->getFichaTipoGlobal(tipoSrc) << endl;
    if(tipoSrc != TESORO){
        this->preguntarCoordenada(aux);
    }
}

void Juego::handlerFicha(TipoFichas tipoSrc){
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
                handlerTesoro(&loopCheck);
                break;
        }
    }
    delete aux;
}

void Juego::mostrarAlertas(string alerta, Jugador* jugadorActual){
    string fileName = "Alertas_" + jugadorActual->getNombre() + ".txt";
    FILE* archivo = fopen(fileName.c_str(), "a");
    fprintf(archivo, "%s\n", alerta.c_str());
    fclose(archivo);
}

void Juego::limpiarArchivo(Jugador* jugadorActual){
    string fileName = "Alertas_" + jugadorActual->getNombre() + ".txt";
    FILE* archivo = fopen(fileName.c_str(), "w");
    fclose(archivo);
}

void Juego::sacarFoto(){
    Jugador* jugadorActual = this->jugadores->getLData(this->jugadores->getIter());
    Coordenada* imgSize = new Coordenada(this->tablero->getTamanioX() * 100, this->tablero->getTamanioY() * 70, 0);
    BMP* imagen = new BMP();
    imagen->SetSize(imgSize->getX(), imgSize->getY());
    imprimirBMP(*imgSize, imagen, this->tablero, this->jugadores->getIter());
    string fileName = "Tablero_" + jugadorActual->getNombre() + ".bmp";
    imagen->WriteToFile(fileName.c_str());
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