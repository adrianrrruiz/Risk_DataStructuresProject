#ifndef GRAFO_H
#define GRAFO_H

#include "Vertice.h"
#include <map>
#include <iostream>
#include "Arista.h"

using namespace std;

class Grafo{
    public:
    map<int, Vertice> vertices;
    map<int, Arista> aristas;
};

#endif  // GRAFO_H