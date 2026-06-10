#include "ListaProveedores.h"

namespace FarmaSystem {

	ListaProveedores::ListaProveedores() {

		primero = nullptr;
		ultimo = nullptr;

		contador = 0;
	}

	ListaProveedores::~ListaProveedores() {

		limpiar();
	}

	void ListaProveedores::agregar(Proveedor* proveedor) {

		NodoProveedor* nuevo = new NodoProveedor(proveedor);

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

	Proveedor* ListaProveedores::obtener(int indice) const {

		if (indice < 0 || indice >= contador) {

			return nullptr;
		}

		NodoProveedor* actual = primero;

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

	Proveedor* ListaProveedores::buscarPorId(int id) const {

		NodoProveedor* actual = primero;

		while (actual != nullptr) {

			if (actual->dato->getId() == id) {

				return actual->dato;
			}

			actual = actual->siguiente;
		}

		return nullptr;
	}

	Proveedor* ListaProveedores::buscarPorNombre(std::string nombre) const {

		NodoProveedor* actual = primero;

		while (actual != nullptr) {

			if (actual->dato->getNombre() == nombre) {

				return actual->dato;
			}

			actual = actual->siguiente;
		}

		return nullptr;
	}

	bool ListaProveedores::eliminar(int id) {

		NodoProveedor* actual = primero;

		while (actual != nullptr) {

			if (actual->dato->getId() == id) {

				// si es el primero
				if (actual == primero) {

					primero = actual->siguiente;

					if (primero != nullptr) {

						primero->anterior = nullptr;
					}
				}

				// si es el ultimo
				if (actual == ultimo) {

					ultimo = actual->anterior;

					if (ultimo != nullptr) {

						ultimo->siguiente = nullptr;
					}
				}

				// conectar anterior con siguiente
				if (actual->anterior != nullptr) {

					actual->anterior->siguiente = actual->siguiente;
				}

				// conectar siguiente con anterior
				if (actual->siguiente != nullptr) {

					actual->siguiente->anterior = actual->anterior;
				}

				delete actual->dato;
				delete actual;

				contador--;

				// si la lista queda vacia
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

	bool ListaProveedores::editar(int id,
		std::string nuevoNombre,
		std::string nuevoTelefono) {

		Proveedor* proveedor = buscarPorId(id);

		if (proveedor == nullptr) {

			return false;
		}

		proveedor->setNombre(nuevoNombre);

		proveedor->setTelefono(nuevoTelefono);

		return true;
	}

	int ListaProveedores::cantidad() const {

		return contador;
	}

	void ListaProveedores::limpiar() {

		NodoProveedor* actual = primero;

		while (actual != nullptr) {

			NodoProveedor* siguiente = actual->siguiente;

			delete actual->dato;
			delete actual;

			actual = siguiente;
		}

		primero = nullptr;
		ultimo = nullptr;

		contador = 0;
	}

	NodoProveedor* ListaProveedores::getPrimero() const {

		return primero;
	}

	NodoProveedor* ListaProveedores::getUltimo() const {

		return ultimo;
	}

}