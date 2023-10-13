#include "..\\include\\Jugador.h"

bool Jugador::operator<(const Jugador& otroJugador) const{
  return resultadoDado < otroJugador.resultadoDado;
}

void Jugador::imprimirTerritorios(Jugador& jugador){
    cout << setw(7) << left << "Codigo "
         << setw(30) << left << "Nombre del territorio"
         << setw(12) << right << "Infanteria" << endl;
    
    for(int i = 0; i < jugador.territorios.size(); i++){
        cout << setw(7) << left << jugador.territorios[i].codigo
             << setw(30) << left << jugador.territorios[i].nombre
             << setw(12) << right << jugador.territorios[i].infanteria << endl;
    }
}

void Jugador::aumentarInfanteria(Jugador& jugador,int codigo,int cantidad){
  for(int i=0;i< jugador.territorios.size();i++){
    if(jugador.territorios[i].codigo == codigo){
      jugador.territorios[i].infanteria+=cantidad;
      jugador.infanteria-=cantidad;
      return;
    }
  }
}

bool Jugador::restarInfanteria(Jugador& jugador,int codigo,int cantidad){
  for(int i=0;i< jugador.territorios.size();i++){
    if(jugador.territorios[i].codigo == codigo){
        if(jugador.territorios[i].infanteria > 1 && jugador.territorios[i].infanteria - cantidad != 0){
            jugador.territorios[i].infanteria-=cantidad;
            jugador.infanteria+=cantidad;
            return true;
        }else{
            cout << "---- Para mover un jugador a otro territorio debe tener minimo 2 tropas ----\n";
            return false;
        }
    }
  }
}

bool Jugador::codigoExiste(Jugador& jugador,int codigo){
  for(int i=0;i< jugador.territorios.size();i++){
    if(jugador.territorios[i].codigo == codigo){
        return true;
    }
  }
  return false;
}

bool Jugador::validarTropasPais(Jugador& jugador, int codigoTerritorio, int cantTropas){
    for(int i = 0; i < jugador.territorios.size(); i++){
        if(codigoTerritorio == jugador.territorios[i].codigo){
            if(cantTropas <= jugador.territorios[i].infanteria){
                return true;
            }else{
                return false;
            }
        }
    }
}

bool Jugador::relacionConPais(Jugador& jugador, int codigoPrimerTerritorio, int codigoSegundoTerritorio){
    for(int i = 0; i < jugador.territorios.size(); i++){
        if(codigoPrimerTerritorio == jugador.territorios[i].codigo){
            for(int j = 0; j < jugador.territorios[i].relaciones.size(); j++){
                if(jugador.territorios[i].relaciones[j] == codigoSegundoTerritorio){
                    return true;
                }
            }
            return false;
        }
    }
}

Pais& Jugador::paisSeleccionado(Jugador& jugador,int codigo){
  for(int i=0;i< jugador.territorios.size();i++){
    if(jugador.territorios[i].codigo == codigo){
        return jugador.territorios[i];
    }
  }
}

bool Jugador::cantidadSolicitadaValida(Jugador& jugador,int cantidadTropas){
  if(cantidadTropas<=jugador.infanteria && cantidadTropas > 0){
    return true;
  }
  else{
    return false;
  }
}

bool Jugador::poseeContinenteAmericaNorte(Jugador& jugador) const {
        for (int codigo = 1; codigo <= 9; ++codigo) {
            bool encontrado = false;
            for (const Pais& t : jugador.territorios) {
                if (t.codigo == codigo) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                return false;
            }
        }
        return true;
}

bool Jugador::poseeContinenteAmericaSur(Jugador& jugador) const {
        for (int codigo = 10; codigo <= 13; ++codigo) {
            bool encontrado = false;
            for (const Pais& t : jugador.territorios) {
                if (t.codigo == codigo) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                return false;
            }
        }
        return true;
}
bool Jugador::poseeContinenteEuropa(Jugador& jugador) const {
        for (int codigo = 14; codigo <= 20; ++codigo) {
            bool encontrado = false;
            for (const Pais& t : jugador.territorios) {
                if (t.codigo == codigo) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                return false;
            }
        }
        return true;
}
bool Jugador::poseeContinenteAfrica(Jugador& jugador) const {
        for (int codigo = 21; codigo <= 26; ++codigo) {
            bool encontrado = false;
            for (const Pais& t : jugador.territorios) {
                if (t.codigo == codigo) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                return false;
            }
        }
        return true;
}
bool Jugador::poseeContinenteAsia(Jugador& jugador) const {
        for (int codigo = 27; codigo <= 38; ++codigo) {
            bool encontrado = false;
            for (const Pais& t : jugador.territorios) {
                if (t.codigo == codigo) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                return false;
            }
        }
        return true;
}
bool Jugador::poseeContinenteOceania(Jugador& jugador) const {
        for (int codigo = 39; codigo <= 42; ++codigo) {
            bool encontrado = false;
            for (const Pais& t : jugador.territorios) {
                if (t.codigo == codigo) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                return false;
            }
        }
        return true;
}

void Jugador::eliminarTerritorio(int codigo) {
    territorios.erase(remove_if(territorios.begin(), territorios.end(),
        [codigo](const Pais& pais) {
            return pais.codigo == codigo;
        }), territorios.end());
    cout << "El territorio " << codigo << " se ELIMINO del jugador " << nombre << endl;
}

void Jugador::eliminarCartaPorCodigo(int codigo) {
        cartas.erase(remove_if(cartas.begin(), cartas.end(),
            [codigo](const Carta& carta) {
                return carta.codigoPais == codigo;
            }), cartas.end());
    }

void Jugador::imprimirCartas(Jugador& jugador){
    cout << "\n=== CARTAS DE " <<jugador.nombre <<" ====\n";
    
    for(int i = 0; i < jugador.cartas.size(); i++){
        cout << "- Pais: "<<jugador.cartas[i].codigoPais << ", Figura: " <<jugador.cartas[i].figura<<endl;
    }
}

Carta Jugador::retornarCarta(Jugador& jugador, int codigo){
    for(int i = 0; i < jugador.cartas.size(); i++){
        if(jugador.cartas[i].codigoPais == codigo){
            return jugador.cartas[i];
        }
    }
}
