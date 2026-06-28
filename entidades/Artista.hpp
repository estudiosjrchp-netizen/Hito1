#pragma once
#include <string>

class Artista {
private:
    std::string idArtista;
    std::string nombre;
    std::string generoPrincipal;
    int oyentesMensuales;

public:
    Artista() : oyentesMensuales(0) {}
    Artista(std::string _id, std::string _nombre, std::string _genero, int _oyentes)
        : idArtista(_id), nombre(_nombre), generoPrincipal(_genero), oyentesMensuales(_oyentes) {}

    std::string getId() const { return idArtista; }
    std::string getNombre() const { return nombre; }
    std::string getGenero() const { return generoPrincipal; }
    int getOyentes() const { return oyentesMensuales; }
};