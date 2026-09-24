#include "Jugador.h"
#include <iostream>

Jugador::Jugador()
{
    nombre = "";
    puntos = 0;
}

Jugador::Jugador(string nombre)
{
    this->nombre = nombre;
    puntos = 0;
}

string Jugador::getNombre()
{
    return nombre;
}

void Jugador::recibirCarta(Carta carta)
{
    mano.push_back(carta);
}

void Jugador::mostrarMano()
{
    cout << "Cartas de " << nombre << ":" << endl;

    for (int i = 0; i < mano.size(); i++)
    {
        cout << i << ". "
             << mano[i].getNumero() << " - "
             << mano[i].getColor() << endl;
    }
}

Carta Jugador::jugarCarta(int posicion)
{
    if (posicion < 0 || posicion >= mano.size())
    {
        return Carta();
    }

    Carta carta = mano[posicion];

    mano.erase(mano.begin() + posicion);

    return carta;
}

int Jugador::cantidadCartas()
{
    return mano.size();
}

Carta Jugador::obtenerCarta(int posicion)
{
    return mano[posicion];
}

void Jugador::sumarPuntos(int cantidad)
{
    puntos += cantidad;
}

int Jugador::getPuntos()
{
    return puntos;
}

void Jugador::recibirCartaGanada(Carta carta)
{
    cartasGanadas.push_back(carta);
}

void Jugador::mostrarCartasGanadas()
{
    cout << "Cartas ganadas por " << nombre << ":" << endl;

    for (int i = 0; i < cartasGanadas.size(); i++)
    {
        cout << cartasGanadas[i].getNumero()
             << " - "
             << cartasGanadas[i].getColor()
             << endl;
    }
}

vector<Carta> Jugador::getMano()
{
    return mano;
}

vector<Carta> Jugador::getCartasGanadas()
{
    return cartasGanadas;
}

void Jugador::cargarDatos(string nombre,
                          int puntos,
                          vector<Carta> mano,
                          vector<Carta> cartasGanadas)
{
    this->nombre = nombre;
    this->puntos = puntos;
    this->mano = mano;
    this->cartasGanadas = cartasGanadas;
}