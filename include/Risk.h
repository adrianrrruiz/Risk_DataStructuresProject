#ifndef RISK_H
#define RISK_H

#include <iostream>
#include <vector>
#include <Continente.h>
#include <Carta.h>
#include <Jugador.h>
#include <fstream>
#include <sstream>

using namespace std;

class Risk {
public:
    void leerContinentes(Risk &juego);
    void leerPaises(Risk &juego);
    void leerRelaciones(Risk &juego);
    void imprimirInformacion(Risk &juego);
    vector<Continente> continentes;
    vector<Jugador> jugadores;
    vector <Carta> cartas;
};

#endif  // RISK_H