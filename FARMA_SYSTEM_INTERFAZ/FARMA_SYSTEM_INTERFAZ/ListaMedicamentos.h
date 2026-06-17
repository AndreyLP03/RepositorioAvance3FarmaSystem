#pragma once
#include "NodoMedicamento.h"
#include <string>

using namespace std;

namespace FarmaSystem {
	class ListaMedicamentos
	{
	private:

		NodoMedicamento* primero;
		int contador;

	public:

		ListaMedicamentos();
		~ListaMedicamentos();



        void agregar(Medicamento* medicamento);
		Medicamento* obtener(int indice) const;
		Medicamento* buscarPorId(int id) const;


		Medicamento* buscarPorNombre(string texto) const;
		bool Eliminar(int id) ;
		int cantidad() const;
		bool limpiar() ;

		bool actualizarStockPorId(int id, int nuevoStock) ;

        bool guardarEnArchivo(const std::string& nombreArchivo) const;
        bool cargarDesdeArchivo(const std::string& nombreArchivo);

    NodoMedicamento* getPrimero() const { return primero; }

	};
}
