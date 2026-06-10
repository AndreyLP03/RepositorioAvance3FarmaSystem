#include "SistemaFarmacia.h"
#include <iostream>


using namespace std;

namespace FarmaSystem {


	SistemaFarmacia::SistemaFarmacia(){
		this->idV = 1;
	this->listaProveedores.cargarDesdeArchivo("proveedores.txt");
	this->listaMeds.cargarDesdeArchivo("medicamentos.txt");
	this->listaClientes.cargarDesdeArchivo("clientes.txt");
	this->listaVentas.cargarDesdeArchivo("ventas.txt", this->listaMeds);
 
	if (listaVentas.getCantidad() > 0) {
		
		this->idV = listaVentas.getCantidad() + 1;
	}
	 
	}


	SistemaFarmacia::~SistemaFarmacia() {
		this->listaProveedores.guardarEnArchivo("proveedores.txt");
		this->listaMeds.guardarEnArchivo("medicamentos.txt");
		this->listaClientes.guardarEnArchivo("clientes.txt");
		this->listaVentas.guardarEnArchivo("ventas.txt");
	}


	//MEDICAMENTOS

	void SistemaFarmacia::registrarMedicamento(Medicamento* nuevoMeds) {
		listaMeds.agregar(nuevoMeds);

	}



	Medicamento* SistemaFarmacia::buscarMedicamento(int id) {
		return listaMeds.buscarPorId(id);
		
	}

	std::string SistemaFarmacia::listarMedicamentos() const {
		
		if (listaMeds.cantidad() == 0) return "No hay medicamentos registrados.";

		std::string resultado = "";
		for (int i = 0; i < listaMeds.cantidad(); i++) {
			Medicamento* med = listaMeds.obtener(i);
			if (med != nullptr) {
				resultado += "----------------------\n";
				resultado += med->mostrar() + "\n";
				resultado += "Categoria    : " + med->getCategoria() + "\n";
				resultado += "Precio final : " + std::to_string(med->calcularPrecioFinal(1)) + "\n";
				resultado += "Advertencia  : " + med->getAdvertencia() + "\n";
			}
		}
		resultado += "----------------------\n";
		return resultado;

	}

	
	int SistemaFarmacia::getCantidadMedicamentos() const {
		return listaMeds.cantidad();
	}


	bool SistemaFarmacia::actualizarStock(int id, int cambio) {
		return listaMeds.actualizarStockPorId(id, cambio);
	}

	bool SistemaFarmacia::eliminarMedicamento(int id) {

		return listaMeds.Eliminar(id);


	}




	//Clientes
	void SistemaFarmacia::registrarCliente(Cliente* nuevoCliente) {

		if (listaClientes.buscarPorCedula(nuevoCliente->getCedula()) != nullptr) {
			return; 
		}
		listaClientes.agregar(nuevoCliente);


	}


	Cliente* SistemaFarmacia::buscarCliente(int id) {
		for (int i = 0; i < listaClientes.cantidad(); i++) {
			Cliente* c = listaClientes.obtener(i);
			if (c != nullptr && c->getID() == id) {
				return c;
			}
		}
		return nullptr;
		
	}


	std::string SistemaFarmacia::listarClientes() const {
		if (listaClientes.cantidad() == 0) return "No hay clientes\n";

		std::string resultado = "";
		for (int i = 0; i < listaClientes.cantidad(); i++) {
			Cliente* c = listaClientes.obtener(i);
			if (c != nullptr) {
				resultado += "----------------------\n";
				resultado += c->mostrar() + "\n";
			}
		}
		resultado += "----------------------\n";
		return resultado;
	}




	bool SistemaFarmacia::fidelidad(int id) {

		Cliente* c = buscarCliente(id);
		if (c != nullptr) {
			c->setFidelidad(!c->getFidelidad());
			return true;
		}
		return false;

	}

	bool SistemaFarmacia::eliminarCliente(int id) {
		Cliente* c = buscarCliente(id);
		if (c != nullptr) {
			return listaClientes.eliminar(c->getCedula());
		}
		return false;
	}




	int SistemaFarmacia::getCantClientes() const {
		return listaClientes.cantidad();
	}



	//VENTAS
	
	bool SistemaFarmacia::realizarVenta(int idCliente, int idMedicamento, int cantidad, std::string fecha) {
		Cliente* cliente = buscarCliente(idCliente);
		Medicamento* med = buscarMedicamento(idMedicamento);

		if (cliente == nullptr || med == nullptr) return false;
		if (cantidad > med->getStock()) return false;

		double total = med->calcularPrecioFinal(cantidad);
		if (cliente->getFidelidad()) {
			total *= 0.95;
		}

		Venta* nuevaVenta = new Venta(idV++, idCliente, med, cantidad, fecha);
		listaVentas.agregar(nuevaVenta);

		med->setStock(med->getStock() - cantidad);
		return true;
	}




}