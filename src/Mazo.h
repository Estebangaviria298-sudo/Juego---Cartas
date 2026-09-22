#ifndef MAZO_H
#define MAZO_H

#include <vector>
#include "Carta.h"

using namespace std;

class Mazo
{
private:
    vector<Carta> cartas;

public:
    Mazo();

    void crearMazo();

    int cantidadCartas();

    void mostrarCartas();

    void barajar();

    Carta sacarCarta();
};

#endif