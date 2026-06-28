#pragma once
#include <string>

class Amigo {
private:
    std::string idUsuario1;
    std::string idUsuario2;
    std::string fechaAmistad;

public:
    Amigo() {}
    Amigo(std::string _id1, std::string _id2, std::string _fecha)
        : idUsuario1(_id1), idUsuario2(_id2), fechaAmistad(_fecha) {}

    std::string getIdUsuario1() const { return idUsuario1; }
    std::string getIdUsuario2() const { return idUsuario2; }
    std::string getFechaAmistad() const { return fechaAmistad; }
};