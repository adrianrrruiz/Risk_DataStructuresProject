#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <vector>
#include <Pais.h>

using namespace std;

class Jugador {
public:
    string color;
    string nombre;
    vector<Pais> territorios;
    int infanteria;
};

#endif  // JUGADOR_H