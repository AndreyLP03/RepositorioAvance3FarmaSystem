#pragma once

#include "NodoProveedor.h"
#include <string>

namespace FarmaSystem {

	class ListaProveedores {

	private:

		NodoProveedor* primero;
		NodoProveedor* ultimo;

		int contador;

	public:

		ListaProveedores();
		~ListaProveedores();

		void agregar(Proveedor* proveedor);

		Proveedor* obtener(int indice) const;

		Proveedor* buscarPorId(int id) const;

		Proveedor* buscarPorNombre(std::string nombre) const;

		bool eliminar(int id);

		bool editar(int id,
			std::string nuevoNombre,
			std::string nuevoTelefono);

        bool guardarEnArchivo(const std::string& nombreArchivo) const;
        bool cargarDesdeArchivo(const std::string& nombreArchivo);

		int cantidad() const;

		void limpiar();

		NodoProveedor* getPrimero() const;
		NodoProveedor* getUltimo() const;
	};

}