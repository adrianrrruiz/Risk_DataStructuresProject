#ifndef PAIS_H
#define PAIS_H

#include <iostream>
#include <vector>

using namespace std;

class Pais {
public:
    string codigoContinente;
    string codigo;
    string nombre;
    vector<int> relaciones;
    int infanteria;
};

#endif  // PAIS_H