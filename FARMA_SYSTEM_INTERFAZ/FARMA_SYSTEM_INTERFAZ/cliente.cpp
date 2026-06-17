#include "Cliente.h"

namespace FarmaSystem {

	Cliente::Cliente(int id, std::string nombre, std::string cedula) {

		this->id = id;

		this->nombre = nombre;

		this->cedula = cedula;

		this->fidelidad = false;
	}

	Cliente::~Cliente() {}

	int Cliente::getID() const { return id; }

	std::string Cliente::getNombre() const { return nombre; }

	std::string Cliente::getCedula() const { return cedula; }

	bool Cliente::getFidelidad() const { return fidelidad; }

	void Cliente::setFidelidad(bool estado) {
		fidelidad = estado;
	}



	void Cliente::setNombre(std::string nuevoNombre) { 
		nombre = nuevoNombre; 
	}
	void Cliente::setCedula(std::string nuevaCedula) { 
		cedula = nuevaCedula; 
	}














	std::string Cliente::mostrar() const {

		return "ID: " + std::to_string(id) +
			" | Nombre: " + nombre +
			" | Cedula: " + cedula +
			" | Fidelidad: " + (fidelidad ? "Activa" : "Inactiva");
	}
}