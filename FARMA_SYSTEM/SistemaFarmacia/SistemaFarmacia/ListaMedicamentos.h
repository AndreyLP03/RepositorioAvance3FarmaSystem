#pragma once

#include <string>


namespace FarmaSystem {
	class Medicamento;
	struct NodoMedicamento;


	class ListaMedicamentos
	{
	private:

		NodoMedicamento* primero;
		int contador;

	public:

		ListaMedicamentos();
		~ListaMedicamentos();

		//funciones

		void agregar(Medicamento* medicamento);
		Medicamento* obtener(int indice) const;
		Medicamento* buscarPorId(int id) const;

		//demas funciones
		Medicamento* buscarPorNombre(std::string texto) const;
		bool Eliminar(int id) ;
		int cantidad() const;
		bool limpiar() ;

		bool actualizarStockPorId(int id, int nuevoStock) ;


		//metodos para el manejo de Archivos

		bool guardarEnArchivo(const std::string& nombreArchivo) const;
		bool cargarDesdeArchivo(const std::string& nombreArchivo);




	};
}
