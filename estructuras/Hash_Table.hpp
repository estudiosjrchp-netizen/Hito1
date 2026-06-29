#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>
#include <string>
#include <functional>

int miFuncionHashCompleja(const std::string& clave, int capacidad_tabla) {
    long long hash_value = 0;
    const int p = 31;
    const int m = 1e9 + 9;
    long long p_pow = 1;
    for (char c : clave) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value % capacidad_tabla;
}

template <typename K, typename V>
class Hash_Table {
private:
    struct Nodo {
        K clave;
        V valor;
        Nodo* siguiente;
        Nodo(K c, V v) : clave(c), valor(v), siguiente(nullptr) {}
    };
    std::vector<Nodo*> tabla;
    int capacidad;

public:
    Hash_Table(int cap = 101) : capacidad(cap) {
        tabla.assign(capacidad, nullptr);
    }

    void insertar(const K& clave, const V& valor) {
        int indice = miFuncionHashCompleja(clave, capacidad);
        Nodo* nuevo = new Nodo(clave, valor);
        nuevo->siguiente = tabla[indice];
        tabla[indice] = nuevo;
    }

    V* buscar(const K& clave) {
        int indice = miFuncionHashCompleja(clave, capacidad);
        Nodo* actual = tabla[indice];
        while (actual != nullptr) {
            if (actual->clave == clave) return &(actual->valor);
            actual = actual->siguiente;
        }
        return nullptr;
    }
};

#endif