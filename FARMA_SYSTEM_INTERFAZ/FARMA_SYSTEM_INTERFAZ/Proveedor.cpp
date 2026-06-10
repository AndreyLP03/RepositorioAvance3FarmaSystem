#include "Proveedor.h"


namespace FarmaSystem {

	Proveedor::Proveedor(int id,
		std::string nombre,
		std::string telefono,
		std::string email,
		std::string pais) {

		this->id = id;

		this->nombre = nombre;
		this->telefono = telefono;
		this->email = email;
		this->pais = pais;
	}

	Proveedor::~Proveedor() {}

	int Proveedor::getId() const {

		return id;
	}

	std::string Proveedor::getNombre() const {

		return nombre;
	}

	std::string Proveedor::getTelefono() const {

		return telefono;
	}

	std::string Proveedor::getEmail() const {

		return email;
	}

	std::string Proveedor::getPais() const {

		return pais;
	}

	void Proveedor::setNombre(std::string nombre) {

		this->nombre = nombre;
	}

	void Proveedor::setTelefono(std::string telefono) {

		this->telefono = telefono;
	}

	

	void Proveedor::setEmail(std::string email) {
		this->email = email;
	}

	void Proveedor::setPais(std::string pais) {
		this->pais = pais;
	}










}
