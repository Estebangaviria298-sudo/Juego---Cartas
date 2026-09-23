#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "Mazo.h"
#include <string>

using namespace std;

class Juego
{
private:
    Mazo mazo;
    Jugador jugadores[4];

    string colorSolicitado;
    string definicion;

public:
    Juego();

    void iniciar();

    void solicitarCondicion();

    void determinarGanador();
};

#endif