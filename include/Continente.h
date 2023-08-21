#ifndef CONTINENTE_H
#define CONTINENTE_H

#include <iostream>
#include <vector>
#include <string>

#include "Pais.h"

using namespace std;

class Continente {
public:
    int codigo;
    string nombre;
    int cantPaises;
    vector<Pais> paises;
};

#endif  // CONTINENTE_H