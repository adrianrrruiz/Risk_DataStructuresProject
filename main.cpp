#include <iostream>
#include <string>
#include <vector>

using namespace std;

void imprimirListaComandos();

void separarCadena(string &linea, string &C1, string &C2,string &C3);

int main(int argc, char* argv[]) {
    string linea;
    string C1;
    string C2;
    string C3;
    bool enEjecucion = true, inicializado = false, jugando = false;
    vector<int> idJugadores;
    vector<int>::iterator itIdJugadores;

    cout << "Bienvido a Risk! Desarrollado por: Adrian, Juliana y Daniel\n";
    do {
        cout << "$ ";
        getline(cin, linea);
        separarCadena(linea,C1,C2,C3);

        if (C1 == "help" || C1 == "ayuda") {
            imprimirListaComandos();
        }

        else if (C1 == "inicializar" && (C2 == "--help" || C2 == "--ayuda" || C2 == "")) {
            if(C2 == "--help" || C2 == "--ayuda" ){
                cout << "-> Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas\n";
                cout << "<nombre_archivo> -> Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>\n";
            }
            else{
                if (!inicializado){
                    cout << "El juego se ha inicializado correctamente\n";
                    inicializado = true;
                }else {
                    cout << "El juego ya ha sido inicializado\n";
                }
            }
        }
        else if(C1 == "inicializar" && (C2 != "--help" || C2 != "--ayuda") && C2 !=""){
            if(C3 == "--help" || C3 == "--ayuda" ){
                cout << "-> Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>\n";
            }
            else{
                if (inicializado){
                    cout << " El juego ya ha sido inicializado.\n";
                    inicializado = true;
                }else {
                    cout << C2 <<" no contiene informacion valida para inicializar el juego.\n";
                }
            }
        }

        else if (C1 == "salir" || C1 == "exit") {
            if(C2 == "--help" || C2 == "--ayuda" ){
                cout << "-> Termina la ejecucion de la aplicacion\n";
            }
            else{
                enEjecucion = false;
            }
        }

        else if (C1 == "turno") {
            if(C2 == "--help" || C2 == "--ayuda" ){
                cout << "-> Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)\n";
            }
            else{
                if(!inicializado){
                    cout << "Esta partida no ha sido inicializada correctamente.\n";
                }else if(!jugando){
                    cout << "Esta partida ya tuvo un ganador\n";
                }
            }
        }

        else if (C1 == "guardar") {
            if(C2 == "--help" || C2 == "--ayuda" ){
                cout << "<nombre_archivo> -> El estado actual del juego es guardado en un archivo de texto\n";
            }
            else{
                if (!inicializado){
                    cout << "Esta partida no ha sido inicializada correctamente.\n";
                }
                else if(inicializado){
                    cout << "La partida ha sido guardada correctamente.\n";
                }
                else{
                    cout << "La partida no ha sido guardada correctamente.\n";
                }
            }
        }

        else if (C1 == "guardar_comprimido") {
            if(C2 == "--help" || C2 == "--ayuda" ){
                cout << "<nombre_archivo> -> El estado actual del juego es guardado en un archivo binario (con extensi�n .bin)\n";
            }
            else{
                if (!inicializado){
                    cout << "Esta partida no ha sido inicializada correctamente.\n";
                }
                else if(inicializado){
                    cout << "La partida ha sido guardada correctamente.\n";
                }
                else{
                    cout << "La partida no ha sido guardada correctamente.\n";
                }
            }
        }

        else if (C1 == "costo_conquista") {
            if(C2 == "--help" || C2 == "--ayuda" ){
                cout << "<territorio> -> El programa debe calcular el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario\n";
            }
            else{
                if (!inicializado){
                    cout << "Esta partida no ha sido inicializada correctamente.\n";
                }
                else if(!jugando){
                    cout << "Esta partida ya tuvo un ganador.\n";
                }
                else{
                    cout << "comando valido\n";
                }
            }
        }

        else if (C1 == "conquista_mas_barata") {
            if(C2 == "--help" || C2 == "--ayuda" ){
                cout << "De todos los territorios posibles, calcular aquel que pueda implicar un menor numero de unidades de ejercito perdidas\n";
            }
            else{
                if (!inicializado){
                    cout << "Esta partida no ha sido inicializada correctamente.\n";
                }
                else if(!jugando){
                    cout << "Esta partida ya tuvo un ganador.\n";
                }
                else{
                    cout << "comando valido\n";
                }
            }
        }

        else {
            cout << "comando invalido\n";
        }

    } while (enEjecucion);

    return 0;
}

void separarCadena(string &linea, string &C1, string &C2, string &C3){
    size_t firstSpacePos = linea.find(" ");

    if (firstSpacePos != std::string::npos) {
        C1 = linea.substr(0, firstSpacePos);
        size_t secondSpacePos = linea.find(" ", firstSpacePos + 1);

        if (secondSpacePos != std::string::npos) {
            C2 = linea.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);
            C3 = linea.substr(secondSpacePos + 1);
        } else {
            C2 = linea.substr(firstSpacePos + 1);
            C3 = "";
        }
    } else {
        C1 = linea;
        C2 = "";
        C3 = "";
    }
}
void imprimirListaComandos(){
    cout << "****************** LISTA DE COMANDOS ******************\n";
    cout << "- inicializar \033[0m-> Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas\n";
    cout << "- turno <id_jugador> \033[0m-> Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)\n";
    cout << "- salir \033[0m-> Termina la ejecucion de la aplicacion\n";
    cout << "- guardar <nombre_archivo> \033[0m-> El estado actual del juego es guardado en un archivo de texto\n";
    cout << "- guardar_comprimido <nombre_archivo> \033[0m-> El estado actual del juego es guardado en un archivo binario (con extensi�n .bin)\n";
    cout << "- inicializar <nombre_archivo> \033[0m-> Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>\n";
    cout << "- costo_conquista <territorio> \033[0m-> El programa debe calcular el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario\n";
    cout << "- conquista_mas_barata \033[0m-> De todos los territorios posibles, calcular aquel que pueda implicar un menor numero de unidades de ejercito perdidas\n";
    cout << "- help \033[0m-> Muestra informacion de ayuda del comando especificado.\n";
}
