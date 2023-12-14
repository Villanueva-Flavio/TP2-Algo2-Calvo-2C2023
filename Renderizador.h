#ifndef __RENDERIZADOR_H__
#define __RENDERIZADOR_H__

#include "Tablero.h"
#include "Enums.h"
#include "EasyBMP.h"
#include "Coordenada.h"
#include "CoordenadaDouble.h"
#include "Ficha.h"

#define IZQUIERDA 0
#define DERECHA 1
#define ATRAS 2


//RENDER
const RGBApixel C_BLANCO = {255, 255, 255, 0};
const RGBApixel C_BORDE = {0, 0, 0, 0};
//TERRAIN
const RGBApixel C_ARENA = {0, 215, 215, 0};
const RGBApixel C_ARENA_OSCURA = {0, 150, 150, 0};
const RGBApixel C_AGUA = {255, 0, 0, 0};
const RGBApixel C_AGUA_OSCURA = {150, 0, 0, 0};
const RGBApixel C_PASTO = {89, 130, 65, 0};
const RGBApixel C_PASTO_OSCURO = {50, 70, 35, 0};
const RGBApixel C_TIERRA = {14, 48, 94, 0};
const RGBApixel C_TIERRA_OSCURA = {9, 32, 64, 0};
//PROPS
const RGBApixel C_INACTIVO = {12, 92, 232, 0};
const RGBApixel C_MINA = {50, 50, 50, 50};
const RGBApixel C_ESPIA = {201, 41, 207, 0};
const RGBApixel C_TESORO = {207, 174, 41, 0};
const RGBApixel C_VACIO = {50, 50, 50, 0};

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

bool pixelEnRango(int px, int py, Coordenada* imgSize){
    return px >= 0 && px < imgSize->getX() && py >= 0 && py < imgSize->getY();
}


int pixelSizeGet(RGBApixel color){
    return (coloresSonIguales(color, C_TESORO) || coloresSonIguales(color, C_ARENA) || coloresSonIguales(color, C_ARENA_OSCURA) || coloresSonIguales(color, C_TIERRA) || coloresSonIguales(color, C_TIERRA_OSCURA) || coloresSonIguales(color, C_PASTO) || coloresSonIguales(color, C_PASTO_OSCURO))? 5 :
           (coloresSonIguales(color, C_INACTIVO))? 7 :
           (coloresSonIguales(color, C_MINA) || coloresSonIguales(color, C_ESPIA))? 4 :
           (coloresSonIguales(color, C_BORDE))? 3 :
           (coloresSonIguales(color, C_AGUA) || coloresSonIguales(color, C_AGUA_OSCURA) || coloresSonIguales(color, C_VACIO))? 1 :
           (coloresSonIguales(color, C_BLANCO))? 0 : 0;
    
}

bool pixelSizeEnRango(Coordenada* pixelPos, Coordenada* imgSize, int pixelSize){
    bool resultado = false;
    if (pixelEnRango(pixelPos->getX() + pixelSize, pixelPos->getY() + pixelSize, imgSize) && 
        pixelEnRango(pixelPos->getX() - pixelSize, pixelPos->getY() - pixelSize, imgSize) && 
        pixelEnRango(pixelPos->getX() + pixelSize, pixelPos->getY() + pixelSize, imgSize) && 
        pixelEnRango(pixelPos->getX() - pixelSize, pixelPos->getY() - pixelSize, imgSize)){
        resultado = true;
    }
    return resultado;
}

void pintarEntidad(BMP* image, Coordenada* pixelPos, RGBApixel color, Coordenada* imgSize){
    int pixelSize = pixelSizeGet(color);
    for(int i = 0; i < pixelSize; i++){
        for(int j = 0; j < pixelSize; j++){
            if(pixelSizeEnRango(pixelPos, imgSize, pixelSize) && !coloresSonIguales(color, C_BLANCO)){
                image->SetPixel(pixelPos->getX() + i, pixelPos->getY() + j, color);
                image->SetPixel(pixelPos->getX() - i, pixelPos->getY() + j, color);
                image->SetPixel(pixelPos->getX() + i, pixelPos->getY() - j, color);
                image->SetPixel(pixelPos->getX() - i, pixelPos->getY() - j, color);
            }
        }
    }
}

void getPixelOffset(int lado, int size, Coordenada* pixelOffset){;
    pixelOffset->setX((lado == IZQUIERDA)? size*5 : (lado == DERECHA)? size*43 : size*55);
    pixelOffset->setY((lado == IZQUIERDA)? size*37 : (lado == DERECHA)? size*31 : size*38);
}

RGBApixel codigoColorSegunCelda(TipoTerreno capaCelda){
    RGBApixel codigoColor;
    switch (capaCelda){
        case TERRENO_ARENA:
            codigoColor = C_ARENA;
            break;
        case TERRENO_AGUA:
            codigoColor = C_AGUA;
            break;
        case TERRENO_PASTO:
            codigoColor = C_PASTO;
            break;
        case TERRENO_TIERRA:
            codigoColor = C_TIERRA;
            break;
        case TERRENO_BORDE:
            codigoColor = C_BORDE;
            break;
        case TERRENO_INACTIVO:
            codigoColor = C_INACTIVO;
            break;
        case FICHA_ESPIA:
            codigoColor = C_ESPIA;
            break;
        case FICHA_MINA:
            codigoColor = C_TESORO;
            break;
        case FICHA_TESORO:
            codigoColor = C_TESORO;
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

RGBApixel getColor(Ficha* ficha, bool esFicha){
    /* RGBApixel colorAux = C_BLANCO;
    if(coloresSonIguales(colorAux, C_BLANCO)){
        colorAux = (capaExiste(ficha->getTipoTerreno()))? codigoColorSegunCelda(ficha->getTipoTerreno()) : colorAux;
    }
    return colorAux; */
    RGBApixel colorAux = C_VACIO;
    if(esFicha){
        switch(ficha->getTipo()){
            case MINA:
                colorAux = C_MINA;
                break;
            case TESORO:
                colorAux = C_TESORO;
                break;
            case ESPIA:
                colorAux = C_ESPIA;
                break;
            case TESORO_DESENTERRADO:
                colorAux = C_TESORO;
                break;
            case INACTIVO:
                colorAux = C_INACTIVO;
                break;
        }
    }
    return colorAux;
}

void getDif(int lado, Coordenada* aux){
    int valor = (lado == ATRAS) ? -1 : 1;
    aux->setX(valor);
    aux->setY(valor);
    aux->setZ(valor);
}

void getPixel(CoordenadaDouble* pixel, Coordenada* matrixPos){
    pixel->setX((double)matrixPos->getX());
    pixel->setY((double)matrixPos->getY());
    pixel->setZ((double)matrixPos->getZ());
}

int matrixPosStarter(int lado, int size){
    return (lado == IZQUIERDA)? 0 : (lado == DERECHA)? 0 : size-1;
}

void imprimirBMP(Coordenada* imgSize, BMP* image, Tablero<Ficha*>* tablero, int jugador){
    RGBApixel color;
    Coordenada* pixelPos = new Coordenada(0, 0, 0);
    Coordenada* matrixPos = new Coordenada(0, 0, 0);
    Coordenada* matrixPosDif = new Coordenada(0, 0, 0);
    Coordenada* pixelOffset = new Coordenada(0, 0, 0);
    CoordenadaDouble* pixel = new CoordenadaDouble(0, 0, 0);
    for(int lado = 0; lado < 3; lado ++){
        getDif(lado, matrixPosDif);
        getPixelOffset(lado, tablero->getTamanioX(), pixelOffset);
        matrixPos->setCoordenada(matrixPosStarter(lado, tablero->getTamanioX()), matrixPosStarter(lado, tablero->getTamanioY()), matrixPosStarter(lado, tablero->getTamanioZ()));
        while (matrixPos->getX() < tablero->getTamanioX() && matrixPos->getX() >= 0) {
            while (matrixPos->getY() < tablero->getTamanioY() && matrixPos->getY() >= 0) {
                while (matrixPos->getZ() < tablero->getTamanioZ() && matrixPos->getZ() >= 0) {
                    getPixel(pixel, matrixPos);
                    aplicarProyeccionIsometrica(pixel, lado);
                    pixelPos->setX(static_cast<int>((pixel->getX()) * 20 + pixelOffset->getX())); 
                    pixelPos->setY(static_cast<int>((pixel->getY()) * 20 + pixelOffset->getY()));
                    color = getColor(tablero->getTDataC(matrixPos), (tablero->getTDataC(matrixPos)->getJugadorOwner() == jugador));
                    pintarEntidad(image, pixelPos, color, imgSize);
                    matrixPos->setZ(matrixPos->getZ() + matrixPosDif->getZ());
                }
                matrixPos->setZ(matrixPosStarter(lado, tablero->getTamanioZ()));
                matrixPos->setY(matrixPos->getY() + matrixPosDif->getY());
            }
            matrixPos->setY(matrixPosStarter(lado, tablero->getTamanioY()));
            matrixPos->setX(matrixPos->getX() + matrixPosDif->getX());
        }
    }
    delete pixelPos, matrixPos, matrixPosDif, pixelOffset;
    delete pixel;
}

#endif