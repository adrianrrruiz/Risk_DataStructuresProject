#include "..\\include\\Risk.h"

void Risk::leerContinentes(Risk &juego) {
    ifstream file("Files\\Continentes.txt");
    string linea, nombre;
    int codigo, numeroPaises;

    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, linea);
            istringstream isContinente(linea);
            isContinente >> codigo;
            isContinente.ignore();
            getline(isContinente, nombre, ',');
            isContinente >> numeroPaises;

            Continente continente;
            continente.codigo = codigo;
            continente.nombre = nombre;
            continente.cantPaises = numeroPaises;
            juego.continentes.push_back(continente);
        }
    }
    file.close();
}

void Risk::leerPaises(Risk &juego){
    ifstream file("Files\\Paises.txt");
    string linea, nombre;
    int codigoContinente, codigo;

    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, linea);
            istringstream isPais(linea);
            isPais >> codigoContinente;
            isPais.ignore();
            isPais >> codigo;
            isPais.ignore();
            getline(isPais, nombre);


            Pais pais;
            pais.codigoContinente = codigoContinente;
            pais.codigo = codigo;
            pais.nombre = nombre;

            for(int i = 0; i<= juego.Continentes.size(); i++){
                if(juego.Continentes[i].Codigo == pais.codigoContinente){
                    juego.Continentes[i].paises.push_back(pais);
                }
            }
        }
    }
    file.close();
}

void Risk::leerRelaciones(Risk &juego) {
    ifstream archivo("Files\\Relaciones.txt");
    string linea;
    int codigo;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            iss >> codigo;
            char separador;
            iss >> separador;

            for (int i = 0; i < juego.continentes.size(); i++) {
                for (int j = 0; j < juego.continentes[i].paises.size(); j++) {
                    if (juego.continentes[i].paises[j].codigo == codigo) {
                        int relacionado;
                        while (iss >> relacionado) {
                            juego.continentes[i].paises[j].relaciones.push_back(relacionado);
                            if (iss.peek() == ',') {
                                iss.ignore();
                            }
                        }
                    }
                }
            }
        }
    }
    archivo.close();
}

void Risk::imprimirInformacion(Risk &juego){

    for (const Continente &continente : juego.continentes) {
        cout << continente.codigo << " " << continente.nombre << " " << endl;
        for(const Pais &pais : continente.paises){
            cout << pais.codigo << " " << pais.nombre << " Relaciones: "<<endl;
            for(const int &i : pais.relaciones){
                cout<< i << "||";
            }
            cout << endl;
        }
    }

}