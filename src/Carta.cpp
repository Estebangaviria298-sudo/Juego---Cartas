#include "Carta.h"

Carta::Carta()
{
    numero = 0;
    color = "";
}

Carta::Carta(int numero, string color)
{
    this->numero = numero;
    this->color = color;
}

int Carta::getNumero()
{
    return numero;
}

string Carta::getColor()
{
    return color;
}