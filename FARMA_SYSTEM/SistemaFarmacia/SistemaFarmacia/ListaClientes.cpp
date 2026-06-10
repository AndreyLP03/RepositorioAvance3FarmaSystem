#include "ListaClientes.h"
#include <fstream>
#include <string>
#include<sstream>

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


	bool ListaClientes::guardarEnArchivo(const std::string& nombreArchivo) const {
		std::ofstream archivo(nombreArchivo);
		if (!archivo.is_open()) {
			return false;
		}

		for (int i = 0; i < this->contador; i++) {
			Cliente* c = this->obtener(i);
			if (c != nullptr) {
				archivo << c->getID() << "|"
					<< c->getNombre() << "|"
					<< c->getCedula() << "|"
					<< (c->getFidelidad() ? "1" : "0") << "\n";
			}
		}
		archivo.close();
		return true;
		
	}




	bool ListaClientes::cargarDesdeArchivo(const std::string& nombreArchivo) {
		std::ifstream archivo(nombreArchivo);

		if (!archivo.is_open()) return false; // Inicia vacío si no existe 

		std::string linea;
		while (std::getline(archivo, linea)) {
			if (linea.empty()) continue;

			std::stringstream ss(linea);
			std::string token;

			int id;
			std::string nombre, cedula;
			bool fidelidad;

			std::getline(ss, token, '|'); id = std::stoi(token);
			std::getline(ss, nombre, '|');
			std::getline(ss, cedula, '|');
			std::getline(ss, token, '|'); fidelidad = (std::stoi(token) == 1);

			Cliente* nuevoCliente = new Cliente(id, nombre, cedula);
			nuevoCliente->setFidelidad(fidelidad);

			this->agregar(nuevoCliente);
		}
		archivo.close();
		return true;
	}
















	}


