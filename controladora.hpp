#pragma once
#include "utiles/matrices_menus.hpp"
#include "utiles/teclado.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "entidades/Usuario.hpp"
#include "estructuras/Hash_Table.hpp"




class Controladora {
private:
    bool ejecutando;
    int opcionSeleccionada;

public:
    Controladora() {
        ejecutando = true;
        opcionSeleccionada = 0;
    }

    void iniciar() {
        cursorVisible(false); 
        //dibuando la parte estatica del fondo
        dibujarInterfazEstatica(); 

        // 2. Bucle principal de la aplicación, la wea que va a cambiar, generalmente letras
        while (ejecutando) {
            mostrarMenuTextual();
            procesarEntrada();
        }
        
        // Al salir, limpiamos pantalla 
        std::cout << "\033[2J\033[1;1H"; 
    }

private:
    void dibujarInterfazEstatica();
    void mostrarMenuTextual();
    void borrarPorcion(int filaInicio, int colInicio, int alto, int ancho);
    void procesarEntrada();
    void ejecutarAccion(int opcion);
};


void Controladora::borrarPorcion(int filaInicio, int colInicio, int alto, int ancho) {
    for (int i = 0; i < alto; i++) {

        // \033[Y;XH mueve el cursor a la Fila Y, Columna X
        std::cout << "\033[" << (filaInicio + i) << ";" << colInicio << "H";
        
        // Imprime espacios para "limpiar" esa línea específica
        for (int j = 0; j < ancho; j++) {
            std::cout << " ";
        }
    }
}


void Controladora::dibujarInterfazEstatica() {
    // Limpiamos todo al arrancar la app por primera vez
    std::cout << "\033[2J\033[1;1H"; 

    std::cout << "\033[33m"; 
    
    std::cout << "\033[0m";  
}

void Controladora::mostrarMenuTextual() {
    // Coordenadas calculadas para 110x40; RECORDAR MANIPULAR LOS AJUSTES DE LA VENTANA/TERMINAL/CONSOLA PARA QUE COINCIDA CON ESTO, SINO SE DESORDENA TODO
    int fila = 17;
    int col = 37;

    // 1. Borramos SOLO el área donde va el menú (alto 8, ancho 35)
    borrarPorcion(fila, col, 8, 35); 

    // 2. Redibujamos el texto en el centro exacto
    std::cout << "\033[" << fila << ";" << col << "H" << "=== SPOTIFY: MENÚ PRINCIPAL ===";
    
    // Usamos el color verde de Spotify para la opción seleccionada
    std::cout << "\033[" << fila + 2 << ";" << col << "H" << (opcionSeleccionada == 0 ? "\033[32m> 1. Perfil y Usuarios\033[0m" : "  1. Perfil y Usuarios");             
    std::cout << "\033[" << fila + 3 << ";" << col << "H" << (opcionSeleccionada == 1 ? "\033[32m> 2. Explorar Canciones\033[0m" : "  2. Explorar Canciones");             
    std::cout << "\033[" << fila + 4 << ";" << col << "H" << (opcionSeleccionada == 2 ? "\033[32m> 3. Mis Playlists\033[0m" : "  3. Mis Playlists");
    std::cout << "\033[" << fila + 5 << ";" << col << "H" << (opcionSeleccionada == 3 ? "\033[32m> 4. Salir\033[0m" : "  4. Salir");
    std::cout << std::flush; 
}

void Controladora::procesarEntrada() {
    // ESTA FUNCIÓN DEBE DETENER EL BUCLE HASTA QUE PRESIONES ALGO.
    char tecla = obtenerTecla(); 

    // En Linux, las flechas envían 27 (ESC), 91 ([), y luego 65 (Arriba) o 66 (Abajo)
    if (tecla == 27) { 
        char corchete = obtenerTecla();
        if (corchete == 91) {
            char direccion = obtenerTecla();
            if (direccion == 65) { // Flecha Arriba
                opcionSeleccionada--;
                if (opcionSeleccionada < 0) opcionSeleccionada = 3; // Efecto circular
            } else if (direccion == 66) { // Flecha Abajo
                opcionSeleccionada++;
                if (opcionSeleccionada > 3) opcionSeleccionada = 0; // Efecto circular
            }
        }
    } 

    else if (tecla == 10 || tecla == 13) {
        ejecutarAccion(opcionSeleccionada);
    }
}

void Controladora::ejecutarAccion(int opcion) {

    borrarPorcion(25, 37, 2, 50);
    std::cout << "\033[25;37H"; 
    
    switch(opcion) {
        case 0:
            std::cout << "Abriendo módulo de Perfil y Usuarios...";
            break;
        case 1:
            std::cout << "Abriendo Explorador de Canciones...";
            break;
        case 2:
            std::cout << "Cargando Playlists...";
            break;
        case 3:
            std::cout << "Saliendo de la app. ¡Hasta pronto!";
            ejecutando = false; 
            break;
    }
    
 
    std::cout << "\nPresiona cualquier tecla para volver...";
    obtenerTecla(); 
}