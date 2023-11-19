#ifndef GRAFO_H
#define GRAFO_H

#include "Vertice.h"
#include <map>
#include <iostream>
#include "Arista.h"
#include <vector>
#include <limits>

using namespace std;

class Grafo{
    public:
    map<int, Vertice> vertices;
    map<int, Arista> aristas;

    vector<vector<double>> floydWarshall();
};

#endif  // GRAFO_H