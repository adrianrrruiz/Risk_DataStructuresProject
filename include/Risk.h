#ifndef RISK_H
#define RISK_H

#include <iostream>
#include <vector>
#include <Continente.h>
#include <Carta.h>
#include <Jugador.h>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Risk {
public:
    void eliminarColor(Risk &juego,string color);
    void imprimirColores(Risk &juego);
    void inicializar(Risk &juego);
    void leerContinentes(Risk &juego);
    void leerPaises(Risk &juego);
    void leerRelaciones(Risk &juego);
    void imprimirInformacion(Risk &juego);
    vector<Continente> continentes;
    vector<Jugador> jugadores;
    vector <Carta> cartas;
    vector <string> colores = {"verde", "azul", "rojo", "amarillo", "negro", "gris"};
    int cantidadJugadores;
};

#endif  // RISK_H