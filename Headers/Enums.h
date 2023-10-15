#ifndef __ENUMS_H__
#define __ENUMS_H__

//Lista
enum Iteracion {
    SIGUIENTE, 
    FINAL, 
    ANTERIOR
};

//Cartas
enum TipoCartas{
    BLINDAJE, 
    RADAR, 
    PARTIR_TESORO, 
    AGENTES_DURMIENTES,
    PALA_PARA_TUNEL,
    BOMBA_DE_RACIMO
};

//Fichas
enum TipoFichas{
    TESORO,
    ESPIA,
    VACIO,
    INACTIVO
};

#endif