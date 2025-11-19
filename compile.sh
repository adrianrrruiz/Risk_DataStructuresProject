#!/bin/bash
# Script de compilación para Linux/Unix/Mac
# Uso: ./compile.sh

echo "Compilando proyecto Risk..."

g++ -std=c++11 -o proyecto main.cpp src/*.cpp src/Grafo/*.cpp

if [ $? -eq 0 ]; then
    echo "Compilación exitosa!"
    echo "Ejecutando proyecto..."
    ./proyecto
else
    echo "Error en la compilación!"
    exit 1
fi

