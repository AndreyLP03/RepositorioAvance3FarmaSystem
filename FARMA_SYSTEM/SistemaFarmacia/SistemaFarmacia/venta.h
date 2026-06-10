
#ifndef VENTA_H
#define VENTA_H

#include <string>
#include "Medicamento.h"

namespace FarmaSystem {

    class Venta {
    private:
        int id;
        int idCliente;
        Medicamento* medicamento;
        int cantidad;
        double precioUnitario;
        double precioFinal;
        std::string fecha;

    public:
        Venta(int id, int idCliente, Medicamento* medicamento, int cantidad, std::string fecha);
        ~Venta();

        void calcularTotal();

        // getters
        int getId() const;
        int getIdCliente() const;
        std::string getNombreMedicamento() const;
        int getCantidad() const;
        double getPrecioUnitario() const;
        double getPrecioFinal() const;
        std::string getFecha() const;
        Medicamento* getMedicamento() const;


    };

}

#endif