#pragma once
# include "Cliente.h"

namespace FarmaSystem {
	
	struct NodoCliente {

		Cliente* dato;
		
		NodoCliente* siguiente;
		NodoCliente* anterior;

		NodoCliente(Cliente* cliente);
	};
}