#pragma once
#include "Medicamento.h"
#include "Cliente.h"
#include "venta.h"
#include "ListaMedicamentos.h"
#include "ListaClientes.h"
#include "ListaVentas.h"
#include "ListaProveedores.h"
namespace FarmaSystem {

	class SistemaFarmacia {
	private:

		ListaMedicamentos listaMeds;
		ListaClientes listaClientes;
		ListaCircularVentas listaVentas;
		ListaProveedores listaProveedores;
		int idV;

	public:
		SistemaFarmacia();

		~SistemaFarmacia();

		//VENTAS
		bool realizarVenta(
			int idCliente,
			int idMedicamento,
			int cantidad,
			std::string fecha
		);



		//METODOS DE CLIENTES
		Cliente* buscarCliente(int id);
		bool eliminarCliente(int id);
		void registrarCliente(Cliente* nuevoCliente);  
		int getCantClientes() const;   
		std::string listarClientes() const;
		bool fidelidad(int id);



		//METODOS DE MEDICAMENTOS
		std::string listarMedicamentos() const;
		Medicamento* buscarMedicamento(int id); 
		bool eliminarMedicamento(int id); 
		int getCantidadMedicamentos() const;
		void registrarMedicamento(Medicamento* nuevoMeds);  
		bool actualizarStock(int id, int cambiar); 






	};

}