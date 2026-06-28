#pragma once
#include <string>

class Letra {
private:
    std::string idLetra;
    std::string idCancion;
    std::string contenido;
    std::string idioma;

public:
    Letra() {}
    Letra(std::string _id, std::string _idCancion, std::string _contenido, std::string _idioma)
        : idLetra(_id), idCancion(_idCancion), contenido(_contenido), idioma(_idioma) {}

    std::string getId() const { return idLetra; }
    std::string getIdCancion() const { return idCancion; }
    std::string getContenido() const { return contenido; }
    std::string getIdioma() const { return idioma; }
};