#include "../include/Jugador.h"

bool Jugador::operator<(const Jugador& otroJugador) const{
  return resultadoDado < otroJugador.resultadoDado;
}