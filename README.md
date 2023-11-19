# Compilación y ejecución
Para compilarlo
```
g++ -std=c++11 -o proyecto .\main.cpp .\src\*.cpp .\src\Grafo\*.cpp
```
Para compilar prueba unitaria guardarPartida
```
g++ -std=c++11 -o proyecto .\src\*.cpp .\test\guardarPartidaTest.cpp
```
Para ejecutarlo
```
.\proyecto.exe 
```

# Juego Risk

Este proyecto implementa una versión del juego de mesa Risk en C++. El juego incluye la lectura de archivos de configuración para cargar continentes, países y relaciones, además de una funcionalidad básica para el desarrollo del juego.

## Contenido

- [Archivos de Configuración](#archivos-de-configuración)
- [Estructura de Clases](#estructura-de-clases)
- [Funcionalidades](#funcionalidades)
- - [Instrucciones de Uso](#instrucciones-de-uso)
- [Contribución](#contribución)
- [Licencia](#licencia)
- [Autores](#autores)

## Archivos de Configuración

- `continentes.txt`: Contiene los 6 continentes, cada uno identificado por un código y con la cantidad de países correspondientes.
- `paises.txt`: Contiene el código del continente al que pertenece, un código de país y el nombre del país.
- `relaciones.txt`: Contiene las relaciones entre países.

## Estructura de Clases

- `Carta.h`, `Continente.h`, `Jugador.h`, `Pais.h` y `Risk.h`: Archivos de cabecera donde se crean las clases correspondientes y se declaran las variables, vectores y funciones necesarias para el funcionamiento del juego.
- `carta.cpp`, `continente.cpp` y `pais.cpp`: Aunque aún no cuentan con código, estos archivos están destinados a contener la implementación de las clases `Carta`, `Continente` y `Pais`.
- `jugador.cpp`: Contiene varias funciones relacionadas con el jugador, como comparar resultados de dados, imprimir territorios, aumentar la infantería en un territorio específico y verificar la posesión de territorios y continentes completos.
- `risk.cpp`: Aquí se realiza el funcionamiento principal del juego, incluyendo la inicialización, distribución de territorios, asignación de tropas iniciales, turnos de juego y ataques.

## Funcionalidades

El proyecto incluye las siguientes funcionalidades en la clase Risk:

- Lectura y carga de información desde archivos.
- Selección de colores de ejército para los jugadores.
- Validación de la cantidad de jugadores.
- Distribución de territorios iniciales.
- Asignación de tropas iniciales.
- Simulación del juego por turnos.
- Ataques entre territorios.
- Gestión de continentes y cartas.


## Instrucciones de Uso

1. Compila los archivos utilizando "g++ -std=c++11 -o proyecto .\main.cpp .\src\*.cpp"
2. Ejecuta el programa resultanten utilizando ".\proyecto.exe"
3. Inseerta "help" para conocer la lista de comandos.
4. Sigue las instrucciones en pantalla para interactuar con el juego.


## Contribución

Si deseas contribuir a este proyecto, sigue estos pasos:

1. Clona el repositorio (https://github.com/aruiz08/Risk_DataStructuresProject.git).
2. Crea una rama para tu función o corrección: `git checkout -b nombre-de-la-rama`
3. Realiza tus cambios y realiza commits: `git commit -m "Descripción de los cambios"`
4. Sube tu rama al repositorio: `git push origin nombre-de-la-rama`
5. Crea un Pull Request en este repositorio.

## Licencia
Este proyecto está bajo la Licencia [MIT](LICENSE).

## Autores

- [Daniel Carvajal](https://github.com/DaniCarvajalG) 
- [Adrain Ruiz](https://github.com/aruiz08)
- [Juliana Bejarano](https://github.com/Julibejarano)

