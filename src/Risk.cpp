#include "../include/Risk.h"

void Risk::leerContinentes(Risk &juego) {
    ifstream file("Files/Continentes.txt");
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
    ifstream file("Files/Paises.txt");
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
string Risk::imprimirColores(Risk &juego){
    cout<< "escoja el numero de color de su ejercito\n";
    int num;
    for(int i =0; i<juego.colores.size(); i++){
        cout << i+1 << ": " << juego.colores[i] << endl;
    }
    cin>>num;
    switch(num) {
        case 1: return juego.colores[0];
        break;
        case 2: return juego.colores[1];
        break;
        case 3: return juego.colores[2];
        break;
        case 4: return juego.colores[3];
        break;
        case 5: return juego.colores[4];
        break;
        case 6: return juego.colores[5];
        break;
        default:
        cout << "opcion incorrecta\n";
        break;
    }
}

void Risk::eliminarColor(Risk &juego,string color){
    vector<string>::iterator it = find(juego.colores.begin(), colores.end(), color);
    if (it != colores.end()) {
        juego.colores.erase(it);
    }
}

void Risk::inicializar(Risk &juego){
    
    leerContinentes(juego);
    leerPaises(juego);
    leerRelaciones(juego);
    
    string nombre;
    string color;
    int infanteriaXJugador,numeroDado;

    Jugador jugador;
    cout <<"ingrese el numero de participantes que jugaran:\n";
    cin >> juego.cantidadJugadores;

    infanteriaXJugador = evaluarInfanteria(juego);

    if(juego.cantidadJugadores < 3){
        cout << "Cantidad erronea, el juego necesita de 3 - 6 jugadores\n";
        return;
    }
    //ingreso de los participantes al juego
    else{
        for(int i=0; i<juego.cantidadJugadores;i++){
            cout<<"ingrese el nombre de los participante: \n";
            cin>>nombre;
            color=imprimirColores(juego);
            eliminarColor(juego,color);
            cout<<"lance el dado para ver el orden a la hora de escoger territorio\n ";
            system("pause");
            numeroDado= lanzamientoDado();
            cout << "saco un: " << numeroDado << endl;
            
            jugador.nombre=nombre;
            jugador.color=color;
            jugador.infanteria=infanteriaXJugador;
            jugador.resultadoDado=numeroDado;
            
            juego.jugadores.push_back(jugador);
        }
        imprimirJugadores(juego); 
    }
    //elección de territorios
    for(int i=0;i<42;i++){

    }
}

void Risk::imprimirJugadores(Risk &juego){
    for(const Jugador &jugador : juego.jugadores){
            cout <<"Jugador: " << jugador.nombre <<" Color: "<<jugador.color << "\n";
    }
}

int Risk::evaluarInfanteria(Risk &juego){
    switch(juego.cantidadJugadores){
        case 3:
            return 35;
            break;
        case 4:
            return 30;
            break;
        case 5:
            return 25;
            break;
        case 6:
            return 20;
            break;
    }
}

int Risk::elegirPais(Risk &juego){
    int codigoTerritorio;
        cout<< "escoja el Territorio que desea ocupar\n";
        for(const Continente continente : juego.continentes){
            cout<<"Continente: " << continente.nombre << endl;
            for(const Pais pais : continente.paises){
                cout <<"\t"<< pais.codigo << ": " << pais.nombre << endl;
            }
        }
        cin >> codigoTerritorio;
        return codigoTerritorio;
}

int Risk::lanzamientoDado(){
        int resultado = rand() % 6 + 1;
        return resultado;
}