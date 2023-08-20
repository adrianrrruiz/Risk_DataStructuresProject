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

            for(int i = 0; i<= juego.continentes.size(); i++){
                if(juego.continentes[i].codigo == pais.codigoContinente){
                    juego.continentes[i].paises.push_back(pais);
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
                    if (juego.continentes[i].paises[j].codigo.compare(to_string(codigo))) {
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

void Risk::inicializar(Risk &juego){
    
    leerContinentes(juego);
    leerPaises(juego);
    leerRelaciones(juego);

    cout <<"ingrese el numero de participantes que jugaran:\n";
    cin >> juego.cantidadJugadores;

    if(juego.cantidadJugadores < 3){
        cout << "Cantidad erronea, el juego necesita de 3 - 6 jugadores\n";
        return;
    }
    else{
        for(int i=0; i<juego.cantidadJugadores;i++){
            cout<<"ingrese el nombre de los participante: \n";
            cin>>juego.jugadores[i].nombre;
            imprimirColores(juego);
            cin>>juego.jugadores[i].color;
        } 
    }


}

void Risk::imprimirColores(Risk &juego){
    cout<< "escoja el color de su ejercito\n";
    for(int i =0; i<juego.colores.size(); i++){
        cout << i+1 << ": " << juego.colores[i] << endl;
    }
}

void Risk::eliminarColor(Risk &juego,string color){
    vector<string>::iterator it = find(juego.colores.begin(), colores.end(), color);
    if (it != colores.end()) {
        juego.colores.erase(it);
    }
}