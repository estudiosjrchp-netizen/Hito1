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

    size_t get_hash(const K& key) const {
        return hash<K>{}(key) % capacity;
    }

public:
    HashTable(size_t size = 10) : capacity(size), num_elements(0) {
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
        // Agregar al final del bucket si no existe
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
                cout << "{" << kv.first << ": " << kv.second << "} -> ";
            }
            cout << "NULL\n";
        }
    }
};