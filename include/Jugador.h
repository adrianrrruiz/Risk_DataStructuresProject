#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <vector>
#include "Pais.h"

using namespace std;

class Jugador {
public:
    bool operator<(const Jugador& otroJugador) const;
    string color;
    string nombre;
    vector<Pais> territorios;
    int infanteria;
    int resultadoDado;
};

#endif  // JUGADOR_H