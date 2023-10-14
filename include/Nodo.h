#ifndef NODO_H
#define NODO_H

#include <iostream>

using namespace std;

class Nodo {
public:
    char simbolo;
    int frecuencia;
    Nodo *izq, *der;
};

#endif  // NODO_H