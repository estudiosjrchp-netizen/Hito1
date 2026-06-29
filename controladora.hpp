#pragma once
#include "utiles/Dependencias.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <functional>
#include <vector>
#include <ctime> // Para generar datos aleatorios
#include "entidades/Usuario.hpp"
#include "estructuras/Hash_Table.hpp"
#include "utiles/algoritmos.hpp" // Fundamental para usar el template de ordenamiento

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
        gotoxy(startX, logoY++); cout << "           _____ _____  ____ _______ _____ _________     __";
        gotoxy(startX, logoY++); cout << "          / ____|  __ \\/ __ \\__   __|_   _|  ____\\ \\   / /";
        gotoxy(startX, logoY++); cout << "         | (___ | |__) | |  | | | |    | | | |__   \\ \\_/ / ";
        gotoxy(startX, logoY++); cout << "          \\___ \\|  ___/| |  | | | |    | | |  __|   \\   /  ";
        gotoxy(startX, logoY++); cout << "          ____) | |    | |__| | | |   _| |_| |       | |   ";
        gotoxy(startX, logoY++); cout << "         |_____/|_|     \\____/  |_|  |_____|_|       |_|   ";
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

    // --- MOTOR DEL MENU INTERACTIVO ---
    int menuInteractivo(vector<string> opciones, int startX, int startY) {
        int seleccion = 0;
        cursorVisible(false);
        
        while (true) {
            // Imprimir opciones
            for (size_t i = 0; i < opciones.size(); i++) {
                gotoxy(startX, startY + i + (i * 1)); // i * 1 para dar espaciado
                if (int(i) == seleccion) {
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
                if (seleccion >= int(opciones.size())) seleccion = 0;
            } 
            // Enter
            else if (tecla == '\r' || tecla == '\n') {
                return seleccion;
            }
            // Logica para flechas en Linux (Secuencia \033[A o \033[B)
            else if (tecla == 27) { 
                char tecla2 = obtenerTecla();
                if (tecla2 == '[') {
                    char tecla3 = obtenerTecla();
                    if (tecla3 == 'A') { // Arriba
                        seleccion--;
                        if (seleccion < 0) seleccion = opciones.size() - 1;
                    } else if (tecla3 == 'B') { // Abajo
                        seleccion++;
                        if (seleccion >= int(opciones.size())) seleccion = 0;
                    }
                }
            }
        }
    }

    // --- CARGA Y GUARDADO DE DATOS ---
    void cargarUsuarios() {
        ifstream archivo("datos/usuarios.txt");
        if (!archivo.is_open()) return;
        
        string linea;
        int maxId = 0;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string idStr, user, email, pass;
            
            getline(ss, idStr, ',');
            getline(ss, user, ',');
            getline(ss, email, ',');
            getline(ss, pass, ',');
            int idLeido = stoi(idStr);
            
            if (idLeido >= maxId) {
                maxId = idLeido;
            }
            Usuario nuevoUser(user, pass, email, idLeido);
            tablaUsuarios.insert(user, nuevoUser);
        }
        
        if (maxId > 0) {
            generadorIds = maxId + 1;
        }
        archivo.close();
    }

    void guardarNuevoUsuario(const Usuario& u) {
        ofstream archivo("datos/usuarios.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "\n" << u.getId() << "," << u.getUsername() << "," << u.getEmail() << "," << u.getPassword();
            archivo.close();
        }
    }

    // --- GENERADOR DE DATASET (Requisito Hito 1) ---
    void generarDataset() {
        borrarArea(5, 12, 100, 20);
        string titulo = "--- GENERADOR DE DATASET ---";
        gotoxy((110 - titulo.length()) / 2, 13); cout << "\033[33m" << titulo << "\033[0m";

        string nombres[] = {"Alonso", "Beto", "Carlos", "Diana", "Elena", "Fabio", "Gina", "Hugo", "Ines", "Juan", "Karla", "Luis", "Maria", "Nadia", "Omar", "Paula", "Quique", "Rosa", "Sofia", "Tito"};
        int generados = 0;

        for (int i = 0; i < 50; ++i) { // Generamos 50 usuarios de prueba rapidos
            string baseNombre = nombres[rand() % 20];
            string user = baseNombre + to_string(rand() % 9999);
            string email = user + "@mail.com";
            string pass = "pass123";

            Usuario temp;
            if (!tablaUsuarios.search(user, temp)) { // Si no existe, lo insertamos
                Usuario nuevo(user, pass, email, generadorIds++);
                tablaUsuarios.insert(user, nuevo);
                guardarNuevoUsuario(nuevo);
                generados++;
            }
        }

        gotoxy(30, 16); cout << "\033[32m[+] Dataset generado exitosamente!\033[0m";
        gotoxy(30, 18); cout << "Se han insertado " << generados << " nuevos usuarios de prueba.";
        gotoxy(30, 20); cout << "Presione Enter para continuar...";
        obtenerTecla();
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
        srand(time(0)); // Inicializamos la semilla para el generador de datos aleatorios
        dibujarMarcoEstaticoPrincipal();
        bool salir = false;
        
        while (!salir) {
            borrarArea(5, 12, 100, 20);
            
            vector<string> opciones = {
                "Iniciar Sesion", 
                "Crear Cuenta Nueva", 
                "Generar Dataset (Usuarios de Prueba)",
                "Salir del Sistema"
            };
            
            int startX = (110 - 40) / 2;
            int seleccion = menuInteractivo(opciones, startX, 15);

            if (seleccion == 0) iniciarSesion();
            else if (seleccion == 1) crearCuenta();
            else if (seleccion == 2) generarDataset();
            else if (seleccion == 3) salir = true;
        }
        
        limpiarPantalla();
        gotoxy(0,0);
        cout << "\033[32mSaliendo de la app. Hasta pronto!\033[0m\n";
    }

    void crearCuenta() {
        borrarArea(5, 12, 100, 20);
        string titulo = "--- CREAR NUEVA CUENTA ---";
        gotoxy((110 - titulo.length()) / 2, 13); cout << "\033[33m" << titulo << "\033[0m";
        
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
            dibujarMarcoEstaticoPrincipal(); // Redibuja el logo grande al salir de sesion
        } else {
            gotoxy(35, 21); cout << "\033[31m[!] Usuario o Contrasena incorrectos. Presione Enter...\033[0m";
            obtenerTecla();
        }
    }

    // --- MANEJO DE ORDENAMIENTOS CON TEMPLATES Y LAMBDAS ---
    void menuPerfilUsuarios() {
        bool salir = false;
        while(!salir) {
            borrarArea(5, 8, 100, 25);
            string titulo = "--- LISTA DE USUARIOS REGISTRADOS ---";
            gotoxy((110 - titulo.length()) / 2, 9); cout << "\033[36m" << titulo << "\033[0m";

            vector<string> opciones = {
                "Mostrar ordenados por ID (Ascendente)",
                "Mostrar ordenados por Nombre (Alfabetico)",
                "Regresar al Menu Principal"
            };
            
            int startX = (110 - 45) / 2;
            int seleccion = menuInteractivo(opciones, startX, 12);
            
            if (seleccion == 2) {
                salir = true;
                continue;
            }

            vector<Usuario> lista = tablaUsuarios.get_all();
            
            // Aqui creamos la funcion Lambda dependiendo de la decision del usuario
            function<bool(Usuario, Usuario)> comparador;

            if (seleccion == 0) {
                // Lambda para ordenar por ID
                comparador = [](Usuario a, Usuario b) { return a.getId() < b.getId(); };
            } else {
                // Lambda para ordenar por Username
                comparador = [](Usuario a, Usuario b) { return a.getUsername() < b.getUsername(); };
            }

            // Llamamos a tu algoritmo genérico (template) pasandole la lambda
            if (!lista.empty()) {
                mergeSort<Usuario>(lista, 0, lista.size() - 1, comparador);
            }

            // Impresion de resultados en pantalla
            borrarArea(5, 8, 100, 25);
            gotoxy(10, 9); cout << "\033[36m--- RESULTADOS ORDENADOS ---\033[0m";
            gotoxy(10, 11); cout << "ID\tNOMBRE DE USUARIO\t\tCORREO ELECTRONICO";
            gotoxy(10, 12); cout << "-------------------------------------------------------------------------";
            
            int y = 13;
            for (size_t i = 0; i < lista.size(); i++) {
                gotoxy(10, y++);
                cout << lista[i].getId() << "\t" << lista[i].getUsername();
                // Tabulaciones para que se vea alineado en consola
                if (lista[i].getUsername().length() < 8) cout << "\t\t\t";
                else if (lista[i].getUsername().length() < 16) cout << "\t\t";
                else cout << "\t";
                
                cout << lista[i].getEmail();
                
                if (y > 28) {
                    gotoxy(10, y); cout << "... y " << lista.size() - i - 1 << " mas. (Espacio en pantalla limitado)";
                    break;
                }
            }
            
            gotoxy(10, y + 2); cout << "Presione Enter para regresar...";
            obtenerTecla();
        }
    }

    void menuPrincipal() {
        dibujarMarcoUsuarioLogueado();
        bool cerrarSesion = false;
        
        while (!cerrarSesion) {
            borrarArea(5, 8, 100, 25);
            
            vector<string> opciones = {
                "Perfil y Usuarios (Ordenamiento c/ Lambdas)",
                "Explorar Canciones (Arbol AVL)",
                "Mis Playlists (Lista Doblemente Enlazada)",
                "Recomendaciones Inteligentes (Grafo)",
                "Cerrar Sesion"
            };
            
            int startX = (110 - 45) / 2;
            int seleccion = menuInteractivo(opciones, startX, 10);

            if (seleccion == 0) {
                menuPerfilUsuarios();
                dibujarMarcoUsuarioLogueado(); // Limpia la pantalla al volver de la subpantalla
            } else if (seleccion >= 1 && seleccion <= 3) {
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