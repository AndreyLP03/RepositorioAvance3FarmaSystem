#pragma once

#include "NodoVenta.h"


    namespace FarmaSystem {

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
        };





};

