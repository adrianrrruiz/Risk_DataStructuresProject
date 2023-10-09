#include "..\\include\\Risk.h"

void Risk::leerContinentes(Risk &juego) {
    try{
        ifstream file("files\\Continentes.txt");
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
    catch(exception& e){
        e.what();
        
    }
    
    
}

void Risk::leerPaises(Risk &juego){
    ifstream file("files\\Paises.txt");
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
    ifstream archivo("files\\Relaciones.txt");
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
    ifstream archivo("files\\cartas.txt");
    
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
    cout << "\n==== Escoja el numero de color de su ejercito ====\n";
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
            cout << "---- Opcion incorrecta ----\n";
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
        cout <<"Ingrese el numero de participantes que jugaran:\n";
        cout <<"(Recuerde que el juego es de 3-6 participantes)\n";
        cout << "$ ";
        cin >> juego.cantidadJugadores;
    }while(!juego.cantidadValida(juego));


    infanteriaXJugador = evaluarInfanteria(juego);

    //ingreso de los participantes al juego
        for(int i=0; i<juego.cantidadJugadores;i++){
            cout<<"\nIngrese el nombre del participante No. " << i+1 << ":\n";
            cout << "$ ";
            cin>>nombre;
            color=imprimirColores(juego);
            eliminarColor(juego,color);
            cout<<"==== Se lanzara el DADO para ver el ORDEN a la hora de escoger territorio ====\n";
            numeroDado= lanzamientoDado();
            cout << "- Saco un: " << numeroDado << endl;
            
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
        cout << "\n==== TURNO DE " << jugadorActual.nombre << " ====\n";
        
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
            cout <<"\n==== " << juego.jugadores[i].nombre << " tienes " << juego.jugadores[i].infanteria << " tropas, donde las deseas repartir? ====\n";
            juego.jugadores[i].imprimirTerritorios(juego.jugadores[i]);
            cout << "$ ";
            cin>> codigoAux;
            if(juego.jugadores[i].codigoExiste(juego.jugadores[i], codigoAux)){
                cout << "Cuantas deseas repatir?\n";
                cout << "$ ";
                cin>> cantidadTropas;
                if(juego.jugadores[i].cantidadSolicitadaValida(juego.jugadores[i], cantidadTropas)){
                    juego.jugadores[i].aumentarInfanteria(juego.jugadores[i],codigoAux,cantidadTropas);
                }
                else{
                    cout << "---- Cantidad erronea de tropas ----\n";
                }
            }
            else{
                cout << "---- Territorio no en su propiedad ----\n";
            }    
        }while(juego.jugadores[i].infanteria!=0);
    }
    return true;
}

void Risk::imprimirJugadores(Risk &juego){
    cout << "\n==== JUGADORES CREADOS ====\n";
    for(const Jugador &jugador : juego.jugadores){
            cout <<"Jugador: " << jugador.nombre <<"   -   Color: "<<jugador.color << "\n";
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
        for (const Pais& pais : juego.paisesDisponibles) {
            if (pais.codigo == codigoTerritorio) {
                return pais;
            }
        }
        cout << "---- Opcion incorrecta. Por favor, elija un territorio valido. ----\n";
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
    int aux, cantidadTropas;
    bool menuAtaque=true;

    if(jugadorExiste(juego,id)){

    Jugador& jugador = jugadorEnTurno(juego,id);
        cout << "\n==== TURNO DE " << jugador.nombre << " ====\n";
        cout << "1ra FASE : Obtener y ubicar nuevas unidades de ejercito.\n\n" ;
        
        //reclamar tropas obligatorias
        int refuerzo = reclamarTropasObligatorias(juego,jugador);
        cout << "Tropas asignadas: " << refuerzo << endl;
        jugador.infanteria= jugador.infanteria + refuerzo;

        //asignar tropas de refuerzo
        do{
            cout <<"\n==== " << jugador.nombre << " tienes " << jugador.infanteria << " tropas de REFUERZO, donde las deseas repartir? ====\n";
            jugador.imprimirTerritorios(jugador);
            cout << "$ ";
            cin>> aux;
            if(jugador.codigoExiste(jugador, aux)){
                cout << "Cuantas deseas repatir?\n";
                cout << "$ ";
                cin>> cantidadTropas;
                if(jugador.cantidadSolicitadaValida(jugador, cantidadTropas)){
                    jugador.aumentarInfanteria(jugador,aux,cantidadTropas);
                }
                else{
                    cout << "---- Cantidad erronea de tropas ----\n";
                }
            }
            else{
                cout << "---- Territorio no en su propiedad ----\n";
            }    
        }while(jugador.infanteria!=0);

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
                    cout << "---- No tienes suficientes cartas para realizar el intercambio ----\n";
                }
                
                break;
            } else if (respuesta == 0) {
                cout << "---- No se realizara el intercambio ----\n";
                break;
            } else {
                cout << "---- Respuesta no valida. Por favor, ingrese 1 para 'si' o 0 para 'no' ----\n" ;
            }
        }

        //Menu de ataque
        cout << "\n\n2da FASE: Ataque\n";
        do {
            cout << "\n==== MENU DE ATAQUE ====\n";
            cout << "Que desea hacer?\n";
            cout << "1: Atacar un territorio\n";
            cout << "0: Dejar de atacar\n";
            cout << "$ ";
            
            cin >> respuesta;
        
            if (respuesta == 1) {
                cout << "==== Elige un territorio propio el cual LIMITE con el territorio que desees ATACAR ====\n";
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
                            cout << "---- Territorio perteneciente a usted, no puede atacarlo ----\n";
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
                                if(jugador.territorios.size()==42){
                                    cout << "\n\n---- Termino la partida " << jugador.nombre << " es el ganador. Felicitaciones!\n";
                                    return true;
                                }
                            }
                        }  
                    }
                    else{
                        cout<<"---- No puedes atacar desde este territorio porque solo tienes una tropa en el\n";
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

        cout << "\n\n3ra FASE : Redistribucion\n";
        do{
            cout << "\n==== REDISTRIBUCION ====\n";
            cout << "Desea redistribuir sus tropas? (1:SI, 0:NO)\n";
            cout << "$ ";
            cin >> respuesta;
            if(respuesta == 1){
                redistribuirTropas(juego, jugador);
            }
        }while(respuesta != 0);
    }
    else{
        cout << "---- Jugador no existe ----\n";
    }
    return false;
}

void Risk::redistribuirTropas(Risk& juego, Jugador& jugador){
    int codigoPrimerTerritorio, codigoSegundoTerritorio, cantTropas;
    bool redistribucionExitosa = false;
    do{
        cout << "====== REDISTRIBUCION DE TROPAS ======\n\n";
        cout << "Asi se encuentran ubicadas tus tropas en el mapa:\n";
        jugador.imprimirTerritorios(jugador);
        cout << "Ingrese codigo del territorio al que va a moverle tropas: \n";
        cout << "$ ";
        cin>> codigoPrimerTerritorio;
        if(jugador.codigoExiste(jugador, codigoPrimerTerritorio)){
            cout << "Cuantas tropas deseas mover?\n";
            cout << "$ ";
            cin>> cantTropas;
            if(jugador.validarTropasPais(jugador, codigoPrimerTerritorio, cantTropas)){
                cout << "Ingrese codigo del territorio a donde va a mover las tropas: \n";
                cout << "$ ";
                cin >> codigoSegundoTerritorio;
                if(jugador.codigoExiste(jugador, codigoSegundoTerritorio)){
                    if(jugador.relacionConPais(jugador, codigoPrimerTerritorio, codigoSegundoTerritorio)){
                        if(jugador.restarInfanteria(jugador, codigoPrimerTerritorio, cantTropas)){
                            jugador.aumentarInfanteria(jugador,codigoSegundoTerritorio,cantTropas);
                            jugador.imprimirTerritorios(jugador);
                            redistribucionExitosa = true;
                        }
                    }else{
                        cout << "---- Los territorios no se relacionan ----\n";
                        cout << "Desea terminar REDISTRIBUCION? (1:SI, 0:NO)\n";
                        cout << "$ ";
                        cin >> redistribucionExitosa;
                    }
                }else{
                    cout << "---- Territorio destino no es de su propiedad ----\n";
                }
            }else{
                cout << "---- No posee la cantidad de tropas que quiere mover ----\n";
            }
        }else{
            cout << "---- Territorio no en su propiedad ----\n";
        }    
    }while(!redistribucionExitosa);
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
    cout<<"---- El jugador no existe ----\n";
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
    cout << "\n==== El pais desde donde vas a ATACAR es " << pais.nombre <<" ====\n";
    cout << "Tropas en el pais:" << pais.infanteria << endl;
    cout << "Paises que te pertenecen relacionados:\n";
    cout <<"- ";
    for (int codigo : enAmbos) {
        cout << codigo << ", ";
    }
    cout << endl;
                
    cout << "Paises que se pueden atacar:\n";
    cout <<"- ";
    for (int codigo : posiblesAtaques) {
        cout << codigo << ", ";
    }
    cout << endl;
    do{
        cout<<"\nIngrese el pais a atacar: \n";
        cout<<"$ ";
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
    cout << "Con cuantas tropas deseas ATACAR "<< atacante.nombre<<" ?\n";
    int tropasAtacantes = cantidadTropasAtacantes(ataca);
    cout << "Con cuantas tropas deseas DEFENDER "<< defensor.nombre<<" ?\n";
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

    cout << "\n==== RESULTADO DE LA BATALLA ====\n";
    cout << "Victorias del ATACANTE: " << victoriasAtacante << "\n";
    cout << "Victorias del DEFENSOR: " << victoriasDefensor << "\n";

    defiende.infanteria += tropasDefensa - victoriasAtacante;

    if(defiende.infanteria > 0){
        ataca.infanteria += tropasAtacantes - victoriasDefensor;
    }
    else{
        conquisto = true;
        int tropasSobrevivientes = tropasAtacantes - victoriasDefensor;
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
        cout << "$ ";
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
        cout << "$ "; 
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
    cout<< "Seleccione uno por uno el codigo de las tres cartas que desea intercambiar\n";
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
        cout<<"Se anadieron " << juego.caballoDorado << " tropas a su infanteria\n";
        actualizarCaballoDorado(juego);
        jugador.eliminarCartaPorCodigo(carta1.codigoPais);
        jugador.eliminarCartaPorCodigo(carta2.codigoPais);
        jugador.eliminarCartaPorCodigo(carta3.codigoPais);
    }
    else{
        cout << "---- Cartas no cumplen ningun requisito para ser intercambiadas ----\n";
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
                cout << "Se insertaron 2 tropas al territorio: " << jugador.territorios[j].nombre << endl;
            }
        }
}

void Risk::guardarPartida(Risk& juego, string nombreArchivo){

    nombreArchivo = "files/games/" + nombreArchivo + ".txt";
    ofstream archivo(nombreArchivo);

    // Verifica si el archivo se abrió correctamente
    if (archivo) {
        archivo << juego.cantidadJugadores << endl; 
        for(Jugador jugador : juego.jugadores){
            archivo << "*" << endl;
            archivo << jugador.nombre << "," << jugador.color << endl; 
            archivo  << jugador.territorios.size() << endl;
            for(Pais pais : jugador.territorios){
                archivo << pais.codigoContinente << "," << pais.codigo << "," << pais.nombre << "," << pais.infanteria << "," << "[";
                for(int i =0; i< pais.relaciones.size(); i++){
                    if(i == 0){
                        archivo << pais.relaciones[i];
                    }
                    else{
                        archivo << "," << pais.relaciones[i];
                    }
                }
                archivo << "]" << endl;
            }
            archivo<< jugador.cartas.size() <<endl;
            for(Carta carta : jugador.cartas){
                archivo << carta.codigoPais << "," << carta.figura << endl;
            }
        }
        // Cierra el archivo
        archivo.close();

        cout << "Se ha escrito en el archivo exitosamente." << endl;
    } else {
        cout << "No se pudo guardar." << endl;
    }
}