#ifndef __RENDERIZADOR_H__
#define __RENDERIZADOR_H__

#include "Tablero.h"
#include "EasyBMP.h"
#include "Coordenada.h"
#include "CoordenadaDouble.h"
#include "Ficha.h"

#define IZQUIERDA 0
#define DERECHA 1
#define ATRAS 2


RGBApixel codigoColorSegunCelda(TipoTerreno capaCelda);

bool capaExiste(TipoTerreno capaCelda);

double gradosARadianes(double grados);

void getAngulos(double angulos[6], int lado);

void aplicarProyeccionIsometrica(CoordenadaDouble* pixel, int lado);

bool coloresSonIguales(RGBApixel color1, RGBApixel color2);

bool colorEnRango(RGBApixel color);

bool pixelEnRango(int px, int py, Coordenada imgSize);

int pixelSizeGet(RGBApixel color);

bool pixelSizeEnRango(Coordenada pixelPos, Coordenada imgSize);

void pintarEntidad(BMP* image, Coordenada pixelPos, RGBApixel color, Coordenada imgSize);

Coordenada getPixelOffset(int lado, int size);

RGBApixel getColor(Ficha* celda);

void imprimirBMP(Coordenada imgSize, BMP* image, Tablero<Ficha*>* tablero, int jugador);

#endif