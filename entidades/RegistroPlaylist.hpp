#pragma once
#include <string>

class RegistroPlaylist {
private:
    std::string idPlaylist;
    std::string idCancion;
    std::string fechaAgregada;
    int posicionOrden;

public:
    RegistroPlaylist() : posicionOrden(0) {}
    RegistroPlaylist(std::string _idPlaylist, std::string _idCancion, std::string _fecha, int _orden)
        : idPlaylist(_idPlaylist), idCancion(_idCancion), fechaAgregada(_fecha), posicionOrden(_orden) {}

    std::string getIdPlaylist() const { return idPlaylist; }
    std::string getIdCancion() const { return idCancion; }
    std::string getFecha() const { return fechaAgregada; }
    int getOrden() const { return posicionOrden; }
};