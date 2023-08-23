#ifndef RISK_H
#define RISK_H

#include <iostream>
#include <vector>
#include "Continente.h"
#include "Carta.h"
#include "Jugador.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

class Risk {
public:
    //funciones inicializar//
    void leerDistribucionCartas(Risk &juego);
    bool cantidadValida(Risk &juego);
    void eliminarColor(Risk &juego,string color);
    string imprimirColores(Risk &juego);
    bool inicializar(Risk &juego);
    void leerContinentes(Risk &juego);
    void leerPaises(Risk &juego);
    void leerRelaciones(Risk &juego);
    void imprimirInformacion(Risk &juego);
    void imprimirJugadores(Risk &juego);
    void borrarPais(Risk &juego,Pais paisEscogido);
    void imprimirTerritoriosDeJugadores(Risk &juego);
    int evaluarInfanteria(Risk &juego);
    void crearPaisesDisponibles(Risk &juego);
    Pais elegirPais(Risk &juego);
    int lanzamientoDado();
    void ordenarJugadores(vector<Jugador> &jugadores);
    bool turno(Risk &juego, string id);
    int reclamarTropasObligatorias(Risk& juego, Jugador &jugador);
    void redistribuirTropas(Risk& juego, Jugador& jugador);
    int escogerPaisAAtacar(Risk &juego,Jugador &jugador,Pais &pais);
    Jugador& jugadorEnTurno(Risk &juego, string id);
    bool paisPosibleAAtacar(vector <int> &posiblesAtaques, int codigo);
    bool ataque(Pais & ataca, Pais & defiende, Jugador& atacante, Jugador& defensor);
    Jugador& jugadorDefiende(Risk &juego, int codigo);
    Pais& delvolverPaisAAtacar(Risk &juego, int codigo);
    int cantidadTropasAtacantes(Pais &atacante);
    int cantidadTropasDefensoras(Pais &defensor);
    Carta cartaAleatoria(Risk& juego);
    void borrarCarta(Risk& juego,Carta carta);
    bool jugadorExiste(Risk &juego, string id);
    void intercambiarCartasXRefuerzos(Risk& juego, Jugador& jugador);
    bool validarSeleccionCartas(Risk& juego,Carta& c1,Carta& c2,Carta& c3);
    void actualizarCaballoDorado(Risk &juego);
    void anadirInfanteriaSiCoincideConcarta(Jugador &jugador, int codigo);
    void transferirCartas(Jugador& ganador, Jugador& perdedor);
    void eliminarJugador(Risk& juego,const string& nombre);
    vector<int> dados(int cantidad);
    vector<Continente> continentes;
    vector<Pais> paisesDisponibles;
    vector<Jugador> jugadores;
    vector <Carta> cartas;
    vector <string> colores = {"Verde", "Azul", "Rojo", "Amarillo", "Negro", "Gris"};
    int cantidadJugadores;
    int caballoDorado;
};

#endif  // RISK_H