#pragma once
#include <iostream>
#include <algorithm>
#include <functional>

template <typename T>
class NodoAVL {
public:
    T dato;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;
    NodoAVL(T valor) : dato(valor), izq(nullptr), der(nullptr), altura(1) {}
};

template <typename T>
class ArbolAVL {
private:
    NodoAVL<T>* raiz;

    int altura(NodoAVL<T>* N) {
        if (N == nullptr) return 0;
        return N->altura;
    }

    NodoAVL<T>* rotacionDerecha(NodoAVL<T>* y) {
        NodoAVL<T>* x = y->izq;
        NodoAVL<T>* T2 = x->der;
        x->der = y;
        y->izq = T2;
        y->altura = std::max(altura(y->izq), altura(y->der)) + 1;
        x->altura = std::max(altura(x->izq), altura(x->der)) + 1;
        return x;
    }

    NodoAVL<T>* rotacionIzquierda(NodoAVL<T>* x) {
        NodoAVL<T>* y = x->der;
        NodoAVL<T>* T2 = y->izq;
        y->izq = x;
        x->der = T2;
        x->altura = std::max(altura(x->izq), altura(x->der)) + 1;
        y->altura = std::max(altura(y->izq), altura(y->der)) + 1;
        return y;
    }

    int obtenerBalance(NodoAVL<T>* N) {
        if (N == nullptr) return 0;
        return altura(N->izq) - altura(N->der);
    }

    NodoAVL<T>* insertar(NodoAVL<T>* nodo, T clave, std::function<int(T, T)> comparador) {
        if (nodo == nullptr) return new NodoAVL<T>(clave);

        int cmp = comparador(clave, nodo->dato);
        if (cmp < 0)
            nodo->izq = insertar(nodo->izq, clave, comparador);
        else if (cmp > 0)
            nodo->der = insertar(nodo->der, clave, comparador);
        else
            return nodo;

        nodo->altura = 1 + std::max(altura(nodo->izq), altura(nodo->der));
        int balance = obtenerBalance(nodo);

        if (balance > 1 && comparador(clave, nodo->izq->dato) < 0) return rotacionDerecha(nodo);
        if (balance < -1 && comparador(clave, nodo->der->dato) > 0) return rotacionIzquierda(nodo);
        if (balance > 1 && comparador(clave, nodo->izq->dato) > 0) {
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && comparador(clave, nodo->der->dato) < 0) {
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }
        return nodo;
    }

    void inOrden(NodoAVL<T>* raiz, std::function<void(T)> accion) {
        if (raiz != nullptr) {
            inOrden(raiz->izq, accion);
            accion(raiz->dato);
            inOrden(raiz->der, accion);
        }
    }

public:
    ArbolAVL() : raiz(nullptr) {}

    void insertar(T clave, std::function<int(T, T)> comparador) {
        raiz = insertar(raiz, clave, comparador);
    }

    void recorrerInOrden(std::function<void(T)> accion) {
        inOrden(raiz, accion);
    }
};