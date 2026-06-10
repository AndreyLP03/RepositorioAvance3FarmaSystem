#pragma once
#include "Medicamento.h"
#include "Cliente.h"
#include "venta.h"

namespace FarmaSystem {

	class SistemaFarmacia {
	private:
		Medicamento** meds;
		Cliente** clientes;

		int cantM, capM;
		int cantC, capC;

		int idM, idC;

		Venta** ventas;
		int cantV, capV;
		int idV;

		void redimensionarVentas();
		void redimensionarMedicamentos(); 
		void redimensionarClientes(); 
		

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
		Cliente** getClientes() const;  
		int getCantClientes() const;   
		std::string listarClientes() const;
		bool fidelidad(int id);



		//METODOS DE MEDICAMENTOS
		std::string listarMedicamentos() const;
		Medicamento* buscarMedicamento(int id); 
		bool eliminarMedicamento(int id); 
		Medicamento** getMedicamentos() const; 
		int getCantidadMedicamentos() const;
		void registrarMedicamento(Medicamento* nuevoMeds);  
		bool actualizarStock(int id, int cambiar); 
	};

}