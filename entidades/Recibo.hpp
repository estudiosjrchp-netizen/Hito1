#pragma once
#include <string>

class Recibo {
private:
    std::string idRecibo;
    std::string idUsuario;
    double montoPagado;
    std::string fechaPago;

public:
    Recibo() : montoPagado(0.0) {}
    Recibo(std::string _id, std::string _idUsuario, double _monto, std::string _fecha)
        : idRecibo(_id), idUsuario(_idUsuario), montoPagado(_monto), fechaPago(_fecha) {}

    std::string getId() const { return idRecibo; }
    std::string getIdUsuario() const { return idUsuario; }
    double getMonto() const { return montoPagado; }
    std::string getFecha() const { return fechaPago; }
};