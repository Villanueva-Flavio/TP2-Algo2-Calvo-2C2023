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

//Celdas
enum Capa{
    CAPA_ARENA,
    CAPA_AGUA,
    CAPA_PASTO,
    CAPA_TIERRA,
    CAPA_BORDE,
    CAPA_MINA,
    CAPA_FUEGO,
    CAPA_INACTIVO,
    FICHA_ESPIA,
    FICHA_MINA,
    FICHA_TESORO
};
}
#endif