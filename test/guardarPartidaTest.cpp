#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"
#include "../include/Risk.h" 
#include <fstream> 

TEST_CASE("Guardar partida") {
    Risk juego;
    juego.cantidadJugadores = 2;

    Jugador jugador1;
    jugador1.nombre = "daniel";
    jugador1.color = "Rojo";
    
    Pais pais1, pais2, pais3;
    pais1.codigoContinente = 1;
    pais1.codigo = 1;
    pais1.nombre = "Alaska";
    pais1.infanteria = 13;
    pais1.relaciones = {2, 6, 32};
    
    jugador1.territorios = {pais1};

    Jugador jugador2;
    jugador2.nombre = "adrian";
    jugador2.color = "Verde";
    
    Pais pais4, pais5, pais6;
    pais4.codigoContinente = 1;
    pais4.codigo = 2;
    pais4.nombre = "Alberta";
    pais4.infanteria = 1;
    pais4.relaciones = {1, 6, 7, 9};
    
    pais5.codigoContinente = 1;
    pais5.codigo = 5;
    pais5.nombre = "Groenlandia";
    pais5.infanteria = 1;
    pais5.relaciones = {6, 7, 8, 15};

    jugador2.territorios = {pais4, pais5};

    juego.jugadores = {jugador1, jugador2};

    juego.guardarPartida(juego, "prueba");

    ifstream archivo("files/games/prueba.txt");
    REQUIRE(archivo.is_open());

    string linea;
    vector<string> contenidoArchivo;

    while (getline(archivo, linea)) {
        contenidoArchivo.push_back(linea);
    }

    // Verifica el contenido del archivo según los datos proporcionados
    REQUIRE(contenidoArchivo[0] == "2"); // Cantidad de jugadores
    REQUIRE(contenidoArchivo[1] == "*"); // Separador de jugador 1
    REQUIRE(contenidoArchivo[2] == "daniel,Rojo"); // Datos de jugador 1
    REQUIRE(contenidoArchivo[3] == "1"); // Cantidad de territorios de jugador 1
    REQUIRE(contenidoArchivo[4] == "1,1,Alaska,13,[2,6,32]"); // Datos del territorio de jugador 1
    REQUIRE(contenidoArchivo[5] == "0"); // Numero de cartas de jugador 1
    REQUIRE(contenidoArchivo[6] == "*"); // Separador de jugador 2
    REQUIRE(contenidoArchivo[7] == "adrian,Verde"); // Datos de jugador 2
    REQUIRE(contenidoArchivo[8] == "2"); // Cantidad de territorios de jugador 2
    REQUIRE(contenidoArchivo[9] == "1,2,Alberta,1,[1,6,7,9]"); // Datos del territorio de jugador 2
    REQUIRE(contenidoArchivo[10] == "1,5,Groenlandia,1,[6,7,8,15]"); // Datos del territorio de jugador 2
    REQUIRE(contenidoArchivo[11] == "0"); // Numero de cartas de jugador 1

    archivo.close();
}
