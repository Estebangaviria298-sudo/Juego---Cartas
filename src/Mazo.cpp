#include "Mazo.h"
#include <iostream>
#include <algorithm>
#include <random>

Mazo::Mazo()
{
}

void Mazo::crearMazo()
{
    for (int numero = 1; numero <= 16; numero++)
    {
        cartas.push_back(Carta(numero, "rojo"));
        cartas.push_back(Carta(numero, "azul"));
    }
}

int Mazo::cantidadCartas()
{
    return cartas.size();
}

void Mazo::mostrarCartas()
{
    for (Carta carta : cartas)
    {
        cout << carta.getNumero() << " - "
             << carta.getColor() << endl;
    }
}

void Mazo::barajar()
{
    random_device rd;
    mt19937 generador(rd());

    shuffle(cartas.begin(), cartas.end(), generador);
}

Carta Mazo::sacarCarta()
{
    Carta carta = cartas.back();
    cartas.pop_back();

    return carta;
}