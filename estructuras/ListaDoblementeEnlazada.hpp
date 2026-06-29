#include <iostream>

using namespace std;

template <typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(T valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaDoblementeEnlazada {
private:
    Nodo<T>* cabeza; 
    Nodo<T>* cola;   
    size_t longitud; 

public:
    ListaDoblementeEnlazada() : cabeza(nullptr), cola(nullptr), longitud(0) {}

    ~ListaDoblementeEnlazada() {
        vaciar();
    }

    void insertar_final(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (!cabeza) { 
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
        longitud++;
    }

    void insertar_inicio(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (!cabeza) { // Si la lista está vacía
            cabeza = cola = nuevoNodo;
        } else {
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
            cabeza = nuevoNodo;
        }
        longitud++;
    }

    bool eliminar(T valor) {
        Nodo<T>* actual = cabeza;
        while (actual) {
            if (actual->dato == valor) {
                if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
                else cabeza = actual->siguiente; 
                if (actual->siguiente) actual->siguiente->anterior = actual->anterior;
                else cola = actual->anterior; 
                delete actual; 
                longitud--;
                return true; 
            }
            actual = actual->siguiente;
        }
        return false; 
    }

    void mostrar_adelante() const {
        Nodo<T>* actual = cabeza;
        cout << "[ ";
        while (actual) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        cout << "]" << endl;
    }

    void mostrar_atras() const {
        Nodo<T>* actual = cola;
        cout << "[ ";
        while (actual) {
            cout << actual->dato << " ";
            actual = actual->anterior;
        }
        cout << "]" << endl;
    }

    void vaciar() {
        Nodo<T>* actual = cabeza;
        while (actual) {
            Nodo<T>* nodoSiguiente = actual->siguiente;
            delete actual;
            actual = nodoSiguiente;
        }
        cabeza = cola = nullptr;
        longitud = 0;
    }

    size_t obtener_tamano() const {
        return longitud;
    }

    // Verificar si la lista está vacía
    bool esta_vacia() const {
        return longitud == 0;
    }
};