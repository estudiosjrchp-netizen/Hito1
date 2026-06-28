#pragma once
#include <string>

class Cancion {
private:
    std::string idCancion;
    std::string titulo;
    int duracionSegundos;
    std::string idArtista; // Relación con Artista
    std::string idAlbum;   // Relación con Album

public:
    Cancion() {}
    Cancion(std::string _id, std::string _titulo, int _duracion, std::string _idArtista, std::string _idAlbum)
        : idCancion(_id), titulo(_titulo), duracionSegundos(_duracion), idArtista(_idArtista), idAlbum(_idAlbum) {}

    std::string getId() const { return idCancion; }
    std::string getTitulo() const { return titulo; }
    int getDuracion() const { return duracionSegundos; }
    std::string getIdArtista() const { return idArtista; }
    std::string getIdAlbum() const { return idAlbum; }
};