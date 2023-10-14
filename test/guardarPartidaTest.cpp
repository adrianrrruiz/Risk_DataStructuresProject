#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"
#include "../include/Risk.h" // Incluye los encabezados necesarios para Risk
#include <fstream> // Incluye la biblioteca para trabajar con archivos

TEST_CASE("guardar Partida") {
// Crea una instancia de Risk para probar
Risk juego;

// Configura los datos de prueba en la instancia de Risk
juego.cantidadJugadores = 3;

// Jugador 1
Jugador jugador1;
jugador1.nombre = "daniel";
jugador1.color = "Rojo";

Pais pais1;
pais1.codigoContinente = 1;
pais1.codigo = 1;
pais1.nombre = "Alaska";
pais1.infanteria = 13;
pais1.relaciones = {2, 6, 32};

Pais pais2;
pais2.codigoContinente = 1;
pais2.codigo = 4;
pais2.nombre = "Estados Unidos Orientales";
pais2.infanteria = 6;
pais2.relaciones = {3, 7, 8, 9};

juego.jugadores.push_back(jugador1);
jugador1.territorios.push_back(pais1);
jugador1.territorios.push_back(pais2);

// Jugador 2
Jugador jugador2;
jugador2.nombre = "adrian";
jugador2.color = "Verde";

Pais pais3;
pais3.codigoContinente = 1;
pais3.codigo = 2;
pais3.nombre = "Alberta";
pais3.infanteria = 1;
pais3.relaciones = {1, 6, 7, 9};

Pais pais4;
pais4.codigoContinente = 1;
pais4.codigo = 5;
pais4.nombre = "Groenlandia";
pais4.infanteria = 1;
pais4.relaciones = {6, 7, 8, 15};

juego.jugadores.push_back(jugador2);
jugador2.territorios.push_back(pais3);
jugador2.territorios.push_back(pais4);

// Jugador 3
Jugador jugador3;
jugador3.nombre = "juliana";
jugador3.color = "Azul";

Pais pais5;
pais5.codigoContinente = 1;
pais5.codigo = 3;
pais5.nombre = "America Central";
pais5.infanteria = 1;
pais5.relaciones = {4, 9, 13};

Pais pais6;
pais6.codigoContinente = 1;
pais6.codigo = 6;
pais6.nombre = "Teorritorio Noroccidental";
pais6.infanteria = 1;
pais6.relaciones = {1, 2, 5, 7};

juego.jugadores.push_back(jugador3);
jugador3.territorios.push_back(pais5);
jugador3.territorios.push_back(pais6);

// Llama a la función guardarPartida con un nombre de archivo de prueba
std::string nombreArchivo = "prueba";
juego.guardarPartida(juego, nombreArchivo);

// Abre el archivo guardado y verifica si se puede abrir
std::string nombreArchivoCompleto = "files/games/" + nombreArchivo + ".txt";
std::ifstream archivoGuardado(nombreArchivoCompleto);

REQUIRE(archivoGuardado.is_open());

// Lee el contenido del archivo
std::string contenidoArchivo((std::istreambuf_iterator<char>(archivoGuardado)), std::istreambuf_iterator<char>());

// Define el contenido esperado
std::string contenidoEsperado =
    "3\n"  // Número de jugadores
    "*\n"  // Indica el inicio del primer jugador
    "daniel,Rojo\n"  // Datos del primer jugador
    "2\n"  // Cantidad de países del primer jugador
    "1,1,Alaska,13,[2,6,32]\n"  // Datos del primer país
    "1,4,Estados Unidos Orientales,6,[3,7,8,9]\n"  // Datos del segundo país
    "0\n"  // Cantidad de cartas del primer jugador
    "*\n"  // Indica el inicio del segundo jugador
    "adrian,Verde\n"  // Datos del segundo jugador
    "2\n"  // Cantidad de países del segundo jugador
    "1,2,Alberta,1,[1,6,7,9]\n"  // Datos del primer país del segundo jugador
    "1,5,Groenlandia,1,[6,7,8,15]\n"  // Datos del segundo país del segundo jugador
    "0\n"  // Cantidad de cartas del segundo jugador
    "*\n"  // Indica el inicio del tercer jugador
    "juliana,Azul\n"  // Datos del tercer jugador
    "2\n"  // Cantidad de países del tercer jugador
    "1,3,America Central,1,[4,9,13]\n"  // Datos del primer país del tercer jugador
    "1,6,Teorritorio Noroccidental,1,[1,2,5,7]\n";  // Datos del segundo país del tercer jugador

// Verifica si el contenido del archivo coincide con lo esperado
REQUIRE(contenidoArchivo == contenidoEsperado);

// Cierra el archivo
archivoGuardado.close();


}
