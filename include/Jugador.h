#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include "Pais.h"
#include "Carta.h"


using namespace std;

class Jugador {
public:
    bool cantidadSolicitadaValida(Jugador& jugador,int cantidadTropas);
    bool codigoExiste(Jugador& jugador,int codigo);
    bool validarTropasPais(Jugador& jugador, int codigoTerritorio, int cantTropas);
    bool operator<(const Jugador& otroJugador) const;
    void imprimirTerritorios(Jugador &jugador);
    void aumentarInfanteria(Jugador& otroJugador,int codigo, int cantidad);
    bool restarInfanteria(Jugador& jugador,int codigo,int cantidad);
    bool relacionConPais(Jugador& jugador, int codigoPrimerTerritorio, int codigoSegundoTerritorio);
    bool poseeContinenteAmericaNorte(Jugador& jugador) const;
    bool poseeContinenteAmericaSur(Jugador& jugador) const;
    bool poseeContinenteEuropa(Jugador& jugador) const;
    bool poseeContinenteAfrica(Jugador& jugador) const;
    bool poseeContinenteAsia(Jugador& jugador) const;
    bool poseeContinenteOceania(Jugador& jugador) const;
    Pais& paisSeleccionado(Jugador& jugador,int codigo);
    void eliminarTerritorio(int codigo);
    void imprimirCartas(Jugador &jugador);
    void eliminarCartaPorCodigo(int codigo);
    Carta retornarCarta(Jugador& jugador, int codigo);

    string color;
    string nombre;
    vector<Pais> territorios;
    vector<Carta> cartas;
    int infanteria = 0;
    int resultadoDado;
};

#endif  // JUGADOR_H