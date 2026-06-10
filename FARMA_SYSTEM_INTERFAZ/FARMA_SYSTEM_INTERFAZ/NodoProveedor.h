#pragma once

#include "Proveedor.h"

namespace FarmaSystem {

	struct NodoProveedor {

		Proveedor* dato;

		NodoProveedor* siguiente;
		NodoProveedor* anterior;

		NodoProveedor(Proveedor* proveedor);




		Proveedor* getProveedor() const;
		NodoProveedor* getSiguiente() const;




	};

}