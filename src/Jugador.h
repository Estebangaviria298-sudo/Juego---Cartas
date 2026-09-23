#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "Carta.h"

using namespace std;

class Jugador
{
private:
    string nombre;
    vector<Carta> mano;

public:
    Jugador();
    Jugador(string nombre);

    string getNombre();

    void recibirCarta(Carta carta);

    void mostrarMano();

    Carta jugarCarta(int posicion);

    int cantidadCartas();

    Carta obtenerCarta(int posicion);
};

#endif