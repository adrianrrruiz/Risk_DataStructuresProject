//Desarrollado por Adrian Ruiz, Juliana Bejarano y Daniel Carvajal
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "include/Risk.h"

using namespace std;

void imprimirListaComandos();

void separarCadena(string &linea, string &comando, string &param1,string &param2);

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    string linea;
    string comando;
    string param1;
    string param2;
    bool enEjecucion = true, inicializado = false, jugando = false;
    vector<int> idJugadores;
    vector<int>::iterator itIdJugadores;
    Risk juego;
    system("cls");
    cout << "\n---- BIENVENIDO A RISK ----\n"; 
    cout << "Desarrollado por: Adrian, Juliana y Daniel\n";
    do {
        cout << "$ ";
        getline(cin, linea);
        separarCadena(linea,comando,param1,param2);

        if (comando == "help" || comando == "ayuda") {
            imprimirListaComandos();
        }
        else if (comando == "inicializar" && (param1 == "--help" || param1 == "--ayuda" || param1 == "")) {
            if(param1 == "--help" || param1 == "--ayuda" ){
                cout << "\ninicializar -> Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas\n";
                cout << "inicializar <nombre_archivo> -> Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>\n\n";
            }else{
                if (!inicializado){
                    system("cls");
                    bool finalizarInicializacion=juego.inicializar(juego);
                    if(finalizarInicializacion){
                        cout << "\nEl juego se ha inicializado correctamente!\n\n";
                        inicializado = true;
                        jugando = true;
                    }
                    cin.ignore();
                }else {
                    cout << "\nEl juego YA ha sido inicializado!\n\n";
                }
            }
        }
        else if(comando == "inicializar" && (param1 != "--help" || param1 != "--ayuda") && param1 !=""){
            if(param2 == "--help" || param2 == "--ayuda" ){
                cout << "\ninicializar -> Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>\n\n";
            }else{
                if (!inicializado){
                    juego.cargarComprimido(param1); // Para probar inicializar con archivo binario
                    bool finalizarInicializacion= juego.cargarPartida(juego,param1);
                    if(finalizarInicializacion){
                        cout << "\nEl juego se ha inicializado correctamente!\n\n";
                        inicializado = true;
                        jugando = true;
                    }
                }else {
                    cout << "\n" << param1 <<" no contiene informacion valida para inicializar el juego.\n\n";
                }
            }
        }
        else if (comando == "salir" || comando == "exit") {
            if(param1 == "--help" || param1 == "--ayuda" ){
                cout << "\nsalir -> Termina la ejecucion de la aplicacion\n\n";
            }else{
                enEjecucion = false;
            }
        }
        else if (comando == "turno") {
            if(param1 == "--help" || param1 == "--ayuda" ){
                cout << "\nturno -> Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)\n\n";
            }else{
                if(!inicializado){
                    cout << "\nEsta partida NO ha sido inicializada correctamente.\n\n";
                }else if(!jugando){
                    cout << "\nEsta partida ya tuvo un ganador :(\n\n";
                }
                else{
                    jugando = (!juego.turno(juego,param1));
                    cin.ignore();
                }
            }
        }
        else if (comando == "guardar") {
            if(param1 == "--help" || param1 == "--ayuda" ){
                cout << "\nguardar <nombre_archivo> -> El estado actual del juego es guardado en un archivo de texto\n\n";
            }else{
                if (!inicializado){
                    cout << "\nEsta partida NO ha sido inicializada correctamente\n\n";
                }
                else if(inicializado){
                    juego.guardarPartida(juego, param1);
                    cout << "\nLa partida ha sido guardada correctamente :)\n\n";
                    cout << "$ ";
                    cin.ignore();
                }
                else{
                    cout << "\nLa partida NO ha sido guardada correctamente\n\n";
                }
            }
        }
        else if (comando == "guardar_comprimido") {
            if(param1 == "--help" || param1 == "--ayuda" ){
                cout << "\nguardar_comprimido <nombre_archivo> -> El estado actual del juego es guardado en un archivo binario (con extension .bin)\n\n";
            }
            else{
                if (!inicializado){
                    cout << "\nEsta partida NO ha sido inicializada correctamente :(\n\n";
                }
                else if(inicializado){
                    juego.guardarComprimido(param1);

                    cout << "\nLa partida ha sido guardada correctamente!\n\n";
                    cout << "$ ";
                    cin.ignore();
                }
                else{
                    cout << "\nLa partida no ha sido guardada correctamente!\n\n";
                }
            }
        }
        else if (comando == "costo_conquista") {
            if(param1 == "--help" || param1 == "--ayuda" ){
                cout << "\ncosto_conquista <territorio> -> El programa debe calcular el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario\n\n";
            }else{
                if (!inicializado){
                    cout << "\nEsta partida NO ha sido inicializada correctamente :(\n\n";
                }
                else if(!jugando){
                    cout << "\nEsta partida ya tuvo un ganador :(\n\n";
                }
                else{
                    cout << "\nComando valido\n\n";
                }
            }
        }
        else if (comando == "conquista_mas_barata") {
            if(param1 == "--help" || param1 == "--ayuda" ){
                cout << "\nDe todos los territorios posibles, calcular aquel que pueda implicar un menor numero de unidades de ejercito perdidas\n\n";
            }else{
                if (!inicializado){
                    cout << "\nEsta partida NO ha sido inicializada correctamente :(\n\n";
                }
                else if(!jugando){
                    cout << "\nEsta partida ya tuvo un ganador :(\n\n";
                }
                else{
                    cout << "\nComando valido\n\n";
                }
            }
        }

        else {
            cout << "\nComando invalido. Pruebe 'help' para ver todos los comandos.\n\n";
        }
    } while (enEjecucion);

    return 0;
}

//Nombre: separarCadena
//Objetivo: Recibir todo el input y separarlo por espacios para usar de los parámetros de los comandos 
//Entradas: Linea completa, comando, primer y segundo parámetro
//Salidas: Variables con sus respectivos valores
void separarCadena(string &linea, string &comando, string &param1, string &param2){
    size_t firstSpacePos = linea.find(" ");

    if (firstSpacePos != string::npos) {
        comando = linea.substr(0, firstSpacePos);
        size_t secondSpacePos = linea.find(" ", firstSpacePos + 1);

        if (secondSpacePos != string::npos) {
            param1 = linea.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);
            param2 = linea.substr(secondSpacePos + 1);
        } else {
            param1 = linea.substr(firstSpacePos + 1);
            param2 = "";
        }
    } else {
        comando = linea;
        param1 = "";
        param2 = "";
    }
}

//Nombre: imprimirListaComandos
//Objetivo: Imprimir una lista de comandos con la funcionalidad de cada uno 
//Entradas: Ninguna
//Salidas: Lista de comandoss
void imprimirListaComandos(){
    cout << "\n****************** LISTA DE COMANDOS ******************\n";
    cout << "- inicializar                         -> Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas\n";
    cout << "- turno <id_jugador>                  -> Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)\n";
    cout << "- salir                               -> Termina la ejecucion de la aplicacion\n";
    cout << "- guardar <nombre_archivo>            -> El estado actual del juego es guardado en un archivo de texto\n";
    cout << "- guardar_comprimido <nombre_archivo> -> El estado actual del juego es guardado en un archivo binario (con extensi�n .bin)\n";
    cout << "- inicializar <nombre_archivo>        -> Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>\n";
    cout << "- costo_conquista <territorio>        -> El programa debe calcular el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario\n";
    cout << "- conquista_mas_barata                -> De todos los territorios posibles, calcular aquel que pueda implicar un menor numero de unidades de ejercito perdidas\n";
    cout << "- help                                -> Muestra informacion de ayuda del comando especificado.\n\n";
}