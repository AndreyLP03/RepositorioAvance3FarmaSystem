#pragma once

#include "NodoVenta.h"
#include <string>

namespace FarmaSystem {

class ListaMedicamentos;

class ListaCircularVentas {
private:
    NodoVenta* primero;
    NodoVenta* ultimo;
    int contador;

public:
    ListaCircularVentas();
    ~ListaCircularVentas();

    void agregar(Venta* nueva);
    NodoVenta* getPrimero() const;
    int getCantidad() const;

    double calcularAcumuladoTotal() const;
    double calcularAcumuladoPorCliente(int idCliente) const;
    bool guardarEnArchivo(const std::string& nombreArchivo) const;
    bool cargarDesdeArchivo(const std::string& nombreArchivo, const class ListaMedicamentos& listaMeds);
};

}