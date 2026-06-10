#pragma once

#include <string>

namespace FarmaSystem {

	class Proveedor {

	private:

		int id;

		std::string nombre;
		std::string telefono;
		std::string email;
		std::string pais;

	public:

		Proveedor(int id,
			std::string nombre,
			std::string telefono,
			std::string email,
			std::string pais);

		~Proveedor();

		int getId() const;

		std::string getNombre() const;
		std::string getTelefono() const;
		std::string getEmail() const;
		std::string getPais() const;

		void setNombre(std::string nombre);
		void setTelefono(std::string telefono);
		void setEmail(std::string email);
		void setPais(std::string pais);

	};
}