#pragma once
#include <string>

namespace FarmaSystem {

	class Cliente {


	private:

		int id;

		std::string nombre;
		std::string cedula;
		bool fidelidad;

	public:

		Cliente(int id, std::string nombre, std::string cedula);
		~Cliente();

		int getID() const;
		std::string getNombre() const;
		std::string getCedula() const;
		bool getFidelidad() const;

		void setFidelidad(bool estado);
		void setNombre(std::string nuevoNombre);
		void setCedula(std::string nuevaCedula);

		std::string mostrar() const;
	};

}