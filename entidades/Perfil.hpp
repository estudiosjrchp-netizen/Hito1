#pragma once
#include <string>

class Perfil {
private:
    std::string idUsuario;
    std::string biografia;
    std::string pais;
    int seguidores;

public:
    Perfil() : seguidores(0) {}
    Perfil(std::string _idUsuario, std::string _bio, std::string _pais)
        : idUsuario(_idUsuario), biografia(_bio), pais(_pais), seguidores(0) {}

    std::string getIdUsuario() const { return idUsuario; }
    std::string getBiografia() const { return biografia; }
    std::string getPais() const { return pais; }
    int getSeguidores() const { return seguidores; }
    
    void agregarSeguidor() { seguidores++; }
};