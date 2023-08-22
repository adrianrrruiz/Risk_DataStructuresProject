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
void Risk::leerDistribucionCartas(Risk &juego) {
    ifstream archivo("Files\\cartas.txt");
    
    if (archivo.is_open()){
        string linea;
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            Carta carta;
            iss >> carta.codigoPais;
            iss.ignore(); // Ignorar la coma
            std::getline(iss, carta.figura);
            juego.cartas.push_back(carta);
        }
        archivo.close();
    }
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
    bool opcionCorrecta = false;
    cout << "escoja el numero de color de su ejercito\n";
    int num;

    for (int i = 0; i < juego.colores.size(); i++) {
        cout << i + 1 << ": " << juego.colores[i] << endl;
    }
    cout << "$ ";

    do {
        cin >> num;
        if (num >= 1 && num <= juego.colores.size()) {
            opcionCorrecta = true;
        } else {
            cout << "opcion incorrecta\n";
        }
    } while (!opcionCorrecta);

    return juego.colores[num - 1];
}
bool Risk::cantidadValida(Risk &juego){
    if(juego.cantidadJugadores > 2 && juego.cantidadJugadores < 7){
        return true;
    }
    else{
        return false;
    }
}

void Risk::eliminarColor(Risk &juego,string color){
    vector<string>::iterator it = find(juego.colores.begin(), colores.end(), color);
    if (it != colores.end()) {
        juego.colores.erase(it);
    }
}

bool Risk::inicializar(Risk &juego){
    
    //leer y crear informacion del juego
    leerContinentes(juego);
    leerPaises(juego);
    leerRelaciones(juego);
    crearPaisesDisponibles(juego);
    leerDistribucionCartas(juego);
    juego.caballoDorado = 4;
    
    string nombre;
    string color;
    int infanteriaXJugador,numeroDado;
    
    //guardar cantidad de participantes
    Jugador jugador;
    do{
        cout <<"ingrese el numero de participantes que jugaran:\n";
        cout <<"recuerde que el juego es de 3-6 participantes\n";
        cout << "$ ";
        cin >> juego.cantidadJugadores;
        system("cls");
    }while(!juego.cantidadValida(juego));


    infanteriaXJugador = evaluarInfanteria(juego);

    //ingreso de los participantes al juego
        for(int i=0; i<juego.cantidadJugadores;i++){
            cout<<"ingrese el nombre del participante: \n";
            cout << "$ ";
            cin>>nombre;
            color=imprimirColores(juego);
            eliminarColor(juego,color);
            cout<<"lance el dado para ver el orden a la hora de escoger territorio\n ";
            system("pause");
            numeroDado= lanzamientoDado();
            cout << "saco un: " << numeroDado << endl;
            system("pause");
            system("cls");
            
            jugador.nombre=nombre;
            jugador.color=color;
            jugador.infanteria=infanteriaXJugador;
            jugador.resultadoDado=numeroDado;
            
            juego.jugadores.push_back(jugador);
        }
        ordenarJugadores(juego.jugadores);
        imprimirJugadores(juego); 

    //elección de territorios
    int contador=0;
    Pais paisEscogido;

    for(int i=0;i<42;i++){
        Jugador& jugadorActual = juego.jugadores[contador];
        cout << "Turno jugador: " << jugadorActual.nombre << endl;
        
        Pais paisEscogido = elegirPais(juego);
        paisEscogido.infanteria = 1;
        jugadorActual.infanteria--;
        jugadorActual.territorios.push_back(paisEscogido);
        borrarPais(juego, paisEscogido);
        
        contador++;
        if (contador == juego.cantidadJugadores) {
            contador = 0;
        }
    }

    //rellenar los territorios con las tropas faltantes

    int codigoAux, cantidadTropas;
    for(int i=0;i<juego.cantidadJugadores;i++){
        do{
            cout << juego.jugadores[i].nombre << ": tienes " << juego.jugadores[i].infanteria << " tropas, donde las deseas repartir?\n";
            juego.jugadores[i].imprimirTerritorios(juego.jugadores[i]);
            cout << "$ ";
            cin>> codigoAux;
            if(juego.jugadores[i].codigoExiste(juego.jugadores[i], codigoAux)){
                cout << "cuantas deseas repatir?\n";
                cout << "$ ";
                cin>> cantidadTropas;
                system("cls");
                if(juego.jugadores[i].cantidadSolicitadaValida(juego.jugadores[i], cantidadTropas)){
                    juego.jugadores[i].aumentarInfanteria(juego.jugadores[i],codigoAux,cantidadTropas);
                }
                else{
                    cout << "cantidad erronea de tropas\n";
                }
            }
            else{
                cout << "territorio no en su propiedad\n";
            }    
        }while(juego.jugadores[i].infanteria!=0);
    }
    return true;
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

Pais Risk::elegirPais(Risk &juego){
    int codigoTerritorio;
    do {
        cout << "Escoja el territorio que desea ocupar:\n";
        for (const Pais& pais : juego.paisesDisponibles) {
            cout << "\t" << pais.codigo << ": " << pais.nombre << endl;
        }
        cout << "$ ";
        cin >> codigoTerritorio;
        system("cls");
        for (const Pais& pais : juego.paisesDisponibles) {
            if (pais.codigo == codigoTerritorio) {
                return pais;
            }
        }
        cout << "Opcion incorrecta. Por favor, elija un territorio valido.\n";
    } while (true);
}

int Risk::lanzamientoDado(){
        int resultado = rand() % 6 + 1;
        return resultado;
}

void Risk:: ordenarJugadores(vector<Jugador> &jugadores){
    int n = jugadores.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if ( jugadores[j]<jugadores[j+1]) {
                swap(jugadores[j], jugadores[j + 1]);
            }
        }
    }
}
void Risk::borrarPais(Risk &juego,Pais paisEscogido){
        for (auto it = juego.paisesDisponibles.begin(); it != juego.paisesDisponibles.end(); ++it) {
            if (it->codigo == paisEscogido.codigo) {
                juego.paisesDisponibles.erase(it);
                break;
            }
        }
}

void Risk::imprimirTerritoriosDeJugadores(Risk &juego){
    for(const Jugador &jugador: juego.jugadores){
        cout << "Terrotorios de " << jugador.nombre << endl;
        for(const Pais &pais : jugador.territorios){
            cout << pais.codigo <<": " <<pais.nombre << endl;
        }
    }
}
void Risk::crearPaisesDisponibles(Risk &juego){
    for (const Continente& continente : juego.continentes) {
        for (const Pais& pais : continente.paises) {
            juego.paisesDisponibles.push_back(pais);
        }
    }
}

bool Risk::turno(Risk &juego, string id){
    int respuesta;
    int codigoAux;
    int codigoPaisAtacar;
    bool menuAtaque=true;

    if(jugadorExiste(juego,id)){

    Jugador& jugador = jugadorEnTurno(juego,id);
        cout << "turno jugador: " << jugador.nombre << endl;
        cout << "Obtener y ubicar nuevas unidades de ejercito.\n" ;
        
        //reclamar tropas obligatorias
        int refuerzo = reclamarTropasObligatorias(juego,jugador);
        cout << "tropas asignadas: " << refuerzo << endl;
        jugador.infanteria+=refuerzo;

        //reclamar tropas por cartas       
        while (true) {
            cout << "Desea intercambiar cartas por tropas? (1 para si / 0 para no):\n";
            cout << "$ ";
            cin >> respuesta;
            
            if (respuesta == 1) {
                if(jugador.cartas.size()>=3){
                    intercambiarCartasXRefuerzos(juego,jugador);
                }
                else{
                    cout << "No tienes suficientes cartas para realizar el intercambio\n";
                }
                
                break;
            } else if (respuesta == 0) {
                cout << "No se realizara el intercambio.\n";
                break;
            } else {
                cout << "Respuesta no valida. Por favor, ingrese 1 para 'si' o 0 para 'no'.\n" ;
            }
        }
        system("pause");
        system("cls");

        //Menu de ataque
        do {
            cout << "Menu de Ataque\n";
            cout << "Que desea hacer?\n";
            cout << "1: atacar un territorio\n";
            cout << "0: dejar de atacar\n";
            cout << "$ ";
            
            cin >> respuesta;
        
            if (respuesta == 1) {
                cout << "Elige un territorio propio el cual limite con el territorio que desees atacar.\n";
                jugador.imprimirTerritorios(jugador);
                cout << "$ ";
                cin >> codigoAux;
                
                if (jugador.codigoExiste(jugador, codigoAux)) {
                    Pais& paisAtaque = jugador.paisSeleccionado(jugador,codigoAux);
                    if(paisAtaque.infanteria>1){
                        codigoPaisAtacar=escogerPaisAAtacar(juego,jugador,paisAtaque);
                        Pais& paisDefensa = delvolverPaisAAtacar(juego,codigoPaisAtacar);
                        Jugador& jugadorDefensa = jugadorDefiende(juego,codigoPaisAtacar);
                        if(jugador.nombre.compare(jugadorDefensa.nombre)==0){
                            cout << "Territorio perteneciente a usted, no puede atacarlo\n";
                        }
                        else{
                            bool conquisto = ataque(paisAtaque,paisDefensa,jugador,jugadorDefensa);
                            if(conquisto){
                                Carta cartaNueva = cartaAleatoria(juego);
                                jugador.cartas.push_back(cartaNueva);
                                borrarCarta(juego,cartaNueva);
                            }

                            if(jugadorDefensa.territorios.size()==0){
                                transferirCartas(jugador,jugadorDefensa);
                                eliminarJugador(juego,jugadorDefensa.nombre);
                            }
                        }  
                    }
                    else{
                        cout<<"no puedes atacar desde este terrotorio porque solo tienes una tropa en el\n";
                    }   
                }
            }
            else if (respuesta == 0) {
                menuAtaque = false;
            }
            else {
                cout << "Respuesta no válida.\n";
            }
        } while (menuAtaque);
    }
    else{
        cout << "jugador no existe\n";
    }
}

int Risk::reclamarTropasObligatorias(Risk& juego, Jugador &jugador){
    int nuevasTropas = jugador.territorios.size()/3;
    bool americaNorte = jugador.poseeContinenteAmericaNorte(jugador);
    bool americaSur = jugador.poseeContinenteAmericaSur(jugador);
    bool europa = jugador.poseeContinenteEuropa(jugador);
    bool africa = jugador.poseeContinenteAfrica(jugador);
    bool asia = jugador.poseeContinenteAsia(jugador);
    bool oceania = jugador.poseeContinenteOceania(jugador);
    if(americaNorte){
        cout << jugador.nombre << " posee el continente: America del Norte\n";
        nuevasTropas +=5;
    }
    if(americaSur){
        cout << jugador.nombre << " posee el continente: America del Sur\n";
        nuevasTropas +=2;
    }
    if(europa){
        cout << jugador.nombre << " posee el continente: Europa\n";
        nuevasTropas +=5;
    }
    if(africa){
        cout << jugador.nombre << " posee el continente: Africa\n";
        nuevasTropas +=3;
    }
    if(asia){
        cout << jugador.nombre << " posee el continente: Asia\n";
        nuevasTropas +=7;
    }
    if(oceania){
        cout << jugador.nombre << " posee el continente: Oceania\n";
        nuevasTropas +=2;
    }
    return nuevasTropas;
}

bool Risk::jugadorExiste(Risk &juego, string id){
    for(int i = 0; i < juego.jugadores.size();i++){
        if(juego.jugadores[i].nombre.compare(id)==0){
            return true;
        }
    }
    return false;
}


Jugador& Risk::jugadorEnTurno(Risk &juego, string id){
    for(int i = 0; i < juego.jugadores.size();i++){
        if(juego.jugadores[i].nombre.compare(id)==0){
            return juego.jugadores[i];
        }
    }
    cout<<"id erroneo\n";
}

int Risk::escogerPaisAAtacar(Risk &juego,Jugador &jugador,Pais &pais){
    int codigoAtaque;
    vector<int> relaciones = pais.getRelaciones(pais);

    set <int> set1(relaciones.begin(),relaciones.end());
    set <int> set2;

    for(const Pais &pais : jugador.territorios){
        set2.insert(pais.codigo);
    }

    vector<int> enAmbos;
    vector<int> posiblesAtaques;
                
    for (int codigo : set1) {
        if (set2.count(codigo) > 0) {
            enAmbos.push_back(codigo);
        }
        else {
            posiblesAtaques.push_back(codigo);
        }
    }
    cout << pais.nombre <<":\n";
    cout << "tropas en el pais:" << pais.infanteria << endl;
    cout << "Paises que te pertenecen relacionados:\n";
    cout <<"-";
    for (int codigo : enAmbos) {
        cout << codigo << "-";
    }
    cout << "\n";
                
    cout << "Paises que se pueden atacar: \n";
    cout <<"-";
    for (int codigo : posiblesAtaques) {
        cout << codigo << "-";
    }
    cout << endl;
    do{
        cout<<"ingrese el pais a atacar: \n";
        cout<<"$";
        cin>>codigoAtaque;
        return codigoAtaque;
    }while(!paisPosibleAAtacar(posiblesAtaques,codigoAtaque));

}
bool Risk::paisPosibleAAtacar(vector <int> &posiblesAtaques, int codigo){
  for(int i=0;i< posiblesAtaques.size();i++){
    if(posiblesAtaques[i] == codigo){
        return true;
    }
  }
  return false;
}

Pais& Risk::delvolverPaisAAtacar(Risk &juego, int codigo){
    for(int i =0;i < juego.jugadores.size();i++){
        for(int j=0; j < juego.jugadores[i].territorios.size();j++){
            if(juego.jugadores[i].territorios[j].codigo == codigo){
                return juego.jugadores[i].territorios[j];
            }
        }
    }
}
bool Risk::ataque(Pais & ataca, Pais & defiende, Jugador& atacante, Jugador& defensor){
    bool conquisto = false;
    cout << "con cuantas tropas deseas atacar "<< atacante.nombre<<" ?\n";
    int tropasAtacantes = cantidadTropasAtacantes(ataca);
    cout << "con cuantas tropas deseas defender "<< defensor.nombre<<" ?\n";
    int tropasDefensa = cantidadTropasDefensoras(defiende);

    ataca.infanteria-=tropasAtacantes;
    defiende.infanteria-=tropasDefensa;

    vector<int>dadosRojos =dados(tropasAtacantes);
    vector<int>dadosBlancos =dados(tropasDefensa);

    sort(dadosRojos.begin(), dadosRojos.end(),greater<int>());
    sort(dadosBlancos.begin(), dadosBlancos.end(),greater<int>());

    int numComparaciones = min(dadosRojos.size(), dadosBlancos.size());

    int victoriasAtacante = 0;
    int victoriasDefensor = 0;

    for (int i = 0; i < numComparaciones; ++i) {
        if (dadosRojos[i] > dadosBlancos[i]) {
            ++victoriasAtacante;
        } else {
            ++victoriasDefensor;
        }
    }

    cout << "Resultado de la batalla:\n";
    cout << "Victorias del atacante: " << victoriasAtacante << "\n";
    cout << "Victorias del defensor: " << victoriasDefensor << "\n";

    defiende.infanteria += tropasDefensa - victoriasDefensor;

    if(defiende.infanteria > 0){
        ataca.infanteria += tropasAtacantes - victoriasAtacante;
    }
    else{
        conquisto = true;
        int tropasSobrevivientes = tropasAtacantes - victoriasAtacante;
        defiende.infanteria = tropasSobrevivientes;
        atacante.territorios.push_back(defiende);
        defensor.eliminarTerritorio(defiende.codigo);
    }
    return conquisto;
}
void Risk::eliminarJugador(Risk& juego,const string& nombre) {
        juego.jugadores.erase(std::remove_if(juego.jugadores.begin(), juego.jugadores.end(),
            [&nombre](const Jugador& jugador) {
                return jugador.nombre == nombre;
            }), juego.jugadores.end());
    }

void Risk::transferirCartas(Jugador& ganador, Jugador& perdedor) {
        ganador.cartas.insert(ganador.cartas.end(), perdedor.cartas.begin(), perdedor.cartas.end());
        perdedor.cartas.clear();
}
Jugador& Risk::jugadorDefiende(Risk &juego, int codigo){
    int jugador ;
    for(int i =0;i < juego.jugadores.size();i++){
        for(int j=0; j < juego.jugadores[i].territorios.size();j++){
            if(juego.jugadores[i].territorios[j].codigo == codigo){
                jugador =i;
            }
        }
    }
    return juego.jugadores[jugador];
}

int Risk::cantidadTropasAtacantes(Pais &atacante){
    int cantidad;
    bool menu = false;
    do{
        if(atacante.infanteria ==2){
            cout << "1 tropa" << endl;
        }
        if(atacante.infanteria==3){
            cout<< "1 tropa" << endl;
            cout<<"2 tropas" << endl; 
        }
        if(atacante.infanteria>=4){
            cout<< "1 tropa" << endl;
            cout<<"2 tropas" << endl;
            cout<<"3 tropas"<< endl;
        }
        cin >> cantidad;
        if(atacante.infanteria == 2 ){
            if(cantidad == 1){
                menu=true;
            }
        }
        if(atacante.infanteria == 3){
            if(cantidad == 1){
                menu=true;
            }
            if(cantidad == 2){
                menu=true;
            }            
        }
        if(atacante.infanteria>=4){
            if(cantidad == 1){
                menu=true;
            }
            if(cantidad == 2){
                menu=true;
            }           
            if(cantidad == 3){
                menu=true;
            }
        }
    }while(!menu);

    return cantidad;
}
int Risk::cantidadTropasDefensoras(Pais &defensor){
    int cantidad;
    bool menu = false;
    do{
        if(defensor.infanteria ==1){
            cout << "1 tropa" << endl;
        }
        if(defensor.infanteria>=2){
            cout<< "1 tropa" << endl;
            cout<<"2 tropas" << endl; 
        }
        cin >> cantidad;
        if(defensor.infanteria == 1){
            if(cantidad == 1){
                menu=true;
            }
        }
        if(defensor.infanteria >= 2){
            if(cantidad == 1){
                menu=true;
            }
            if(cantidad == 2){
                menu=true;
            }            
        }
        
    }while(!menu);

    return cantidad;
}
vector<int> Risk::dados(int cantidad){
    vector<int>dados;
    for(int i=0;i<cantidad;i++){
        int resultado = rand() % 6 + 1;
        dados.push_back(resultado);
    }
    return dados;
}

Carta Risk::cartaAleatoria(Risk& juego){
    int numeroAleatorio = std::rand() % 42 + 1;
    return juego.cartas[numeroAleatorio];
}

void Risk::borrarCarta(Risk& juego, Carta carta){
    for (auto it = juego.cartas.begin(); it != juego.cartas.end(); ++it) {
        if (it->codigoPais == carta.codigoPais) {
            juego.cartas.erase(it);
            break;
        }
    }
}

void Risk::intercambiarCartasXRefuerzos(Risk& juego, Jugador& jugador){
    Carta carta1, carta2, carta3;
    int codigoCarta1, codigoCarta2, codigoCarta3;
    jugador.imprimirCartas(jugador);
    cout<< "seleccione 1 por 1 el codigo de las tres cartas que desea intercambiar\n";
    cin>>codigoCarta1;
    cin>>codigoCarta2;
    cin>>codigoCarta3;
    carta1 = jugador.retornarCarta(jugador,codigoCarta1);
    carta2 = jugador.retornarCarta(jugador,codigoCarta2);
    carta3 = jugador.retornarCarta(jugador,codigoCarta3);

    bool cumple =validarSeleccionCartas(juego,carta1,carta2,carta3);

    if(cumple){
        jugador.infanteria=+juego.caballoDorado;
        anadirInfanteriaSiCoincideConcarta(jugador,codigoCarta1);
        anadirInfanteriaSiCoincideConcarta(jugador,codigoCarta2);
        anadirInfanteriaSiCoincideConcarta(jugador,codigoCarta3);
        cout<<"se añadieron " << juego.caballoDorado << " tropas a su infanteria\n";
        actualizarCaballoDorado(juego);
        jugador.eliminarCartaPorCodigo(carta1.codigoPais);
        jugador.eliminarCartaPorCodigo(carta2.codigoPais);
        jugador.eliminarCartaPorCodigo(carta3.codigoPais);
    }
    else{
        cout << "cartas no cumplen ningun requisito para ser intercambiadas\n";
    }
}

bool Risk::validarSeleccionCartas(Risk& juego,Carta& c1,Carta& c2,Carta& c3){
    bool figurasIguales = (c1.figura == c2.figura && c2.figura == c3.figura);
    bool figurasDiferentes = (c1.figura != c2.figura && c2.figura != c3.figura && c1.figura != c3.figura);
    bool comodinPresente = (c1.figura == "comodin" || c2.figura == "comodin" || c3.figura == "comodin");

    return figurasIguales || figurasDiferentes || (comodinPresente && (figurasIguales || figurasDiferentes));
}

void Risk::actualizarCaballoDorado(Risk &juego){
    int valor = juego.caballoDorado;

    if(valor == 4){
        juego.caballoDorado +=2;
    }
    if(valor == 6){
        juego.caballoDorado +=2;
    }
    if(valor == 8){
        juego.caballoDorado +=2;
    }
    if(valor == 10){
        juego.caballoDorado +=2;
    }
    if(valor == 12){
        juego.caballoDorado +=3;
    }
    if(valor >= 15){
        juego.caballoDorado +=5;
    }    
}
void Risk::anadirInfanteriaSiCoincideConcarta(Jugador &jugador, int codigo){
        for(int j=0; j < jugador.territorios.size();j++){
            if(jugador.territorios[j].codigo == codigo){
                jugador.territorios[j].infanteria+=2;
                cout << "se insertaron 2 tropas al territorio: " << jugador.territorios[j].nombre << endl;
            }
        }
}