#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>

using namespace std;

template <typename K, typename V>
class HashTable {
private:
    vector<list<pair<K, V>>> table;
    size_t num_elements;
    size_t capacity;
    
    // Atributo para almacenar la lambda de la funcion Hash compleja
    function<size_t(const K&)> hash_func;

    size_t get_hash(const K& key) const {
        return hash_func(key) % capacity; // Usamos la lambda en lugar de std::hash
    }

public:
    // El constructor ahora recibe la lambda. Por defecto usa una basica si no se envia nada.
    HashTable(size_t size = 10, function<size_t(const K&)> hf = [](const K& k){ return hash<K>{}(k); }) 
        : capacity(size), num_elements(0), hash_func(hf) {
        table.resize(capacity);
    }

    void insert(const K& key, const V& value) {
        size_t index = get_hash(key);
        for (auto& kv : table[index]) {
            if (kv.first == key) {
                kv.second = value; // Actualizar si la clave ya existe
                return;
            }
        }
        table[index].emplace_back(key, value);
        num_elements++;
    }

    bool search(const K& key, V& value_out) const {
        size_t index = get_hash(key);
        for (const auto& kv : table[index]) {
            if (kv.first == key) {
                value_out = kv.second;
                return true;
            }
        }
        return false;
    }

    bool remove(const K& key) {
        size_t index = get_hash(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                num_elements--;
                return true;
            }
        }
        return false;
    }

    void display() const {
        for (size_t i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            for (const auto& kv : table[i]) {
                cout << "{" << kv.first << ": ...} -> ";
            }
            cout << "NULL\n";
        }
    }

    // --- NUEVO METODO PARA EL HITO 1 ---
    // Permite extraer los datos al vector para usar el ordenamiento avanzado
    vector<V> get_all() const {
        vector<V> elements;
        for (const auto& bucket : table) {
            for (const auto& kv : bucket) {
                elements.push_back(kv.second);
            }
        }
        return elements;
    }
};