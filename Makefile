# Makefile para compilar el proyecto Risk en Linux/Unix/Mac
# Uso: make

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = proyecto
SRCDIR = src
SOURCES = main.cpp \
          $(SRCDIR)/Carta.cpp \
          $(SRCDIR)/Continente.cpp \
          $(SRCDIR)/Jugador.cpp \
          $(SRCDIR)/Nodo.cpp \
          $(SRCDIR)/Pais.cpp \
          $(SRCDIR)/Risk.cpp \
          $(SRCDIR)/Grafo/Arista.cpp \
          $(SRCDIR)/Grafo/Grafo.cpp \
          $(SRCDIR)/Grafo/Vertice.cpp

OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Compilar prueba unitaria
test: $(SRCDIR)/*.cpp test/guardarPartidaTest.cpp
	$(CXX) $(CXXFLAGS) -o test_proyecto $(SRCDIR)/*.cpp test/guardarPartidaTest.cpp
	./test_proyecto

