#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "Mazo.h"
#include <string>
#include <vector>

using namespace std;

class Juego
{
private:
    Mazo mazo;
    Jugador jugadores[4];

    string colorSolicitado;
    string definicion;

    vector<Carta> cartasJugadas;
    vector<int> jugadoresQueJugaron;

public:
    Juego();

    void iniciar();

    void solicitarCondicion();

    void determinarGanador();

    void jugarRonda();
};

#endif