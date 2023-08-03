#include <iostream>
#include <string>

using namespace std;

int main() {
    string comando;
    bool ciclo = true, inicializado = false, partida = false;

    do {
        cout << "$";
        getline(cin, comando);

        if (comando == "help") {
            cout << "Lista de comandos:" << endl;
            cout << "inicializar: Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas" << endl;
            cout << "turno <id_jugador>: Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)" << endl;
            cout << "salir: Termina la ejecucion de la aplicacion" << endl;
            cout << "guardar <nombre_archivo>: El estado actual del juego es guardado en un archivo de texto" << endl;
            cout << "guardar_comprimido <nombre_archivo>: El estado actual del juego es guardado en un archivo binario (con extensión .bin)" << endl;
            cout << "inicializar <nombre_archivo>: Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>" << endl;
            cout << "costo_conquista <territorio>: El programa debe calcular el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario" << endl;
            cout << "conquista_mas_barata: De todos los territorios posibles, calcular aquel que pueda implicar un menor numero de unidades de ejercito perdidas" << endl;
            cout << "help: Muestra informacion de ayuda del comando especificado." << endl;
        } else if (comando == "inicializar" && !inicializado) {
            cout << "inicializacion satisfactoria" << endl;
            inicializado = true;
            partida = true;
        } else if (comando == "inicializar" && inicializado) {
            cout << "Juego en curso" << endl;
        } else if (comando == "salir") {
            ciclo = false;
        } else if (comando == "turno") {
            cout << "comando valido" << endl;
        } else if (comando == "guardar") {
            cout << "comando valido" << endl;
        } else if (comando == "guardar_comprimido") {
            cout << "comando valido" << endl;
        } else if (comando == "costo_conquista") {
            cout << "comando valido" << endl;
        } else if (comando == "conquista_mas_barata") {
            cout << "comando valido" << endl;
        } else {
            cout << "comando invalido" << endl;
        }
    } while (ciclo);

    return 0;
}

