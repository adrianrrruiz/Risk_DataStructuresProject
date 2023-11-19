#ifndef RISK_H
#define RISK_H

#include <iostream>
#include <vector>
#include "Continente.h"
#include "Carta.h"
#include "Jugador.h"
#include "Nodo.h"
#include "Grafo\\Grafo.h"
#include "Grafo\\Vertice.h"
#include "Grafo\\Arista.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <set>
#include <unordered_map>
#include <map>
#include <queue>
#include <bitset>

using namespace std;


struct comp{
    bool operator()(Nodo *i, Nodo *d)
    {
        return i->frecuencia > d->frecuencia;
    }
};

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
    
    //segundo avance

    void guardarPartida(Risk& juego, string nombreArchivo);
    bool cargarPartida(Risk& juego, string nombreArchivo);
    void corregirCartas(Risk& juego);
    void codificar(Nodo *raiz, string str, unordered_map<char, string> &CodigoHuffman);
    void decodificar(Nodo *raiz, int &indice, string str, string &textoNormal);
    void crearArbol(map<char, long> &tablaFrecuencia, Nodo *&raiz);
    void crearTablaFrecuencia(map<char, long> &tablaFrecuencia, string texto);
    string generarCodigoCodificado(string texto, unordered_map<char, string> diccionarioHuffman);
    string crearCadenaDelArchivoTxt(string nombreArchivo);
    void guardarComprimido(string nombreArchivo);
    int modificarCadena(string &cadenaCodificada);
    void pasarDeStringABytes(string cadenaCodificada, vector<bitset<8>> &cadenaComprimida);
    Nodo *getNode(char simbolo, int frecuencia, Nodo *izq, Nodo *der);
    void cargarComprimido(string nombreArchivo);
    void escribirEnArchivoDescompresion(string nombreArchivo, string textoNormal);
    string pasarDeCodificadaANormal(string cadenaCodificada, Nodo *raiz);

    //tercer avance
    void crearGrafo(Risk &juego);
    void mostrarGrafo(Risk &juego);
    void actualizarGrafo(Risk &juego);
    void imprimirDistancias(vector<vector<double>> distancias);
    void costo_Conquista(Risk &juego, Jugador jugador, int &territorioDado, int &territorioMasCercano, double &distanciaMasCorta);
    void imprimirTerritoriosDeOtrosJugadores(Risk &juego, Jugador jugador1);
    bool codigoSolicitadoAdecuado(Risk &juego,Jugador jugador1,int codigo);
    void conquistaMasBarata(Risk &juego, Jugador jugador1, int &territorioDado, int &territorioMasCercano, double &distanciaMasCorta);

    vector<int> dados(int cantidad);
    vector<Continente> continentes;
    vector<Pais> paisesDisponibles;
    vector<Jugador> jugadores;
    vector <Carta> cartas;
    vector <string> colores = {"Verde", "Azul", "Rojo", "Amarillo", "Negro", "Gris"};
    Grafo grafo;
    int cantidadJugadores;
    int caballoDorado;
};

#endif  // RISK_H