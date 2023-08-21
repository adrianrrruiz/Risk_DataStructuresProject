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
bool Jugador::codigoExiste(Jugador& jugador,int codigo){
  for(int i=0;i< jugador.territorios.size();i++){
    if(jugador.territorios[i].codigo == codigo){
        return true;
    }
  }
  return false;
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
