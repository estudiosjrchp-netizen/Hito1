#pragma once
#include <string>

class Anuncio {
private:
    std::string idAnuncio;
    std::string empresaSponsor;
    int duracionSegundos;

public:
    Anuncio() : duracionSegundos(0) {}
    Anuncio(std::string _id, std::string _empresa, int _duracion)
        : idAnuncio(_id), empresaSponsor(_empresa), duracionSegundos(_duracion) {}

    std::string getId() const { return idAnuncio; }
    std::string getSponsor() const { return empresaSponsor; }
    int getDuracion() const { return duracionSegundos; }
};