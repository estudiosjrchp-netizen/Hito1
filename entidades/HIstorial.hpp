#pragma once
#include <string>

class HIstorial {
private:
    std::string idUsuario;
    std::string idCancion;
    std::string fechaReproduccion; // Formato YYYY-MM-DD
    int segundosEscuchados;

public:
    HIstorial() : segundosEscuchados(0) {}
    HIstorial(std::string _idUsuario, std::string _idCancion, std::string _fecha, int _segundos)
        : idUsuario(_idUsuario), idCancion(_idCancion), fechaReproduccion(_fecha), segundosEscuchados(_segundos) {}

    std::string getIdUsuario() const { return idUsuario; }
    std::string getIdCancion() const { return idCancion; }
    std::string getFecha() const { return fechaReproduccion; }
    int getSegundos() const { return segundosEscuchados; }
};