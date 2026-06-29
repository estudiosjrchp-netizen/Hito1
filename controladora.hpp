#pragma once
#include "utiles/matrices_menus.hpp"
#include "utiles/teclado.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <functional>
#include <vector>
#include "entidades/Usuario.hpp"
#include "estructuras/Hash_Table.hpp"

using namespace std;

class Controladora {
private:
    HashTable<string, Usuario> tablaUsuarios;
    Usuario usuarioActual;
    bool usuarioLogueado;
    int generadorIds;

    // --- FUNCIONES DE DIBUJO Y CONSOLA ---
    void borrarArea(int x, int y, int ancho, int alto) {
        for (int i = 0; i < alto; i++) {
            gotoxy(x, y + i);
            cout << string(ancho, ' '); // Sobreescribe con espacios
        }
    }

    void dibujarMarcoEstaticoPrincipal() {
        limpiarPantalla();
        cursorVisible(false);
        gotoxy(0, 0); cout << string(110, '=');
        gotoxy(0, 39); cout << string(110, '=');

        int logoY = 2;
        int startX = (110 - 58) / 2;
        gotoxy(startX, logoY++); cout << "   ███████╗██████╗  ██████╗ ████████╗██╗███████╗██╗   ██╗ ";
        gotoxy(startX, logoY++); cout << "   ██╔════╝██╔══██╗██╔═══██╗╚══██╔══╝██║██╔════╝╚██╗ ██╔╝ ";
        gotoxy(startX, logoY++); cout << "   ███████╗██████╔╝██║   ██║   ██║   ██║█████╗   ╚████╔╝  ";
        gotoxy(startX, logoY++); cout << "   ╚════██║██╔═══╝ ██║   ██║   ██║   ██║██╔══╝    ╚██╔╝   ";
        gotoxy(startX, logoY++); cout << "   ███████║██║     ╚██████╔╝   ██║   ██║██║        ██║    ";
        gotoxy(startX, logoY++); cout << "   ╚══════╝╚═╝      ╚═════╝    ╚═╝   ╚═╝╚═╝        ╚═╝    ";

        gotoxy(0, 10); cout << string(110, '=');
    }

    void dibujarMarcoUsuarioLogueado() {
        limpiarPantalla();
        cursorVisible(false);
        gotoxy(0, 0); cout << string(110, '=');
        
        string titulo = "=== SPOTIFY: MENU PRINCIPAL ===";
        gotoxy((110 - titulo.length()) / 2, 2); cout << titulo;
        
        string info = "Usuario: " + usuarioActual.getUsername() + " | Email: " + usuarioActual.getEmail();
        gotoxy((110 - info.length()) / 2, 4); cout << info;
        
        gotoxy(0, 6); cout << string(110, '=');
        gotoxy(0, 39); cout << string(110, '=');
    }

    // --- MOTOR DEL MENÚ INTERACTIVO ---
    int menuInteractivo(vector<string> opciones, int startX, int startY) {
        int seleccion = 0;
        cursorVisible(false);
        
        while (true) {
            // Imprimir opciones
            for (size_t i = 0; i < opciones.size(); i++) {
                gotoxy(startX, startY + i + (i * 1)); // i * 1 para dar espaciado
                if (i == seleccion) {
                    cout << "\033[32m> " << opciones[i] << " <\033[0m   "; // Verde y remarcado
                } else {
                    cout << "  " << opciones[i] << "     ";
                }
            }
            cout.flush();
            char tecla = obtenerTecla();
            
            // W o Flecha Arriba
            if (tecla == 'w' || tecla == 'W' || tecla == 72 || tecla == 65) {
                seleccion--;
                if (seleccion < 0) seleccion = opciones.size() - 1;
            } 
            // S o Flecha Abajo
            else if (tecla == 's' || tecla == 'S' || tecla == 80 || tecla == 66) {
                seleccion++;
                if (seleccion >= opciones.size()) seleccion = 0;
            } 
            // Enter
            else if (tecla == '\r' || tecla == '\n') {
                return seleccion;
            }
            // Lógica para flechas en Linux (Secuencia \033[A o \033[B)
            else if (tecla == 27) { 
                char tecla2 = obtenerTecla();
                if (tecla2 == '[') {
                    char tecla3 = obtenerTecla();
                    if (tecla3 == 'A') { // Arriba
                        seleccion--;
                        if (seleccion < 0) seleccion = opciones.size() - 1;
                    } else if (tecla3 == 'B') { // Abajo
                        seleccion++;
                        if (seleccion >= opciones.size()) seleccion = 0;
                    }
                }
            }
        }
    }

    // --- CARGA DE DATOS ---
    void cargarUsuarios() {
        ifstream archivo("datos/usuarios.txt");
        if (!archivo.is_open()) return;
        string linea;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string user, email, pass;
            getline(ss, user, ',');
            getline(ss, email, ',');
            getline(ss, pass, ',');
            Usuario nuevoUser(user, pass, email, generadorIds++);
            tablaUsuarios.insert(user, nuevoUser);
        }
        archivo.close();
    }

    void guardarNuevoUsuario(const Usuario& u) {
        ofstream archivo("datos/usuarios.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "\n" << u.getUsername() << "," << u.getEmail() << "," << u.getPassword();
            archivo.close();
        }
    }

public:
    Controladora() : usuarioLogueado(false), generadorIds(1) {
        auto hashComplejo = [](const string& clave) -> size_t {
            size_t hashVal = 0;
            size_t p = 31;
            for (char c : clave) {
                hashVal = hashVal * p + c;
            }
            return hashVal;
        };
        tablaUsuarios = HashTable<string, Usuario>(100, hashComplejo);
        cargarUsuarios();
    }

    void iniciar() {
        dibujarMarcoEstaticoPrincipal();
        bool salir = false;
        
        while (!salir) {
            borrarArea(5, 12, 100, 20); // Limpiar zona dinámica de dibujo central
            
            vector<string> opciones = {
                "Iniciar Sesion", 
                "Crear Cuenta Nueva", 
                "Salir del Sistema"
            };
            
            int startX = (110 - 20) / 2; // Centrado manual aprox
            int seleccion = menuInteractivo(opciones, startX, 15);

            if (seleccion == 0) iniciarSesion();
            else if (seleccion == 1) crearCuenta();
            else if (seleccion == 2) salir = true;
        }
        
        limpiarPantalla();
        gotoxy(0,0);
        cout << "\033[32mSaliendo de la app. Hasta pronto!\033[0m\n";
    }

    void crearCuenta() {
        borrarArea(5, 12, 100, 20);
        string titulo = "--- CREAR NUEVA CUENTA ---";
        gotoxy((110 - titulo.length()) / 2, 13); cout << "\033[33m" << titulo << "\033[0m"; // Título en amarillo

        string user, email, pass;
        gotoxy(30, 16); cout << "Nombre de usuario  : ";
        gotoxy(30, 18); cout << "Correo Electronico : ";
        gotoxy(30, 20); cout << "Contrasena         : ";

        cursorVisible(true);
        gotoxy(51, 16); getline(cin, user);
        
        Usuario temp;
        if (tablaUsuarios.search(user, temp)) {
            cursorVisible(false);
            gotoxy(30, 23); cout << "\033[31m[!] El usuario ya existe. Presione Enter...\033[0m";
            obtenerTecla();
            return;
        }

        gotoxy(51, 18); getline(cin, email);
        gotoxy(51, 20); getline(cin, pass);
        cursorVisible(false);

        Usuario nuevoUsuario(user, pass, email, generadorIds++);
        tablaUsuarios.insert(user, nuevoUsuario);
        guardarNuevoUsuario(nuevoUsuario);
        
        gotoxy(30, 23); cout << "\033[32m[+] Cuenta creada con exito! Presione Enter...\033[0m";
        obtenerTecla();
    }

    void iniciarSesion() {
        borrarArea(5, 12, 100, 20);
        string titulo = "--- INICIAR SESION ---";
        gotoxy((110 - titulo.length()) / 2, 13); cout << "\033[33m" << titulo << "\033[0m";

        string user, pass;
        gotoxy(35, 16); cout << "Usuario    : ";
        gotoxy(35, 18); cout << "Contrasena : ";

        cursorVisible(true);
        gotoxy(48, 16); getline(cin, user);
        gotoxy(48, 18); getline(cin, pass);
        cursorVisible(false);

        Usuario userEncontrado;
        if (tablaUsuarios.search(user, userEncontrado) && userEncontrado.getPassword() == pass) {
            usuarioActual = userEncontrado;
            usuarioLogueado = true;
            menuPrincipal();
            dibujarMarcoEstaticoPrincipal(); // Al regresar al menu principal de afuera, redibuja el logo grande
        } else {
            gotoxy(35, 21); cout << "\033[31m[!] Usuario o Contrasena incorrectos. Presione Enter...\033[0m";
            obtenerTecla();
        }
    }

    void menuPrincipal() {
        dibujarMarcoUsuarioLogueado();
        bool cerrarSesion = false;
        
        while (!cerrarSesion) {
            borrarArea(5, 8, 100, 25);
            
            vector<string> opciones = {
                "Perfil y Usuarios",
                "Explorar Canciones (Arbol AVL)",
                "Mis Playlists (Lista Doblemente Enlazada)",
                "Recomendaciones Inteligentes (Grafo)",
                "Cerrar Sesion"
            };
            
            int startX = (110 - 45) / 2;
            int seleccion = menuInteractivo(opciones, startX, 10);

            if (seleccion >= 0 && seleccion <= 3) {
                borrarArea(5, 8, 100, 25);
                gotoxy(35, 15); cout << "\033[33mModulo en construccion... Presione Enter.\033[0m";
                obtenerTecla();
            } else if (seleccion == 4) {
                usuarioLogueado = false;
                cerrarSesion = true;
            }
        }
    }
};