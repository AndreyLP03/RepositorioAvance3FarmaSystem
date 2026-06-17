#ifndef SISTEMAFARMACIA_H
#define SISTEMAFARMACIA_H

#include <string>
#include "Medicamento.h"
#include "Cliente.h"
#include "venta.h"


#include "listamedicamentos.h"
#include "ListaClientes.h"
#include "ListaVentas.h"
#include "ListaProveedores.h"

namespace FarmaSystem {

class SistemaFarmacia {
private:

    ListaProveedores listaProveedores;
    ListaMedicamentos listaMeds;
    ListaClientes listaClientes;
    ListaCircularVentas listaVentas;

    int idV;

public:
    SistemaFarmacia();
    ~SistemaFarmacia();


    ListaMedicamentos& getListaMedicamentos() { return listaMeds; }
    ListaCircularVentas& getListaVentas() { return listaVentas; }
    ListaClientes& getListaClientes() { return listaClientes; }
    ListaProveedores& getListaProveedores() { return listaProveedores; }


    bool realizarVenta(
        int idCliente,
        int idMedicamento,
        int cantidad,
        std::string fecha
        );


    Cliente* buscarCliente(int id);
    bool eliminarCliente(int id);
    void registrarCliente(Cliente* nuevoCliente);
    int getCantClientes() const;
    std::string listarClientes() const;
    bool fidelidad(int id);


    std::string listarMedicamentos() const;
    Medicamento* buscarMedicamento(int id);
    bool eliminarMedicamento(int id);
    int getCantidadMedicamentos() const;
    void registrarMedicamento(Medicamento* nuevoMeds);
    bool actualizarStock(int id, int cambio);
};

}

#endif