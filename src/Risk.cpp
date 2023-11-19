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
            getline(iss, carta.figura);
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
    crearGrafo(juego);
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
            system("cls");
            cout<<"Ingrese el nombre del participante No. " << i+1 << ":\n";
            cout << "$ ";
            cin>>nombre;
            color=imprimirColores(juego);
            eliminarColor(juego,color);
            cout<<"==== Se lanzara el DADO para ver el ORDEN a la hora de escoger territorio ====\n";
            system("pause");
            numeroDado= lanzamientoDado();
            cout << "- Saco un: " << numeroDado << endl;
            system("pause");
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
        system("cls");
        Jugador& jugadorActual = juego.jugadores[contador];
        cout << "==== TURNO DE " << jugadorActual.nombre << " ====\n";
        
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
            system("cls");
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
    mostrarGrafo(juego);
    actualizarGrafo(juego);
    return true;
}

void Risk::imprimirJugadores(Risk &juego){
    system("cls");
    cout << "\n==== JUGADORES CREADOS ====\n";
    for(const Jugador &jugador : juego.jugadores){
            cout <<"Jugador: " << jugador.nombre <<"   -   Color: "<<jugador.color << "\n";
    }
    system("pause");
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
    actualizarGrafo(juego);
    int respuesta;
    int codigoAux;
    int codigoPaisAtacar;
    int aux, cantidadTropas;
    bool menuAtaque=true;

    if(jugadorExiste(juego,id)){

        Jugador& jugador = jugadorEnTurno(juego,id);
        system("cls");
        cout << "==== TURNO DE " << jugador.nombre << " ====\n";
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
        system("cls");
        cout << "\n\n2da FASE: Ataque\n";
        system("pause");
        do {
            system("cls");
            cout << "\n==== MENU DE ATAQUE ====\n";
            cout << "Que desea hacer?\n";
            cout << "1: Atacar un territorio\n";
            cout << "2: Ver lo que me cuesta conquistar un territorio\n";
            cout << "3: Ver la conquista mas barata\n";
            cout << "0: Dejar de atacar\n";
            cout << "$ ";
            
            cin >> respuesta;
        
            if (respuesta == 1) {
                system("cls");
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
            else if (respuesta == 2){
            int territorioDado;
            do{
                system("cls");
                imprimirTerritoriosDeOtrosJugadores(juego, jugador);
                cout << "Ingrese el codigo del pais el cual desea conquistar: " << endl;
                cout <<"$ ";
                cin >> territorioDado;
            }while(!codigoSolicitadoAdecuado(juego,jugador,territorioDado));
                int territorioMasCercano;
                double distanciaMasCorta;
                costo_Conquista(juego, jugador, territorioDado, territorioMasCercano, distanciaMasCorta);
                cout << "Para conquistar el territorio " << territorioDado << ", debe atacar desde " << territorioMasCercano << " . Debe conquistar " << distanciaMasCorta << " unidades de ejercito.\n";
                system("pause");
            }
            else if (respuesta == 3){
                int territorioMasCercano, territorioDado;
                double distanciaMasCorta = 1000;
                conquistaMasBarata(juego, jugador, territorioDado, territorioMasCercano, distanciaMasCorta);
                cout << "La conquista mas barata es avanzar sobre el territorio " << territorioDado << " desde el territorio " << territorioMasCercano << " . Debe conquistar " << distanciaMasCorta << " unidades de ejercito.\n";
                system("pause");
            }
            else if (respuesta == 0) {
                menuAtaque = false;
            }
            else {
                cout << "Respuesta no válida.\n";
            }
        } while (menuAtaque);
        system("cls");
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
        system("cls");
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
        juego.jugadores.erase(remove_if(juego.jugadores.begin(), juego.jugadores.end(),
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
    int numeroAleatorio = rand() % 42 + 1;
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

bool Risk::cargarPartida(Risk& juego, string nombreArchivo){
    leerContinentes(juego);
    leerPaises(juego);
    leerRelaciones(juego);
    leerDistribucionCartas(juego);
    juego.caballoDorado = 4;
    nombreArchivo = "files/games/" + nombreArchivo + ".txt";
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        int aux;
        archivo >> juego.cantidadJugadores;
        archivo.ignore();
        cout << "cantidad de jugadores:"<< juego.cantidadJugadores << endl;
        for(int i =0; i < juego.cantidadJugadores; i++){
            Jugador jugador;
            string line;
            getline(archivo, line);
            cout<<"asterisco:" << line << endl;
            getline(archivo,line);
            istringstream jugadorInfo(line);
            getline(jugadorInfo, jugador.nombre, ',');
            cout<< "nombre:"<< jugador.nombre << endl;
            getline(jugadorInfo, jugador.color, ',');
            cout<< "color:"<< jugador.color << endl;
            getline(archivo,line);
            int cantidadPaises;
            cantidadPaises = stoi(line);
            cout<< "Cantidad Paises: "<< cantidadPaises << endl;
            for(int i =0; i < cantidadPaises; i++){
                Pais paisAux;
                string contCode, otherCode, troops, relations,aux;
                getline(archivo,line);
                cout << "info Pais: " << line << endl;
                istringstream infoPais(line);
                getline(infoPais,contCode, ',');
                paisAux.codigoContinente = stoi(contCode);
                cout << "codigo Continente: " << paisAux.codigoContinente << endl;
                getline(infoPais,otherCode,',');
                paisAux.codigo = stoi(otherCode);
                cout << "codigo: " << paisAux.codigo << endl;
                getline(infoPais,paisAux.nombre,',');
                cout << "nombre: " << paisAux.nombre << endl;
                getline(infoPais,troops,',');
                paisAux.infanteria = stoi(troops);
                cout <<"infanteria: " << paisAux.infanteria << endl;
                getline(infoPais, relations, '[');
                getline(infoPais, relations, ']');
                cout << "relaciones: " << relations << endl;
                istringstream relacionesStream(relations);
                string relacion;
                while (getline(relacionesStream, relacion, ',')) {
                    cout << relacion << ",";
                    paisAux.relaciones.push_back(stoi(relacion));
                }
                jugador.territorios.push_back(paisAux);
            }
            getline(archivo,line);
            aux = stoi(line);
            cout << "cantidad Cartas: " << aux << endl;
            for(int i= 0; i < aux; i++){
                string auxInt;
                Carta aux;
                getline(archivo,line);
                istringstream carta(line);
                getline(carta,auxInt,',');
                aux.codigoPais = stoi(auxInt);
                getline(carta,aux.figura,',');
                jugador.cartas.push_back(aux);
            }  
            juego.jugadores.push_back(jugador); 
        }
        archivo.close();
        corregirCartas(juego);
        crearGrafo(juego);
        actualizarGrafo(juego);
        cout << "Se ha leido el archivo exitosamente." << endl;
        return true;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
        return false;
    }
}

void Risk::corregirCartas(Risk& juego){
    for(int i = 0; i < juego.cantidadJugadores; i++){
        for(int j=0; j < juego.jugadores[i].cartas.size();j++){
            borrarCarta(juego,juego.jugadores[i].cartas[j]);
        }
    }
}

//Codificar caracteres
void Risk::codificar(Nodo *raiz, string str, unordered_map<char, string> &diccionarioHuffman){
    if(raiz == nullptr){
        return;
    }
    if(raiz->izq == nullptr && raiz->der == nullptr){
        diccionarioHuffman[raiz->simbolo] = str;
    }
    codificar(raiz->izq, str + "0", diccionarioHuffman);
    codificar(raiz->der, str + "1", diccionarioHuffman); 
}

//Pasar de codificación a caracteres
void Risk::decodificar(Nodo *raiz, int &indice, string str, string &textoNormal)
{
    if(raiz == nullptr){
        return;
    }
    if(raiz->izq == nullptr && raiz->der == nullptr){
        textoNormal += raiz->simbolo;
        return;
    }
    indice++;
    if(str[indice] == '0'){
        decodificar(raiz->izq, indice, str, textoNormal);
    }else{
        decodificar(raiz->der, indice, str, textoNormal);
    }
}

void Risk::crearArbol(map<char, long> &tablaFrecuencia, Nodo*&raiz)
{
    priority_queue<Nodo*, vector<Nodo*>, comp> colaPrioridad;
    //Llenar cola de prioridad
    for(auto pair: tablaFrecuencia){
        //Inserta los nodos a la cola de prioridad con sus hijos der e izq en nullptr
        //pair.first = simbolo
        //pair.second = frecuencia
        colaPrioridad.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    priority_queue<Nodo*, vector<Nodo*>, comp> copiaPrioridad = colaPrioridad;
    cout << "Recorriendo cola de prioridad \n";
    system("pause");
    while (!copiaPrioridad.empty()) {
        Nodo* elemento = copiaPrioridad.top();
        cout << "simbolo " << elemento->simbolo << "- frecuencia " << elemento->frecuencia<< endl;
        copiaPrioridad.pop();
    }
    system("pause");
    //Con los dos primeros elementos de la cola, crea un nuevo nodo y su raiz es la suma de sus frecuencias
    while(colaPrioridad.size() != 1){
        Nodo *izq = colaPrioridad.top();
        colaPrioridad.pop();
        Nodo *der = colaPrioridad.top();
        colaPrioridad.pop();
        
        int sum = izq->frecuencia + der->frecuencia;
        //El valor del simbolo es '\0' para todos los nodos intermedios o raiz
        colaPrioridad.push(getNode('\0', sum, izq, der));
    }
    
    raiz = colaPrioridad.top();
}

void Risk::crearTablaFrecuencia(map<char, long> &tablaFrecuencia, string texto){
    for(char simbolo: texto){
        tablaFrecuencia[simbolo]++;
    }
}

string Risk::generarCodigoCodificado(string texto, unordered_map<char, string> diccionarioHuffman){
    string str = "";
    for(char simbolo: texto){
        str += diccionarioHuffman[simbolo];
    }
    return str;
}

string Risk::crearCadenaDelArchivoTxt(string nombreArchivo){
    nombreArchivo = "files/games/" + nombreArchivo + ".txt";
    ifstream archivo(nombreArchivo);
    string cadenaCompleta = "";
    // Verifica si el archivo se abrió correctamente
    if (archivo) {
        string linea;
        while (getline(archivo, linea)) {
            cadenaCompleta += linea + "\n";
        }
        // Cierra el archivo
        archivo.close();
    } else {
        cout << "No se pudo leer el archivo" << endl;
    }
    return cadenaCompleta;
}

void Risk::guardarComprimido(string nombreArchivo){
    string todoElArchivoEnUnaCadena = crearCadenaDelArchivoTxt(nombreArchivo);
    // cout << "Creo cadena con archivo txt\n";
    // cout << todoElArchivoEnUnaCadena << endl;
    map<char, long> tablaFrecuencia;
    unordered_map<char, string> diccionarioHuffman;
    Nodo *raiz;
    crearTablaFrecuencia(tablaFrecuencia, todoElArchivoEnUnaCadena);
    // cout << "Creo tabla frecuencia\n";
    // for (auto pair : tablaFrecuencia){
    //     cout << pair.first << " - " << pair.second << endl;
    // }
    crearArbol(tablaFrecuencia, raiz);
    codificar(raiz, "", diccionarioHuffman);
    
    cout << "\nLos codigos de Huffman son:\n\n";
    for(auto pair : diccionarioHuffman){
        cout << " " << pair.first << " - " << pair.second <<endl;
    }
    system("pause");
    //Obtener codigo completo codificado
    string cadenaCodificada = generarCodigoCodificado(todoElArchivoEnUnaCadena,diccionarioHuffman);
    int cerosAdicionales = modificarCadena(cadenaCodificada);
    vector<bitset<8>> cadenaComprimida;
    //Se crean los bytes y se llena el vector "cadenaComprimida"
    pasarDeStringABytes(cadenaCodificada, cadenaComprimida);

    // for (int i = 0; i < cadenaComprimida.size(); i++) {
    //     cout << "Byte # " << i << ": "<< cadenaComprimida[i] << endl;
    // }
    nombreArchivo = "files/games/" + nombreArchivo + ".dat";
    ofstream archivoBin(nombreArchivo, ios::binary|ios::out);

    if(archivoBin.is_open()){
        //Obtener cantidad de caracteres diferentes (tamaño del mapa)
        short cantCaracteresDiferentes = tablaFrecuencia.size();
        cout << "Cantidad caracteres diferentes: " << cantCaracteresDiferentes << endl;
        archivoBin.write(reinterpret_cast<const char*>(&cantCaracteresDiferentes), sizeof(short));
         //Obtener cantidad de caracteres de todo el archivo original
        long cantCaracteres = todoElArchivoEnUnaCadena.size();
        cout << "Cantidad caracteres: " << cantCaracteres << endl;
        archivoBin.write(reinterpret_cast<const char*>(&cantCaracteres), sizeof(long));
        // Escribir los pares clave-valor de la tabla de frecuencia uno por uno
        cout << "---- TABLA DE FRECUENCIA ----\n";
        for (const auto& par : tablaFrecuencia) {
            cout << "Caracter: " << par.first << " - Frecuencia: " << par.second << endl;
            archivoBin.write(reinterpret_cast<const char*>(&par.first), sizeof(char));
            archivoBin.write(reinterpret_cast<const char*>(&par.second), sizeof(long));
        }
        //Escribir el tamaño del vector
        size_t tamanoVector = cadenaComprimida.size();
        cout << "Cantidad de bytes: " << tamanoVector << endl;
        archivoBin.write(reinterpret_cast<const char*>(&tamanoVector), sizeof(size_t));
        // Escribir los elementos del vector uno por uno
        for (const bitset<8>& byte : cadenaComprimida) {
            // cout << "Byte # " << ": "<< byte << endl;
            archivoBin.write(reinterpret_cast<const char*>(&byte), sizeof(bitset<8>));
        }
        //Escribir 0s adicionales en la cadena comprimida
        cout << "Ceros adicionales: " << cerosAdicionales << endl;
        archivoBin.write(reinterpret_cast<const char*>(&cerosAdicionales), sizeof(int));
        system("pause");
        archivoBin.close();
    }else{
        cout << "No se pudo abrir el archivo!" << endl;
    }
}

//Añadir 0s adicionales para que sea multiplo de 8
int Risk::modificarCadena(string &cadenaCodificada){
    if(cadenaCodificada.size() % 8 != 0){
        //Toca agregar 0s
        int faltantes =  8 - (cadenaCodificada.size()%8);
        for(short i=0 ;i <faltantes ;i++){
            cadenaCodificada+="0";
        }
        return faltantes;
    }
    return 0;
}

void Risk::pasarDeStringABytes(string cadenaCodificada, vector<bitset<8>> &cadenaComprimida){
    int cantBytes = cadenaCodificada.size() / 8;
    cout << "Cantidad de bytes: " << cantBytes << endl;
    for(int i = 0; i < cadenaCodificada.length(); i += 8){
        string byte = cadenaCodificada.substr(i,8);
        bitset<8> byteReal(byte);
        cadenaComprimida.push_back(byteReal);
    }
}

//Asignar los nuevos nodos en el árbol de Huffman
Nodo *Risk::getNode(char simbolo, int frecuencia, Nodo *izq, Nodo *der)
{
    Nodo* nodo = new Nodo();
    
    nodo->simbolo = simbolo;
    nodo->frecuencia = frecuencia;
    nodo->izq = izq;
    nodo->der = der;

    return nodo;
}

void Risk::cargarComprimido(string nombreArchivo){
    string nombreArchivoOriginal = nombreArchivo;
    nombreArchivo = "files/games/" + nombreArchivo + ".dat";
    string cadenaCodificada = "";
    map<char, long> tablaFrecuencia;
    Nodo *raiz;
    bool lecturaOK = true;
    short cantCaracteresDiferentes;
    long cantCaracteres;
    size_t tamanoVector; 
    int cerosAdicionales;
    vector<bitset<8>> cadenaComprimida;

    ifstream archivoBin(nombreArchivo, ios::binary);

    if(archivoBin.is_open()){
        if(archivoBin.read(reinterpret_cast<char*>(&cantCaracteresDiferentes), sizeof(short))){
            cout << "Cantidad caracteres diferentes: " << cantCaracteresDiferentes << endl;
        }else{
            lecturaOK = false;
        }
        if(archivoBin.read(reinterpret_cast<char*>(&cantCaracteres), sizeof(long)) && lecturaOK){
            cout << "Cantidad caracteres: " << cantCaracteres << endl;
        }else{
            lecturaOK = false;
        }
        cout << "---- TABLA DE FRECUENCIA ----\n";
        for (int i = 0; i < cantCaracteresDiferentes; i++) {
            char clave;
            long valor;
            if(archivoBin.read(reinterpret_cast<char*>(&clave), sizeof(char)) && archivoBin.read(reinterpret_cast<char*>(&valor), sizeof(long)) && lecturaOK){
                cout << "Caracter: " << clave << " - Frecuencia: " << valor << endl;
                tablaFrecuencia.insert(make_pair(clave, valor));
            }else{
                lecturaOK = false;
            }
        }
        if(archivoBin.read(reinterpret_cast<char*>(&tamanoVector), sizeof(size_t)) && lecturaOK){
            cout << "Cantidad de bytes: " << tamanoVector << endl;
        }else{
            lecturaOK = false;
        }
        
        cadenaComprimida.resize(tamanoVector);
        for (int i = 0; i < tamanoVector; i++) {
            if(archivoBin.read(reinterpret_cast<char*>(&cadenaComprimida[i]), sizeof(bitset<8>)) && lecturaOK){
                cout << "Byte # " << i << ": "<< cadenaComprimida[i] << endl;
            }else{
                lecturaOK = false;
            }
        }
        if(archivoBin.read(reinterpret_cast<char*>(&cerosAdicionales), sizeof(int)) && lecturaOK){
            cout << "Ceros adicionales: " << cerosAdicionales << endl;
        }else{
            lecturaOK = false;
        }
        system("pause");
        if(lecturaOK){
            crearArbol(tablaFrecuencia, raiz);
            for(bitset<8> byte : cadenaComprimida){
                cadenaCodificada += byte.to_string();
            }
            if(cerosAdicionales != 0){
                //Quitando ceros adicionales
                cadenaCodificada.erase(cadenaCodificada.length() - cerosAdicionales);
            }
            string textoNormal;
            textoNormal = pasarDeCodificadaANormal(cadenaCodificada, raiz);
            cout << "El texto decodificado es: " << endl;
            cout << textoNormal;
            nombreArchivoOriginal = "files/games/" + nombreArchivoOriginal + ".txt";
            escribirEnArchivoDescompresion(nombreArchivoOriginal, textoNormal);
        }
        archivoBin.close();
    }else{
        cout << "No se pudo abrir el archivo!" << endl;
    }
}

void Risk::escribirEnArchivoDescompresion(string nombreArchivo, string textoNormal){
    ofstream archivoDescomprimido(nombreArchivo); 

    if(archivoDescomprimido) { //Verificar que si abre
        archivoDescomprimido << textoNormal;
        archivoDescomprimido.close(); 
    }else {
        cout << "No se pudo abrir el archivo" << endl;
    }

    cout << "El archivo se creo correctamente!" << endl;
    system("pause");
}

string Risk::pasarDeCodificadaANormal(string cadenaCodificada, Nodo* raiz){
    int index = -1;
    string textoNormal = "";
    while(index < (int)cadenaCodificada.size() - 2){
        decodificar(raiz, index, cadenaCodificada, textoNormal);
    }
    
    return textoNormal;
}

void Risk::crearGrafo(Risk &juego){
    ifstream archivo("files\\Relaciones.txt");
    string linea;
    int codigo;
    Vertice vertice;
    Arista arista;
    int contador = 1;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            iss >> codigo;
            vertice.id = codigo;
            juego.grafo.vertices.insert(make_pair(codigo,vertice));
            char separador;
            iss >> separador;
            int relacionado;
            while (iss >> relacionado) {
                arista.idOrigen= codigo;
                arista.idDestino = relacionado;
                arista.peso = 0;
                juego.grafo.aristas.insert(make_pair(contador,arista));
                contador++;
                if (iss.peek() == ',') {
                    iss.ignore();
                }
            }
        }
    archivo.close();
    }
}
void Risk::mostrarGrafo(Risk &juego){
    cout << "Vertices:" << endl;
        for (const auto& par : juego.grafo.vertices) {
            cout << "ID del vertice: " << par.first << ", Valor: " << par.second.id << endl;
        }

        cout << "\nAristas:" << endl;
        for (const auto& par : juego.grafo.aristas) {
            cout << "ID de la arista: " << par.first << ", Origen: " << par.second.idOrigen
                      << ", Destino: " << par.second.idDestino << ", Peso: " << par.second.peso << endl;
        }
}

void Risk::actualizarGrafo(Risk &juego){
    for(const Jugador &jugador: juego.jugadores){
        for(const Pais &pais : jugador.territorios){
            for (auto& par : juego.grafo.aristas) {
                if(par.second.idDestino == pais.codigo){
                    par.second.setPeso(pais.infanteria);
                }
            }
        }
    }
}

void Risk::imprimirDistancias(vector<vector<double>> distancias){
        int n = distancias.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (distancias[i][j] == numeric_limits<double>::infinity()) {
                    cout << "Infinito ";
                } else {
                    cout << distancias[i][j] << " ";
                }
            }
            cout << endl;
        }
}

void Risk::costo_Conquista(Risk &juego, Jugador jugador, int &territorioDado, int &territorioMasCercano, double &distanciaMasCorta){
    actualizarGrafo(juego);
    auto distancias = juego.grafo.floydWarshall();
    //imprimirDistancias(distancias);
    territorioMasCercano = -1; 
    distanciaMasCorta = numeric_limits<double>::infinity();
    for (int i = 0; i < jugador.territorios.size();i++) {
        int territorioControlado = jugador.territorios[i].codigo;
        if (distancias[territorioControlado][territorioDado] < distanciaMasCorta) {
            distanciaMasCorta = distancias[territorioControlado][territorioDado];
            territorioMasCercano = territorioControlado;
        }
    }
}

void Risk::imprimirTerritoriosDeOtrosJugadores(Risk &juego, Jugador jugador1){
    for(const Jugador &jugador: juego.jugadores){
        if(jugador1.nombre != jugador.nombre){
            cout << "Territorios de " << jugador.nombre << endl;
            for(const Pais &pais : jugador.territorios){
                cout << pais.codigo <<": " <<pais.nombre << endl;
            }
        }   
    }
}

bool Risk::codigoSolicitadoAdecuado(Risk &juego,Jugador jugador1, int codigo){
    for(const Jugador &jugador: juego.jugadores){
        if(jugador1.nombre != jugador.nombre){
            for(const Pais &pais : jugador.territorios){
                if(codigo = pais.codigo){
                    return true;
                }
            }
        }   
    }
    return false;
}

void Risk::conquistaMasBarata(Risk &juego, Jugador jugador1, int &territorioDado, int &territorioMasCercano, double &distanciaMasCorta){
    int territorioOrigen, territorioDestino;
    double costoUnidades;
    for(const Jugador &jugador: juego.jugadores){
        if(jugador1.nombre != jugador.nombre){
            for(const Pais &pais : jugador.territorios){
                territorioDestino = pais.codigo;
                costo_Conquista(juego, jugador1, territorioDestino, territorioOrigen, costoUnidades);
                if(costoUnidades < distanciaMasCorta){
                    distanciaMasCorta = costoUnidades;
                    territorioMasCercano = territorioOrigen;
                    territorioDado = territorioDestino;
                }
            }
        }   
    }
}