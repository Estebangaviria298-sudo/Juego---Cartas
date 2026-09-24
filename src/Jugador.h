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
    vector<Carta> cartasGanadas;
    int puntos;

public:
    Jugador();
    Jugador(string nombre);

    string getNombre();

    void recibirCarta(Carta carta);

    void mostrarMano();

    Carta jugarCarta(int posicion);

    int cantidadCartas();

    Carta obtenerCarta(int posicion);

    void sumarPuntos(int cantidad);

    int getPuntos();

    void recibirCartaGanada(Carta carta);

    void mostrarCartasGanadas();

    vector<Carta> getMano();

    vector<Carta> getCartasGanadas();

    void cargarDatos(string nombre, int puntos,
                     vector<Carta> mano,
                     vector<Carta> cartasGanadas);
};

#endif