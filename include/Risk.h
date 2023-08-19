#ifndef RISK_H
#define RISK_H

#include <iostream>
#include <vector>
#include <Continente.h>
#include <Carta.h>
#include <Jugador.h>

using namespace std;

class Risk {
public:
    vector<Continente> continentes;
    vector<Jugador> jugadores;
    vector <Carta> cartas;
};

#endif  // RISK_H