#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <cstdlib>

#ifdef _WIN32
    // Windows
    #include <windows.h>
    #define CLEAR_SCREEN system("cls")
    #define PAUSE system("pause")
#elif __linux__ || __unix__ || __APPLE__
    // Linux/Unix/Mac
    #define CLEAR_SCREEN system("clear")
    #define PAUSE do { std::cout << "Presione Enter para continuar..."; std::cin.ignore(); std::cin.get(); } while(0)
#else
    // Plataforma desconocida
    #define CLEAR_SCREEN std::cout << "\033[2J\033[1;1H" // ANSI escape code
    #define PAUSE do { std::cout << "Presione Enter para continuar..."; std::cin.ignore(); std::cin.get(); } while(0)
#endif

#endif // PLATFORM_H

