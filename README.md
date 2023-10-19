▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂

Descripción breve del juego:

N jugadores en un mapa de tamaño X Y Z, con M tesoros.
Donde pierden los que se quedan sin tesoros, y es por turno
▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂

Ejecución del turno:

a) El jugador recibe una carta aleatoria

b) El jugador decide si usar esa carta, guardarla, o usar otra carta

c) El jugador deja una mina
    1) Si hay un tesoro: Descubre la ubicacion del tesoro
    2) Si hay un tesoro propio: pide otra coordenada
    3) Si hay un espía: Mata al espía
    4) Si hay un casillero vacío: Queda inactivo
    5) Si está inactivo: pide otra coordenada

d) El jugador deja un espía
    1) Si hay un tesoro: Recupera el tesoro (en 5 turnos)
    2) Si hay un tesoro propio: pide otra coordenada
    3) Si hay un espía: Se eliminan ambos espías
    4) Si hay un casillero vacío: Se queda esperando a un tesoro
    5) Si está inactivo:  No se puede mover ahí

e) El jugador mueve un tesoro
    (Solo si el casillero no está inactivo)
    1) Si hay un tesoro: Notifica al jugador de la presencia de un tesoro y elige otra coordenada
    2) Si hay un espía: El jugador pierde el tesoro
    3) Si hay un casillero vacío: Mueve el tesoro a esta dirección
    4) Si está inactivo: pide otra coordenada


▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂

Descripción de las cartas existentes:
    
    Propia de la consigna:
        1- Blindaje: Bloquea captura de tesoro por X turnos
        2- Radar: Soltada en una posicion: detecta tesoros 3 casilleros a la redonda
        3- Partir tesoro: Parte un tesoro en 2 casilleros
    
    Propio del programador:
        4- Agentes durmientes: Permite colocar 2 espias adicionales
        5- Pala para tunel: Mueve un tesoro bajo tierra advirtiendo antes si hay un espia para redireccionar
        6- Bomba de racimo: Suelta una bomba que despliega minas aleatoriamente desde un area dependiendo 
               del tamaño del mapa (1/4 * size  ->  1:4 2:8 3:12 4:16 5:20)

▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂
