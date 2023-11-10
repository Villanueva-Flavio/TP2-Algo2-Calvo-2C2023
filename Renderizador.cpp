#include <sstream>
#include <string>
#include <iostream>
#include "Tablero.h"
#include "./Headers/Renderizador.h"
#include "Enums.h"

//RENDER
const RGBApixel BLANCO = {255, 255, 255, 0};
const RGBApixel BORDE = {0, 0, 0, 0};
//TERRAIN
const RGBApixel ARENA = {0, 215, 215, 0};
const RGBApixel ARENA_OSCURA = {0, 150, 150, 0};
const RGBApixel AGUA = {255, 0, 0, 0};
const RGBApixel AGUA_OSCURA = {150, 0, 0, 0};
const RGBApixel PASTO = {89, 130, 65, 0};
const RGBApixel PASTO_OSCURO = {50, 70, 35, 0};
const RGBApixel TIERRA = {14, 48, 94, 0};
const RGBApixel TIERRA_OSCURA = {9, 32, 64, 0};
//PROPS
const RGBApixel INACTIVO = {12, 92, 232, 0};
const RGBApixel MINA = {50, 50, 50, 50};
const RGBApixel ESPIA = {201, 41, 207, 0};
const RGBApixel TESORO = {207, 174, 41, 0};


double gradosARadianes(double grados){
    return grados * 3.14159 / 180.0;
}

void getAngulos(double angulos[6], int lado){
    switch(lado){
        case IZQUIERDA:
            angulos[0] = 40; angulos[1] = 20; angulos[2] = 0; angulos[3] = 30; angulos[4] = -30; angulos[5] = -30;
            break;
        case DERECHA:
            angulos[0] = -40; angulos[1] = 20; angulos[2] = 0; angulos[3] = -30; angulos[4] = 30; angulos[5] = -30;
            break;
        case ATRAS:
            angulos[0] = 40; angulos[1] = 20; angulos[2] = 0; angulos[3] = -30; angulos[4] = 30; angulos[5] = -30;
            break;
    }
}

void aplicarProyeccionIsometrica(CoordenadaDouble* pixel, int lado){
    double angulos[6];
    getAngulos(angulos, lado);
    pixel->setX((double)(gradosARadianes(angulos[0]) * pixel->getX() + gradosARadianes(angulos[1]) * pixel->getY() + gradosARadianes(angulos[2]) * pixel->getZ()));
    pixel->setY((double)(gradosARadianes(angulos[3]) * pixel->getX() + gradosARadianes(angulos[4]) * pixel->getY() + gradosARadianes(angulos[5]) * pixel->getZ()));
}

bool coloresSonIguales(RGBApixel color1, RGBApixel color2){
    return color1.Red == color2.Red && color1.Green == color2.Green && color1.Blue == color2.Blue;
}

bool colorEnRango(RGBApixel color){
    return color.Red >= 0 && color.Red <= 255 && color.Green >= 0 && color.Green <= 255 && color.Blue >= 0 && color.Blue <= 255;
}

bool pixelEnRango(int px, int py, Coordenada imgSize){
    return px >= 0 && px < imgSize.getX() && py >= 0 && py < imgSize.getY();
}


int pixelSizeGet(RGBApixel color){
    int resultado = (coloresSonIguales(color, AGUA))? 2:8;
    resultado = (coloresSonIguales(color, INACTIVO))? 7:resultado;
    resultado = (coloresSonIguales(color, AGUA_OSCURA) || coloresSonIguales(color, BORDE) || coloresSonIguales(color, MINA))? 3:resultado;
    resultado = (coloresSonIguales(color, ARENA) || coloresSonIguales(color, ARENA_OSCURA) || coloresSonIguales(color, TIERRA) || coloresSonIguales(color, TIERRA_OSCURA) || coloresSonIguales(color, PASTO))? 6:resultado;
    return resultado;
}

bool pixelSizeEnRango(Coordenada pixelPos, Coordenada imgSize, int pixelSize){
    bool resultado = false;
    if(pixelEnRango(pixelPos.getX() + pixelSize, pixelPos.getY() + pixelSize, imgSize) && 
        pixelEnRango(pixelPos.getX() - pixelSize, pixelPos.getY() - pixelSize, imgSize) && 
        pixelEnRango(pixelPos.getX() + pixelSize, pixelPos.getY() + pixelSize, imgSize) && 
        pixelEnRango(pixelPos.getX() - pixelSize, pixelPos.getY() - pixelSize, imgSize)){
        resultado = true;
    }
    return resultado;
}

void pintarEntidad(BMP* image, Coordenada pixelPos, RGBApixel color, Coordenada imgSize){
    int pixelSize = pixelSizeGet(color);
    for(int i = 0; i < pixelSize; i++){
        for(int j = 0; j < pixelSize; j++){
            if(pixelSizeEnRango(pixelPos, imgSize, pixelSize) && !coloresSonIguales(color, BLANCO)){
                    image->SetPixel(pixelPos.getX() + i, pixelPos.getY() + j, color);
                    image->SetPixel(pixelPos.getX() - i, pixelPos.getY() + j, color);
                    image->SetPixel(pixelPos.getX() + i, pixelPos.getY() - j, color);
                    image->SetPixel(pixelPos.getX() - i, pixelPos.getY() - j, color);
            }
        }
    }
}

Coordenada getPixelOffset(int lado, int size){
    Coordenada pixelOffset = Coordenada(0, 0, 0);
    pixelOffset.setX((lado == IZQUIERDA)? size*5 : (lado == DERECHA)? size*43 : size*55);
    pixelOffset.setY((lado == IZQUIERDA)? size*37 : (lado == DERECHA)? size*31 : size*38);
    return pixelOffset;
}

RGBApixel codigoColorSegunCelda(TipoTerreno capaCelda){
    RGBApixel codigoColor;
    switch (capaCelda){
        case TERRENO_ARENA:
            codigoColor = ARENA;
            break;
        case TERRENO_AGUA:
            codigoColor = AGUA;
            break;
        case TERRENO_PASTO:
            codigoColor = PASTO;
            break;
        case TERRENO_TIERRA:
            codigoColor = TIERRA;
            break;
        case TERRENO_BORDE:
            codigoColor = BORDE;
            break;
        case TERRENO_INACTIVO:
            codigoColor = INACTIVO;
            break;
        case FICHA_ESPIA:
            codigoColor = ESPIA;
            break;
        case FICHA_MINA:
            codigoColor = TESORO;
            break;
        case FICHA_TESORO:
            codigoColor = TESORO;
            break;
    }
    return codigoColor;
}

bool capaExiste(TipoTerreno capaCelda){
    if(capaCelda == TERRENO_ARENA || capaCelda == TERRENO_AGUA || capaCelda == TERRENO_PASTO || capaCelda == TERRENO_TIERRA ||capaCelda == FICHA_MINA 
       || capaCelda == TERRENO_BORDE || capaCelda == TERRENO_FUEGO || capaCelda == FICHA_ESPIA){
        return true;
    }
    return false;
}

RGBApixel getColor(Celda celda, bool esFicha){
    RGBApixel colorAux = (esFicha)? ESPIA : BLANCO;
    if(coloresSonIguales(colorAux, BLANCO)){
        colorAux = (capaExiste(celda.getTipo()))? codigoColorSegunCelda(celda.getTipo()) : colorAux;
    }
    return colorAux;
}

void getAux(int lado, Coordenada* aux){
    int valor = (lado == ATRAS) ? -1 : 1;
    aux->setX(valor);
    aux->setY(valor);
    aux->setZ(valor);
}

void getPixel(CoordenadaDouble* pixel, Coordenada matrixPos){



    pixel->setX((double)matrixPos.getX());
    pixel->setY((double)matrixPos.getY());
    pixel->setZ((double)matrixPos.getZ());
}

int matrixPosStarter(int lado, int size){
    return (lado == IZQUIERDA)? 0 : (lado == DERECHA)? 0 : size-1;
}

void imprimirBMP(Coordenada imgSize, BMP* image, Tablero<Celda*>* tablero, int jugador){
    RGBApixel color;
    int i = 0;
    Coordenada pixelPos, matrixPos, aux, pixelOffset;
    CoordenadaDouble pixel;
    bool esFicha = false;
    for(int lado = 0; lado < 3; lado ++){
        getAux(lado, &aux);
        pixelOffset = getPixelOffset(lado, tablero->getTamanioX());

        matrixPos.setX(matrixPosStarter(lado, tablero->getTamanioX()));
        matrixPos.setY(matrixPosStarter(lado, tablero->getTamanioY()));
        matrixPos.setZ(matrixPosStarter(lado, tablero->getTamanioZ()));

        while (matrixPos.getX() < tablero->getTamanioX() && matrixPos.getX() >= 0) {
            while (matrixPos.getY() < tablero->getTamanioY() && matrixPos.getY() >= 0) {
                while (matrixPos.getZ() < tablero->getTamanioZ() && matrixPos.getZ() >= 0) {
                    getPixel(&pixel, matrixPos);
                    aplicarProyeccionIsometrica(&pixel, lado);
                    pixelPos.setX(static_cast<int>((pixel.getX()) * 20 + pixelOffset.getX())); 
                    pixelPos.setY(static_cast<int>((pixel.getY()) * 20 + pixelOffset.getY()));
                    esFicha = (tablero->getTData(matrixPos.getX(), matrixPos.getY(), matrixPos.getZ())->getFicha()->getJugadorOwner() == jugador && tablero->getTData(matrixPos.getX(), matrixPos.getY(), matrixPos.getZ())->getFicha()->getTipo() != MINA_FICHA);
                    color = getColor(*tablero->getTData(matrixPos.getX(), matrixPos.getY(), matrixPos.getZ()), esFicha);
                    pintarEntidad(image, pixelPos, color, imgSize);
                    matrixPos.setZ(matrixPos.getZ() + aux.getZ());
                }
                matrixPos.setZ(matrixPosStarter(lado, tablero->getTamanioZ()));
                matrixPos.setY(matrixPos.getY() + aux.getY());
            }
            matrixPos.setY(matrixPosStarter(lado, tablero->getTamanioY()));
            matrixPos.setX(matrixPos.getX() + aux.getX());
        }
    }
}