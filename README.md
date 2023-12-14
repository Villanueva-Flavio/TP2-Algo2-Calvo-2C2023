
# TP2- Algo2Calvo: TESORO BINARIO v2

Bienvenido al repositorio del juego que he creado para la cátedra Calvo (01) de Algoritmos y Programación 2, 2C2023 de FIUBA
Dicho juego consiste en una mezcla de Batalla naval pero más enfocado en busqueda y recuperación de tesoros
El juego fue diseñado para sacar fotos para cada jugador para cada tablero por separado, en formato 3D con 3 perspectivas distintas.
Que lo disfrutes, y no dudes en contactarme si tenés alguna duda.


## 1. Compilar.

> Para compilar el juego se puede hacer en un solo comando independientemente de la carencia de un Make file

	g++ *.cpp -o TESORO_BINARIO


## 2. Consideraciones al jugar.

> Recordar que el juego generará una carpeta en el directorio donde es ejecutado, llamado: "Partida" donde se guardarán todos los archivos de todos los jugadores, .txt y .bmp con prefijo del tipo de archivo y el nombre del jugador seleccionado

## 3. Jugar.

### 1. Carga del juego:
> Para cargar el juego basta con simplemente ejecutar el binario compilado

	Linux: ./TESORO_BINARIO
	Windows: run TESORO_BINARIO.exe

> Se le preguntará la cantidad de jugadores (de 2 a 10)

> A continuación se le preguntara por cada jugador:

	NOMBRE DEL JUGADOR
	POSICION DE FICHA 1
	POSICION DE FICHA 2
	POSICION DE FICHA 3
	POSICION DE FICHA 4

Recuerde que la posición de ficha se debe ingresar los 3 números dentro del margen del mapa, espaciados en 1 sola línea, aunque también acepta \n

### 2. Jugabilidad del turno.
	

 1. Handler Carta.
	 1. Usar Carta.
		 El juego le mostrará la carta que ha recibido y le preguntará si quiere usarla
		 Las opciones son: si/no/salir.
		 Si elige "si": usará la carta.
		 Si elige "no": se guardará en el mazo.
		 Si elige "salir": saldrá del juego completamente. 
	 2. Ver Mazo.
		 El juego a continuación le dará la opción de poder entrar a ver su mazo, este mismo se imprimirá en el archivo de Alertas que posea dicho jugador, las opciones de elegir son las mismas, si no elige si, no se imprimirán, en el caso de imprimir las cartas, puede elegir 0 para no elegir ninguna carta.
	 3. Tipos de Carta.
	 
		 1. Blindaje.
			 Prevee que un tesoro propio sea atacado en el siguiente turno.
			 
		 2. Radar.
			 Revela todas las fichas enemigas en una posición designada en un radio de 3 posiciones.
			 
		 3. Duplicar tesoro.
			 Genera una copia de un Tesoro nuevo en una posición designada
			 
		 4. Pala para túnel.
			 Permite mover una de tus fichas a otra posición
			 
		 5. Agentes durmientes.
			 Invoca a 2 nuevos espías
			 
		 6. Bomba de racimo.
			 Ataca 5 posiciones de manera manual.
	 
 2. Handler Mina.
	 El juego le pedírá una posición para soltar una mina, en caso de que esta impactase con una ficha propia o una casilla inactiva, le pedirá nuevamente ingresar una posición nueva.
	 Si esta se encuentra contra un espía enemigo lo elimina, si es un tesoro lo desentierra.
 3. Handler Espía.
	 El juego le pedirá una posición para dejar un nuevo espía, no puede atacar posiciones propias ni celdas inactivas, pero recuperará tesoros desenterrados.
 4. Handler Tesoro.
	 Finalmente el juego le pedirá seleccionar uno de sus tesoros, y moverlo a una posición contigua.
### 4. Archivos.
Los archivos a generarse son:
>Alertas_`NOMBRE DEL JUGADOR`.txt
`NOMBRE DEL JUGADOR`.bmp
### 5. Conclusión.
   Eso es todo, dale un star si te gustó, y unite a nuestro grupo de Discord que está creciendo.
   Lo unico que quiero pedirte es que si usarás algo de lo presente en este trabajo, no olvides de mencionarme, y por favor
   **PRINCIPALMENTE ANTE TODO:** usalo como para tomar ideas, pero no hagas tu trabajo práctico copiado de este, ya que después de todo, la idea es que aprendas vos también.

**Discord:** *thepozzard*
[**Servidor de Discord**](https://discord.gg/QskYJQAtcx "https://discord.gg/QskYJQAtcx")
[**Pagina web**](http://bonzzard.com.ar)

![a_28a07e26b320c29c3cf7702568c00104](https://github.com/Villanueva-Flavio/Ej-Algo2-Calvo-2C2023/assets/78744163/1abdf365-c39e-4442-92e1-7c5a63acb00f)
