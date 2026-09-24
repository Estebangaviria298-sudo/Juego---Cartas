#include "Juego.h"
#include <iostream>

using namespace std;

Juego::Juego()
{
    jugadores[0] = Jugador("Jugador 1");
    jugadores[1] = Jugador("Jugador 2");
    jugadores[2] = Jugador("Jugador 3");
    jugadores[3] = Jugador("Jugador 4");

    numeroRonda = 1;
}

void Juego::iniciar()
{
    mazo.crearMazo();
    mazo.barajar();

    // Repartir 4 cartas a cada jugador al comenzar el juego
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            jugadores[j].recibirCarta(mazo.sacarCarta());
        }
    }

    mostrarEstadoJugadores();

    cout << "\nCartas restantes en el mazo: "
         << mazo.cantidadCartas()
         << endl;

    bool continuar = true;

    while (continuar)
    {
        // Reponer cartas antes de comenzar la ronda
        reponerCartas();

        cout << "\n==========================" << endl;
        cout << "         RONDA "
             << numeroRonda
             << endl;
        cout << "==========================" << endl;

        solicitarCondicion();

        jugarRonda();

        char respuesta;

        cout << "\nDesea jugar otra ronda? (s/n): ";
        cin >> respuesta;

        if (respuesta == 's' || respuesta == 'S')
        {
            numeroRonda++;
        }
        else
        {
            continuar = false;
        }
    }

    cout << "\n==========================" << endl;
    cout << "       FIN DEL JUEGO" << endl;
    cout << "==========================" << endl;

    cout << "\nPuntajes finales:" << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << jugadores[i].getNombre()
             << ": "
             << jugadores[i].getPuntos()
             << " puntos"
             << endl;
    }
}

void Juego::solicitarCondicion()
{
    bool condicionValida = false;

    while (!condicionValida)
    {
        cout << "\nIngrese el color solicitado (rojo/azul): ";
        cin >> colorSolicitado;

        cout << "Ingrese la definicion (bajo/alto): ";
        cin >> definicion;

        if ((colorSolicitado == "rojo" ||
             colorSolicitado == "azul") &&
            (definicion == "bajo" ||
             definicion == "alto"))
        {
            condicionValida = true;
        }
        else
        {
            cout << "\nCondicion no valida." << endl;

            cout << "Use solamente:" << endl;
            cout << "rojo bajo" << endl;
            cout << "rojo alto" << endl;
            cout << "azul bajo" << endl;
            cout << "azul alto" << endl;
        }
    }

    cout << "\nCondicion seleccionada: "
         << colorSolicitado
         << " "
         << definicion
         << endl;
}

void Juego::jugarRonda()
{
    cartasJugadas.clear();
    jugadoresQueJugaron.clear();

    cout << "\n--- CARTAS JUGADAS ---" << endl;

    for (int i = 0; i < 4; i++)
    {
        bool encontroCarta = false;

        for (int j = 0;
             j < jugadores[i].cantidadCartas();
             j++)
        {
            Carta carta = jugadores[i].obtenerCarta(j);

            if (carta.getColor() == colorSolicitado)
            {
                Carta cartaJugadas =
                    jugadores[i].jugarCarta(j);

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
                 << colorSolicitado
                 << endl;
        }
    }

    determinarGanador();

    mostrarEstadoJugadores();

    cout << "\nCartas restantes en el mazo: "
         << mazo.cantidadCartas()
         << endl;

    mostrarResumenRonda();

    mostrarTablaPuntajes();
}

void Juego::determinarGanador()
{
    if (cartasJugadas.size() == 0)
    {
        cout << "\nNo se jugaron cartas." << endl;
        return;
    }

    int posicionGanadora = 0;

    for (int i = 1;
         i < cartasJugadas.size();
         i++)
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

    int jugadorGanador =
        jugadoresQueJugaron[posicionGanadora];

    int puntosRonda = 0;

    for (int i = 0;
         i < cartasJugadas.size();
         i++)
    {
        puntosRonda += cartasJugadas[i].getNumero();
    }

    jugadores[jugadorGanador].sumarPuntos(puntosRonda);

    for (int i = 0;
         i < cartasJugadas.size();
         i++)
    {
        jugadores[jugadorGanador]
            .recibirCartaGanada(cartasJugadas[i]);
    }

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

    cout << "\n--- CARTAS GANADAS ---" << endl;

    for (int i = 0; i < 4; i++)
    {
        if (jugadores[i].getPuntos() > 0)
        {
            jugadores[i].mostrarCartasGanadas();
            cout << endl;
        }
    }
}

void Juego::mostrarEstadoJugadores()
{
    cout << "\n--- ESTADO DE LOS JUGADORES ---"
         << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << "\nJugador: "
             << jugadores[i].getNombre()
             << endl;

        cout << "Cartas en mano: "
             << jugadores[i].cantidadCartas()
             << endl;

        jugadores[i].mostrarMano();

        cout << "Puntos: "
             << jugadores[i].getPuntos()
             << endl;
    }
}

void Juego::reponerCartas()
{
    cout << "\n--- REPOSICION DE CARTAS ---" << endl;

    for (int i = 0; i < 4; i++)
    {
        while (jugadores[i].cantidadCartas() < 4 &&
               mazo.cantidadCartas() > 0)
        {
            Carta carta = mazo.sacarCarta();

            jugadores[i].recibirCarta(carta);

            cout << jugadores[i].getNombre()
                 << " recibe: "
                 << carta.getNumero()
                 << " - "
                 << carta.getColor()
                 << endl;
        }
    }
}

void Juego::mostrarResumenRonda()
{
    cout << "\n==========================" << endl;
    cout << "     RESUMEN DE RONDA" << endl;
    cout << "==========================" << endl;

    cout << "Ronda: "
         << numeroRonda
         << endl;

    cout << "Condicion: "
         << colorSolicitado
         << " "
         << definicion
         << endl;

    if (cartasJugadas.size() > 0)
    {
        int posicionGanadora = 0;

        for (int i = 1;
             i < cartasJugadas.size();
             i++)
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

        int jugadorGanador =
            jugadoresQueJugaron[posicionGanadora];

        cout << "Ganador: "
             << jugadores[jugadorGanador].getNombre()
             << endl;

        cout << "Carta ganadora: "
             << cartasJugadas[posicionGanadora].getNumero()
             << " - "
             << cartasJugadas[posicionGanadora].getColor()
             << endl;
    }
    else
    {
        cout << "No hubo cartas jugadas."
             << endl;
    }

    cout << "Cartas restantes en el mazo: "
         << mazo.cantidadCartas()
         << endl;
}

void Juego::mostrarTablaPuntajes()
{
    cout << "\n==========================" << endl;
    cout << "      TABLA DE PUNTAJES" << endl;
    cout << "==========================" << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << jugadores[i].getNombre()
             << ": "
             << jugadores[i].getPuntos()
             << " puntos"
             << endl;
    }
}