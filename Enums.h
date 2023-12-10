#ifndef __ENUMS_H__
#define __ENUMS_H__

//Colores terminal
#define RES_COLOR       "\033[0m"
#define RES_FONDO       "\u001b[0m"
#define COLOR_NEGRO     "\033[30m" 
#define COLOR_ROJO      "\033[31m" 
#define COLOR_VERDE     "\033[32m" 
#define COLOR_AMARILLO  "\033[33m" 
#define COLOR_AZUL      "\033[34m" 
#define COLOR_BLANCO    "\033[37m" 

#define COLOR_NEGRO_NEGRITA    "\033[1m\033[30m"  
#define COLOR_ROJO_NEGRITA     "\033[1m\033[31m"  

#define FONDO_NEGRO      "\u001b[40m;1m"
#define FONDO_ROJO       "\u001b[41m;1m"
#define FONDO_VERDE      "\u001b[42m;1m"
#define FONDO_AMARILLO   "\u001b[43m;1m"
#define FONDO_AZUL       "\u001b[44m;1m"
#define FONDO_BLANCO     "\u001b[47m;1m"

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