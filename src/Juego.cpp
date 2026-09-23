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

    solicitarCondicion();
    determinarGanador();
}

void Juego::solicitarCondicion()
{
    cout << "\nIngrese el color solicitado (rojo/azul): ";
    cin >> colorSolicitado;

    cout << "Ingrese la definicion (bajo/alto): ";
    cin >> definicion;

    cout << "\nCondicion seleccionada: "
         << colorSolicitado << " " << definicion << endl;
}

void Juego::determinarGanador()
{
    Carta mejorCarta;
    string nombreGanador = "";
    bool primeraCarta = true;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < jugadores[i].cantidadCartas(); j++)
        {
            Carta carta = jugadores[i].obtenerCarta(j);

            if (carta.getColor() == colorSolicitado)
            {
                if (primeraCarta)
                {
                    mejorCarta = carta;
                    nombreGanador = jugadores[i].getNombre();
                    primeraCarta = false;
                }
                else if (definicion == "bajo" &&
                         carta.getNumero() < mejorCarta.getNumero())
                {
                    mejorCarta = carta;
                    nombreGanador = jugadores[i].getNombre();
                }
                else if (definicion == "alto" &&
                         carta.getNumero() > mejorCarta.getNumero())
                {
                    mejorCarta = carta;
                    nombreGanador = jugadores[i].getNombre();
                }
            }
        }
    }

    if (!primeraCarta)
    {
        cout << "\nGanador: " << nombreGanador << endl;

        cout << "Carta ganadora: "
             << mejorCarta.getNumero() << " - "
             << mejorCarta.getColor() << endl;
    }
}