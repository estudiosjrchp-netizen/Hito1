#pragma once
#include <string>

class Genero {
private:
    std::string idGenero;
    std::string nombre;
    std::string descripcion;

public:
    Genero() {}
    Genero(std::string _id, std::string _nombre, std::string _descripcion)
        : idGenero(_id), nombre(_nombre), descripcion(_descripcion) {}

    std::string getId() const { return idGenero; }
    std::string getNombre() const { return nombre; }
    std::string getDescripcion() const { return descripcion; }
};