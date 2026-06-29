#pragma once
#include "utiles/matrices_menus.hpp"
#include "utiles/teclado.hpp"
#include <iostream>

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

    // Aquí llamas a tu matriz de utiles/matrices_menus.hpp
    std::cout << "\033[33m"; // Cambiar color a Amarillo
    
    // EJEMPLO: Dibujar logo en la fila 2, columna 5
    // dibujarLogoSpotifyMatriz(); 
    
    std::cout << "\033[0m";  // RESET de color importantísimo
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
    // Importante: forzar que la consola imprima los cambios inmediatamente
    std::cout << std::flush; 
}

void Controladora::procesarEntrada() {
    // Asumiendo que teclado.hpp tiene una función que lee un caracter.
    // ESTA FUNCIÓN DEBE DETENER EL BUCLE HASTA QUE PRESIONES ALGO.
    char tecla = obtenerTecla(); // <- Reemplaza por tu función real de teclado.hpp
    
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
    // Tecla Enter (en Linux suele ser 10 ('\n'), en otros 13 ('\r'))
    else if (tecla == 10 || tecla == 13) {
        ejecutarAccion(opcionSeleccionada);
    }
}

void Controladora::ejecutarAccion(int opcion) {
    // Borramos el área de mensajes abajo del menú para dar feedback
    borrarPorcion(25, 37, 2, 50);
    std::cout << "\033[25;37H"; // Nos posicionamos debajo del menú
    
    switch(opcion) {
        case 0:
            std::cout << "Abriendo módulo de Perfil y Usuarios...";
            // Aquí instanciarías Usuario.hpp o Perfil.hpp
            break;
        case 1:
            std::cout << "Abriendo Explorador de Canciones...";
            // Aquí enlazas con Cancion.hpp
            break;
        case 2:
            std::cout << "Cargando Playlists...";
            // Aquí enlazas con PlayList.hpp
            break;
        case 3:
            std::cout << "Saliendo de la app. ¡Hasta pronto!";
            ejecutando = false; // Rompe el bucle principal
            break;
    }
    
    // Pausar un momento para que el profe vea que entró a la opción
    // Puedes reemplazar esto con tu propia función de espera
    std::cout << "\nPresiona cualquier tecla para volver...";
    obtenerTecla(); 
}