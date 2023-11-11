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
    MINA,
    TESORO,
    ESPIA,
    VACIO,
    TESORO_DESENTERRADO,
    INACTIVO
};

//Celdas
enum TipoTerreno{
    TERRENO_ARENA,
    TERRENO_AGUA,
    TERRENO_PASTO,
    TERRENO_TIERRA,
    TERRENO_BORDE,
    TERRENO_FUEGO,
    TERRENO_INACTIVO,
    FICHA_ESPIA,
    FICHA_MINA,
    FICHA_TESORO
};

//Decidiones
enum Decision{
    SI,
    NO,
    SALIR,
    NINGUNA
};

#endif