▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂

Descripción breve del juego:

N jugadores en un mapa de tamaño X Y Z, con M tesoros.
Donde pierden los que se quedan sin tesoros, y es por turno
▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂

Ejecución del turno:

a) El jugador recibe una carta aleatoria

b) El jugador decide si usar esa carta, guardarla, o usar otra carta

┏━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┑
┃                   ┃    Interacción                                                                ┃
┃     Actividades   ┃━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┫
┃                   ┃      Tesoro          ┃      Espía      ┃      Vacío      ┃      Inactivo      ┃
┃━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫
┃                   ┃                      ┃                 ┃ Casilla         ┃  No                ┃
┃                   ┃     Descubre         ┃  Mata al        ┃                 ┃                    ┃
┃  c) Dejar Mina    ┃   la ubicación       ┃                 ┃     queda       ┃    se              ┃
┃                   ┃     del tesoro       ┃     espía       ┃                 ┃                    ┃
┃                   ┃                      ┃                 ┃      inactiva   ┃      puede         ┃
┃                   ┃                      ┃                 ┃                 ┃                    ┃
┃━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫
┃                   ┃  Recupera tesoro     ┃   Se eliminan   ┃  Se queda       ┃   No se puede      ┃
┃  d) Dejar Espía   ┃   (tarda 5 turnos)   ┃   Ambos espías  ┃ esperando a un  ┃       mover        ┃
┃                   ┃                      ┃                 ┃    tesoro       ┃            ahí     ┃
┃━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫
┃                   ┃  Notifica al Jugador ┃   El jugador    ┃ Mueve el tesoro ┃ No se puede        ┃
┃  e) Mover Tesoro  ┃  la presencia del    ┃   pierde el     ┃   a esta        ┃   mover            ┃
┃                   ┃   tesoro             ┃     tesoro      ┃    dirección    ┃     acá            ┃
┗━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┛

▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂

Descripción de las cartas existentes:
    
    Proveída por la consigna:
        1- Blindaje: Bloquea captura de tesoro por X turnos
        2- Radar: Soltada en una posicion: detecta tesoros 3 casilleros a la redonda
        3- Partir tesoro: Parte un tesoro en 2 casilleros
    
    Propio del programador:
        4- Agentes durmientes: Permite colocar 2 espias adicionales
        5- Pala para tunel: Mueve un tesoro bajo tierra advirtiendo antes si hay un espia para redireccionar
        6- Bomba de racimo: Suelta una bomba que despliega minas aleatoriamente desde un area dependiendo 
               del tamaño del mapa (1/4 * size  ->  1:4 2:8 3:12 4:16 5:20)

▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂