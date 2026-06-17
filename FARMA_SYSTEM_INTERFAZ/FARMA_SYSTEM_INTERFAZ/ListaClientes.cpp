#include "ListaClientes.h"

namespace FarmaSystem {
	ListaClientes::ListaClientes() {

		primero = nullptr;
		ultimo = nullptr;

		contador = 0;
	}
	ListaClientes::~ListaClientes() {

		limpiar();
	}

	void ListaClientes::agregar(Cliente* cliente) {

		NodoCliente* nuevo = new NodoCliente(cliente);

		if (primero == nullptr) {
			primero = nuevo;
			ultimo = nuevo;
		}
		else {

			ultimo->siguiente = nuevo;

			nuevo->anterior = ultimo;

			ultimo = nuevo;
		}
		contador++;
	}
	int ListaClientes::cantidad() const {

		return contador;
	}
	NodoCliente* ListaClientes::getPrimero() const {

		return primero;
	}

	NodoCliente* ListaClientes::getUltimo() const {

		return ultimo;
	}
	Cliente* ListaClientes::buscarPorCedula(std::string Cedula)const {

		NodoCliente* actual = primero;

		while (actual != nullptr) {

			if (actual->dato->getCedula() == Cedula) {

				return actual->dato;
			}
			actual = actual->siguiente;
		}
		return nullptr;
	}

	Cliente* ListaClientes::obtener(int indice) const {

		if (indice < 0 || indice >= contador) {

			return nullptr;
		}

		NodoCliente* actual = primero;

		int posicion = 0;

		while (actual != nullptr) {

			if (posicion == indice) {

				return actual->dato;
			}

			actual = actual->siguiente;

			posicion++;
		}

		return nullptr;
	}

	bool ListaClientes::eliminar(std::string cedula) {

		NodoCliente* actual = primero;

		while (actual != nullptr) {

			if (actual->dato->getCedula() == cedula) {

				
				if (actual == primero) {

					primero = actual->siguiente;

					if (primero != nullptr) {

						primero->anterior = nullptr;
					}
				}

				
				if (actual == ultimo) {

					ultimo = actual->anterior;

					if (ultimo != nullptr) {

						ultimo->siguiente = nullptr;
					}
				}

				
				if (actual->anterior != nullptr) {

					actual->anterior->siguiente = actual->siguiente;
				}

				
				if (actual->siguiente != nullptr) {

					actual->siguiente->anterior = actual->anterior;
				}

				delete actual->dato;
				delete actual;

				contador--;

				
				if (contador == 0) {

					primero = nullptr;
					ultimo = nullptr;
				}

				return true;
			}

			actual = actual->siguiente;
		}

		return false;
	}
	bool ListaClientes::editar(std::string cedulaBuscada,
		std::string nuevoNombre,
		std::string nuevaCedula) {

		Cliente* cliente = buscarPorCedula(cedulaBuscada);

		if (cliente == nullptr) {

			return false;
		}

		cliente->setNombre(nuevoNombre);

		cliente->setCedula(nuevaCedula);

		return true;
	}

	void ListaClientes::limpiar() {

		NodoCliente* actual = primero;

		while (actual != nullptr) {

			NodoCliente* siguiente = actual->siguiente;

			delete actual->dato;
			delete actual;

			actual = siguiente;
		}

		primero = nullptr;
		ultimo = nullptr;

		contador = 0;
	}
}