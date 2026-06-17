#pragma once
#include "NodoCliente.h"
#include <string>

namespace FarmaSystem {

	class ListaClientes
	{
	private:
		NodoCliente* primero;
		NodoCliente* ultimo;

		int contador;
	public:
		ListaClientes();
		~ListaClientes();

		void agregar(Cliente* cliente);

		Cliente* obtener(int indice) const;
		Cliente* buscarPorCedula(std::string cedula) const;

		bool eliminar(std::string cedula);
		bool editar(std::string cedulaBuscada, std::string NuevoNombre, std::string NuevaCedula);
        bool guardarEnArchivo(const std::string& nombreArchivo) const;
        bool cargarDesdeArchivo(const std::string& nombreArchivo);

		int cantidad() const;

		void limpiar();

		NodoCliente* getPrimero() const;
		NodoCliente* getUltimo() const;
	};
}
