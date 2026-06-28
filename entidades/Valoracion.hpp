#pragma once
#include <string>

class Valoracion {
private:
    std::string idUsuario;
    std::string idCancion;
    int puntuacion; // Estrellas del 1 al 5
    std::string comentario;

public:
    Valoracion() : puntuacion(0) {}
    Valoracion(std::string _idUsuario, std::string _idCancion, int _puntos, std::string _comentario)
        : idUsuario(_idUsuario), idCancion(_idCancion), puntuacion(_puntos), comentario(_comentario) {}

    std::string getIdUsuario() const { return idUsuario; }
    std::string getIdCancion() const { return idCancion; }
    int getPuntuacion() const { return puntuacion; }
    std::string getComentario() const { return comentario; }
};