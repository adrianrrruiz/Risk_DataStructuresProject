#include "..\\..\\include\\Grafo\\Grafo.h"

vector<vector<double>> Grafo::floydWarshall()
{
    vector<vector<double>> distancias;
    int n = vertices.size() + 1;
    distancias.resize(n, vector<double>(n, numeric_limits<double>::infinity()));

    // Initialize the diagonal elements to 0
    for (int i = 0; i < n; i++)
    {
        distancias[i][i] = 0;
    }

    // Set the initial distances based on the existing edges
    for (const auto &aristaPar : aristas)
    {
        const Arista &arista = aristaPar.second;
        int origen = arista.idOrigen;
        int destino = arista.idDestino;
        distancias[origen][destino] = arista.peso;
    }

    // Perform the Floyd-Warshall algorithm
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (distancias[i][k] != numeric_limits<double>::infinity() &&
                    distancias[k][j] != numeric_limits<double>::infinity() &&
                    distancias[i][k] + distancias[k][j] < distancias[i][j])
                {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                }
            }
        }
    }

    return distancias;
}
