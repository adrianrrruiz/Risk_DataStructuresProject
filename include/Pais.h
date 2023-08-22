#ifndef PAIS_H
#define PAIS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;

class Pais {
public:
    vector<int>getRelaciones(Pais &pais);
    int codigoContinente;
    int codigo;
    string nombre;
    vector<int> relaciones;
    int infanteria;
};

#endif  // PAIS_H