#include <iostream>
#include <string>
#include <vector>

using namespace std;

void imprimirListaComandos();

int main(int argc, char* argv[]) {
    string comando;
    bool enEjecucion = true, inicializado = false, jugando = false;
    vector<int> idJugadores;
    vector<int>::iterator itIdJugadores;

    cout << "Bienvido a Risk! Desarrollado por: Adrian, Juliana y Daniel\n";
    do {
        cout << "\033[0;33m$ \033[0m";
        cin >> comando;

        if (comando == "help" || comando == "ayuda") {
            imprimirListaComandos();
        } else if (comando == "inicializar") {
            if (!inicializado){
                cout << "El juego se ha inicializado correctamente\n";
                inicializado = true;
            }else {
                cout << "El juego ya ha sido inicializado\n";
            }
        } else if (comando == "salir" || comando == "exit") {
            enEjecucion = false;
        } else if (comando == "turno") {
            if(!inicializado){
                cout << "Esta partida no ha sido inicializada correctamente.\n";
            }else if(!jugando){
                cout << "Esta partida ya tuvo un ganador\n";
            }
        } else if (comando == "guardar") {
            cout << "comando valido\n";
        } else if (comando == "guardar_comprimido") {
            cout << "comando valido\n";
        } else if (comando == "costo_conquista") {
            cout << "comando valido\n";
        } else if (comando == "conquista_mas_barata") {
            cout << "comando valido\n";
        } else {
            cout << "comando invalido\n";
        }
    } while (enEjecucion);

    return 0;
}

void imprimirListaComandos(){
    cout << "\033[0;42m****************** LISTA DE COMANDOS ******************\033[0m\n";
    cout << "\033[0;36m- inicializar \033[0m-> Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas\n";
    cout << "\033[0;36m- turno <id_jugador> \033[0m-> Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)\n";
    cout << "\033[0;36m- salir \033[0m-> Termina la ejecucion de la aplicacion\n";
    cout << "\033[0;36m- guardar <nombre_archivo> \033[0m-> El estado actual del juego es guardado en un archivo de texto\n";
    cout << "\033[0;36m- guardar_comprimido <nombre_archivo> \033[0m-> El estado actual del juego es guardado en un archivo binario (con extensi�n .bin)\n";
    cout << "\033[0;36m- inicializar <nombre_archivo> \033[0m-> Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>\n";
    cout << "\033[0;36m- costo_conquista <territorio> \033[0m-> El programa debe calcular el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario\n";
    cout << "\033[0;36m- conquista_mas_barata \033[0m-> De todos los territorios posibles, calcular aquel que pueda implicar un menor numero de unidades de ejercito perdidas\n";
    cout << "\033[0;36m- help \033[0m-> Muestra informacion de ayuda del comando especificado.\n";
}