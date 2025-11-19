@echo off
REM Script de compilación para Windows
REM Uso: compile.bat

echo Compilando proyecto Risk...
g++ -std=c++11 -o proyecto.exe main.cpp src\*.cpp src\Grafo\*.cpp

if %ERRORLEVEL% EQU 0 (
    echo Compilacion exitosa!
    echo Ejecutando proyecto...
    proyecto.exe
) else (
    echo Error en la compilacion!
    pause
)

