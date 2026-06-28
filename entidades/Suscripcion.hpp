#pragma once
#include <string>

class Suscripcion {
private:
    std::string idSuscripcion;
    std::string tipoPlan; // "Free", "Premium Individual", "Premium Duo"
    double precioMensual;
    bool activa;

public:
    Suscripcion() : activa(false) {}
    Suscripcion(std::string _id, std::string _tipo, double _precio)
        : idSuscripcion(_id), tipoPlan(_tipo), precioMensual(_precio), activa(true) {}

    std::string getId() const { return idSuscripcion; }
    std::string getTipoPlan() const { return tipoPlan; }
    double getPrecio() const { return precioMensual; }
    bool isActiva() const { return activa; }
    
    void cancelarSuscripcion() { activa = false; }
};