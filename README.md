# 🔨 Compilación y ejecución

Este proyecto es multiplataforma y funciona tanto en **Windows** como en **Linux/Unix/Mac**.

## 🪟 Windows

### Opción 1: Usando el script de compilación (Recomendado)
```batch
compile.bat
```

### Opción 2: Compilación manual
```batch
g++ -std=c++11 -o proyecto.exe main.cpp src\*.cpp src\Grafo\*.cpp
```

### Ejecución
```batch
proyecto.exe
```

## 🐧 Linux/Unix/Mac

### Opción 1: Usando Make (Recomendado)
```bash
make
make run
```

Para limpiar archivos compilados:
```bash
make clean
```

### Opción 2: Usando el script de compilación
```bash
./compile.sh
```

### Opción 3: Compilación manual
```bash
g++ -std=c++11 -o proyecto main.cpp src/*.cpp src/Grafo/*.cpp
./proyecto
```

## 🧪 Pruebas unitarias

### Windows
```batch
g++ -std=c++11 -o test_proyecto src\*.cpp test\guardarPartidaTest.cpp
test_proyecto.exe
```

### Linux/Unix/Mac
```bash
make test
```

# 🕹️ Juego Risk

![Risk Photo](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fplay-risk-online.net%2Fwp-content%2Fuploads%2F2016%2F04%2Frisk1.jpg&f=1&nofb=1&ipt=f4f548b9df93e631ec998609f2640f3bfa4ab1bcc79e3e5fb6e0c027c3b62406)

Este proyecto implementa una versión del juego de mesa Risk en C++. El juego incluye la lectura de archivos de configuración para cargar continentes, países y relaciones, además de una funcionalidad básica para el desarrollo del juego.

## Contenido

- [Archivos de Configuración](#archivos-de-configuración)
- [Estructura de Clases](#estructura-de-clases)
- [Funcionalidades](#funcionalidades)
- [Instrucciones de Uso](#instrucciones-de-uso)
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

1. **Compila el proyecto** usando uno de los métodos descritos en la sección [Compilación y ejecución](#compilación-y-ejecución)
2. **Ejecuta el programa** resultante:
   - Windows: `proyecto.exe`
   - Linux/Unix/Mac: `./proyecto`
3. **Inserta "help"** para conocer la lista de comandos disponibles
4. **Sigue las instrucciones** en pantalla para interactuar con el juego

### Características multiplataforma

El proyecto detecta automáticamente el sistema operativo y ajusta:
- Comandos de limpieza de pantalla (`cls` en Windows, `clear` en Linux)
- Comandos de pausa (compatible con ambas plataformas)
- Rutas de archivos (funcionan en ambos sistemas)


## Contribución

Si deseas contribuir a este proyecto, sigue estos pasos:

1. Clona el repositorio (https://github.com/adrianrrruiz/Risk_DataStructuresProject.git).
2. Crea una rama para tu función o corrección: `git checkout -b nombre-de-la-rama`
3. Realiza tus cambios y realiza commits: `git commit -m "Descripción de los cambios"`
4. Sube tu rama al repositorio: `git push origin nombre-de-la-rama`
5. Crea un Pull Request en este repositorio.

## Licencia
Este proyecto está bajo la Licencia [MIT](LICENSE).

## Autores

- [Daniel Carvajal](https://github.com/DaniCarvajalG) 
- [Adrian Ruiz](https://github.com/adrianrrruiz)
- [Juliana Bejarano](https://github.com/Julibejarano)

