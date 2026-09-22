#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "Mazo.h"

class Juego
{
private:
    Mazo mazo;
    Jugador jugadores[4];

public:
    Juego();

    void iniciar();
};

#endif