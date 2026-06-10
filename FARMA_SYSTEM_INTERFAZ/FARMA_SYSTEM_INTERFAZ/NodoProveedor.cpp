#include "NodoProveedor.h"

namespace FarmaSystem {

	NodoProveedor::NodoProveedor(Proveedor* proveedor) {

		dato = proveedor;

		siguiente = nullptr;
		anterior = nullptr;
	}



	Proveedor* NodoProveedor::getProveedor() const {
		return this->dato;
	}


	NodoProveedor* NodoProveedor::getSiguiente() const {
		return this->siguiente;
	}










}
