#pragma once
#include <iostream>

// Detectamos el Sistema Operativo automáticamente
#ifdef _WIN32
    // --- LÓGICA PARA WINDOWS ---
    #include <conio.h>
    #include <windows.h>
    
    char obtenerTecla() {
        return _getch(); // Usamos la versión moderna de getch en Windows
    }

    void limpiarPantalla() {
        system("cls");
    }

#else
    // --- LÓGICA PARA LINUX / MAC ---
    #include <termios.h>
    #include <unistd.h>

    char obtenerTecla() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0) perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
        return buf;
    }

    void limpiarPantalla() {
        system("clear");
    }
    
#endif