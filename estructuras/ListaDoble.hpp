#ifndef LISTADOBLE_HPP
#define LISTADOBLE_HPP

template <typename T>
class ListaDoble {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo* anterior;
        Nodo(T d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
    };
    Nodo* inicio;
    Nodo* fin;
    int tamano;

public:
    ListaDoble() : inicio(nullptr), fin(nullptr), tamano(0) {}

    void insertarFinal(T dato) {
        Nodo* nuevo = new Nodo(dato);
        if (!inicio) {
            inicio = fin = nuevo;
        } else {
            fin->siguiente = nuevo;
            nuevo->anterior = fin;
            fin = nuevo;
        }
        tamano++;
    }

    int getTamano() { return tamano; }
};

#endif