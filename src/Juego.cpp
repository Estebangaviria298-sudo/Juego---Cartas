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

    jugarRonda();
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

void Juego::jugarRonda()
{
    cartasJugadas.clear();
    jugadoresQueJugaron.clear();

    cout << "\n--- CARTAS JUGADAS ---" << endl;

    for (int i = 0; i < 4; i++)
    {
        bool encontroCarta = false;

        for (int j = 0; j < jugadores[i].cantidadCartas(); j++)
        {
            Carta carta = jugadores[i].obtenerCarta(j);

            if (carta.getColor() == colorSolicitado)
            {
                Carta cartaJugadas = jugadores[i].jugarCarta(j);

                cartasJugadas.push_back(cartaJugadas);
                jugadoresQueJugaron.push_back(i);

                cout << jugadores[i].getNombre()
                     << " juega: "
                     << cartaJugadas.getNumero()
                     << " - "
                     << cartaJugadas.getColor()
                     << endl;

                encontroCarta = true;
                break;
            }
        }

        if (!encontroCarta)
        {
            cout << jugadores[i].getNombre()
                 << " no tiene una carta "
                 << colorSolicitado << endl;
        }
    }

    determinarGanador();

    cout << "\n--- MANOS DESPUES DE JUGAR ---" << endl;

    for (int i = 0; i < 4; i++)
    {
        jugadores[i].mostrarMano();
        cout << endl;
    }
}

void Juego::determinarGanador()
{
    if (cartasJugadas.size() == 0)
    {
        cout << "\nNo se jugaron cartas." << endl;
        return;
    }

    int posicionGanadora = 0;

    for (int i = 1; i < cartasJugadas.size(); i++)
    {
        if (definicion == "bajo" &&
            cartasJugadas[i].getNumero() <
            cartasJugadas[posicionGanadora].getNumero())
        {
            posicionGanadora = i;
        }

        if (definicion == "alto" &&
            cartasJugadas[i].getNumero() >
            cartasJugadas[posicionGanadora].getNumero())
        {
            posicionGanadora = i;
        }
    }

    int jugadorGanador = jugadoresQueJugaron[posicionGanadora];

    int puntosRonda = 0;

    for (int i = 0; i < cartasJugadas.size(); i++)
    {
        puntosRonda += cartasJugadas[i].getNumero();
    }

    jugadores[jugadorGanador].sumarPuntos(puntosRonda);

    cout << "\n--- GANADOR ---" << endl;

    cout << "Ganador: "
         << jugadores[jugadorGanador].getNombre()
         << endl;

    cout << "Carta ganadora: "
         << cartasJugadas[posicionGanadora].getNumero()
         << " - "
         << cartasJugadas[posicionGanadora].getColor()
         << endl;

    cout << "Puntos de la ronda: "
         << puntosRonda
         << endl;

    cout << "Puntos acumulados de "
         << jugadores[jugadorGanador].getNombre()
         << ": "
         << jugadores[jugadorGanador].getPuntos()
         << endl;
}