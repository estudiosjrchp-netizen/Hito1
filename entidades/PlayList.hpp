#pragma once
#include <string>

class PlayList {
private:
    std::string idPlaylist;
    std::string nombre;
    std::string idUsuarioPropietario; // Relación con el creador
    int cantidadCanciones;
    bool esPublica;

public:
    PlayList() : cantidadCanciones(0), esPublica(false) {}
    PlayList(std::string _id, std::string _nombre, std::string _idUsuario, bool _esPublica)
        : idPlaylist(_id), nombre(_nombre), idUsuarioPropietario(_idUsuario), cantidadCanciones(0), esPublica(_esPublica) {}

    std::string getId() const { return idPlaylist; }
    std::string getNombre() const { return nombre; }
    std::string getIdUsuario() const { return idUsuarioPropietario; }
    bool getEsPublica() const { return esPublica; }
    
    void incrementarCanciones() { cantidadCanciones++; }
};