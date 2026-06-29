#pragma once
#include "utiles/matrices_menus.hpp"
#include "utiles/teclado.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <functional>
#include "entidades/Usuario.hpp"
#include "estructuras/Hash_Table.hpp"

using namespace std;

class Controladora {
private:
    HashTable<string, Usuario> tablaUsuarios;
    Usuario usuarioActual;
    bool usuarioLogueado;
    int generadorIds;

    void imprimirCentrado(string texto) {
        int anchoTotal = 110;
        int padding = (anchoTotal - texto.length()) / 2;
        if (padding > 0) {
            cout << string(padding, ' ') << texto << endl;
        } else {
            cout << texto << endl;
        }
    }

    void cargarUsuarios() {
        ifstream archivo("datos/usuarios.txt");
        if (!archivo.is_open()) return;

        string linea;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string user, email, pass;
            
            // Leemos según tu formato: username, email, password
            getline(ss, user, ',');
            getline(ss, email, ',');
            getline(ss, pass, ',');
            
            // Instanciamos el usuario y generamos un ID
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
        // RÚBRICA: Función Lambda para Hash Complejo (Polynomial Rolling Hash)
        auto hashComplejo = [](const string& clave) -> size_t {
            size_t hashVal = 0;
            size_t p = 31;
            for (char c : clave) {
                hashVal = hashVal * p + c;
            }
            return hashVal;
        };

        // RÚBRICA: Instanciar Hash Table con template y lambda
        tablaUsuarios = HashTable<string, Usuario>(100, hashComplejo);
        
        cargarUsuarios();
    }

    void iniciar() {
        cursorVisible(true);
        bool salir = false;
        while (!salir) {
            limpiarPantalla();
            cout << string(110, '=') << "\n\n";
            imprimirCentrado("   ███████╗██████╗  ██████╗ ████████╗██╗███████╗██╗   ██╗ ");
            imprimirCentrado("   ██╔════╝██╔══██╗██╔═══██╗╚══██╔══╝██║██╔════╝╚██╗ ██╔╝ ");
            imprimirCentrado("   ███████╗██████╔╝██║   ██║   ██║   ██║█████╗   ╚████╔╝  ");
            imprimirCentrado("   ╚════██║██╔═══╝ ██║   ██║   ██║   ██║██╔══╝    ╚██╔╝   ");
            imprimirCentrado("   ███████║██║     ╚██████╔╝   ██║   ██║██║        ██║    ");
            imprimirCentrado("   ╚══════╝╚═╝      ╚═════╝    ╚═╝   ╚═╝╚═╝        ╚═╝    ");
            cout << "\n";
            cout << string(110, '=') << "\n\n";
            imprimirCentrado("1. Iniciar Sesion");
            imprimirCentrado("2. Crear Cuenta Nueva");
            imprimirCentrado("3. Salir del Sistema");
            cout << "\n" << string(110, '=') << "\n";
            cout << "> Seleccione una opcion: ";
            
            string opcion;
            getline(cin, opcion);

            if (opcion == "1") iniciarSesion();
            else if (opcion == "2") crearCuenta();
            else if (opcion == "3") salir = true;
        }
        limpiarPantalla();
        cout << "\nSaliendo de la app. Hasta pronto!\n";
    }

    void crearCuenta() {
        limpiarPantalla();
        cout << string(110, '-') << "\n";
        imprimirCentrado("--- CREAR NUEVA CUENTA ---");
        cout << string(110, '-') << "\n\n";
        
        string user, email, pass;
        cout << "> Ingrese un nombre de usuario: ";
        getline(cin, user);
        
        Usuario temp;
        // RÚBRICA: Búsqueda O(1) usando el HashTable
        if (tablaUsuarios.search(user, temp)) {
            cout << "\n[!] El usuario '" << user << "' ya existe. Presione Enter para volver...";
            obtenerTecla();
            return;
        }

        cout << "> Ingrese su correo electronico: ";
        getline(cin, email);
        cout << "> Ingrese una contrasena: ";
        getline(cin, pass);

        Usuario nuevoUsuario(user, pass, email, generadorIds++);
        tablaUsuarios.insert(user, nuevoUsuario);
        guardarNuevoUsuario(nuevoUsuario);
        
        cout << "\n[+] Cuenta creada con exito! Ya puedes iniciar sesion. Presione Enter...";
        obtenerTecla();
    }

    void iniciarSesion() {
        limpiarPantalla();
        cout << string(110, '-') << "\n";
        imprimirCentrado("--- INICIAR SESION ---");
        cout << string(110, '-') << "\n\n";
        
        string user, pass;
        cout << "> Usuario: ";
        getline(cin, user);
        cout << "> Contrasena: ";
        getline(cin, pass);

        Usuario userEncontrado;
        // Pasamos 'userEncontrado' por referencia como pide tu método search
        if (tablaUsuarios.search(user, userEncontrado)) {
            if (userEncontrado.getPassword() == pass) {
                usuarioActual = userEncontrado;
                usuarioLogueado = true;
                menuPrincipal(); // Ir al menú interno
            } else {
                cout << "\n[!] Contrasena incorrecta. Presione Enter para volver...";
                obtenerTecla();
            }
        } else {
            cout << "\n[!] Usuario no encontrado. Presione Enter para volver...";
            obtenerTecla();
        }
    }

    void menuPrincipal() {
        bool cerrarSesion = false;
        while (!cerrarSesion) {
            limpiarPantalla();
            cout << string(110, '=') << "\n";
            imprimirCentrado("=== SPOTIFY: MENU PRINCIPAL ===");
            imprimirCentrado("Usuario Actual: " + usuarioActual.getUsername() + " | Email: " + usuarioActual.getEmail());
            cout << string(110, '=') << "\n\n";
            
            imprimirCentrado("1. Perfil y Usuarios");
            imprimirCentrado("2. Explorar Canciones (Arbol AVL)");
            imprimirCentrado("3. Mis Playlists (Lista Doblemente Enlazada)");
            imprimirCentrado("4. Recomendaciones Inteligentes (Grafo)");
            imprimirCentrado("5. Cerrar Sesion");
            cout << "\n" << string(110, '=') << "\n";
            cout << "> Seleccione una opcion: ";

            string opcion;
            getline(cin, opcion);

            if (opcion == "1") {
                cout << "\nModulo en construccion... Presione Enter."; obtenerTecla();
            } else if (opcion == "2") {
                cout << "\nModulo en construccion... Presione Enter."; obtenerTecla();
            } else if (opcion == "3") {
                cout << "\nModulo en construccion... Presione Enter."; obtenerTecla();
            } else if (opcion == "4") {
                cout << "\nModulo en construccion... Presione Enter."; obtenerTecla();
            } else if (opcion == "5") {
                usuarioLogueado = false;
                cerrarSesion = true;
            }
        }
    }
};