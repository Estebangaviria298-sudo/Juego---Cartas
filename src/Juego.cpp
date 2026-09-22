#include "Juego.h"
#include <iostream>

using namespace std;

Juego::Juego()
{
    jugadores[0] = Jugador("Jugador 1");
    jugadores[1] = Jugador("Jugador 2");
    jugadores[2] = Jugador("Jugador 3");
    jugadores[3] = Jugador("Jugador 4");
}

void Juego::iniciar()
{
    mazo.crearMazo();
    mazo.barajar();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            jugadores[j].recibirCarta(mazo.sacarCarta());
        }
    }

    for (int i = 0; i < 4; i++)
    {
        jugadores[i].mostrarMano();
        cout << endl;
    }

    cout << "Cartas restantes en el mazo: "
         << mazo.cantidadCartas() << endl;
}