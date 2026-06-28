#pragma once
#include <string>

class Album {
private:
    std::string idAlbum;
    std::string titulo;
    std::string idArtista; // Relación con el artista creador
    int anioLanzamiento;

public:
    Album() : anioLanzamiento(0) {}
    Album(std::string _id, std::string _titulo, std::string _idArtista, int _anio)
        : idAlbum(_id), titulo(_titulo), idArtista(_idArtista), anioLanzamiento(_anio) {}

    std::string getId() const { return idAlbum; }
    std::string getTitulo() const { return titulo; }
    std::string getIdArtista() const { return idArtista; }
    int getAnio() const { return anioLanzamiento; }
};