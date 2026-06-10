#pragma once

#include "venta.h"
namespace FarmaSystem {


	class NodoVenta
	{

    private:
        Venta* venta;
        NodoVenta* siguiente;

    public:
        NodoVenta(Venta* v);
        ~NodoVenta();

        Venta* getVenta() const;
        NodoVenta* getSiguiente() const;
        void setSiguiente(NodoVenta* sig);

	};

}