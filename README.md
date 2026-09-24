\# Juego de Cartas



\## Descripción



Juego de cartas desarrollado en C++ como proyecto académico. El programa utiliza programación orientada a objetos mediante las clases Carta, Jugador, Mazo y Juego.



El juego se desarrolla por rondas. En cada ronda se solicita un color y una condición sobre el número de la carta. El ganador recibe las cartas jugadas y obtiene puntos según los números de las cartas ganadas.



\## Reglas principales



\- El mazo contiene 32 cartas.

\- Hay cartas con números del 1 al 16.

\- Cada número tiene una carta roja y una azul.

\- Cada jugador inicia con 4 cartas.

\- Las condiciones pueden ser:

&#x20; - Azul más bajo.

&#x20; - Azul más alto.

&#x20; - Rojo más bajo.

&#x20; - Rojo más alto.

\- El ganador de cada ronda recibe las cartas jugadas.

\- Los puntos corresponden a la suma de los números de las cartas ganadas.

\- El juego permite guardar y cargar una partida mediante serialización.



\## Clases



\### Carta

Representa una carta mediante su número y color.



\### Jugador

Administra el nombre, las cartas de la mano, las cartas ganadas y los puntos.



\### Mazo

Crea, mezcla y administra las cartas disponibles.



\### Juego

Controla las rondas, condiciones, ganadores, puntajes y guardado/carga de partidas.



\## Estructura del proyecto



```text

Juego-Cartas/

├── src/

│   ├── Carta.h

│   ├── Carta.cpp

│   ├── Jugador.h

│   ├── Jugador.cpp

│   ├── Mazo.h

│   ├── Mazo.cpp

│   ├── Juego.h

│   ├── Juego.cpp

│   └── main.cpp

├── .gitignore

└── README.md

