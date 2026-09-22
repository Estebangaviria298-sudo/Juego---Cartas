#ifndef CARTA_H
#define CARTA_H

#include <string>
using namespace std;

class Carta
{
private:
    int numero;
    string color;

public:
    Carta();
    Carta(int numero, string color);

    int getNumero();
    string getColor();
};

#endif
