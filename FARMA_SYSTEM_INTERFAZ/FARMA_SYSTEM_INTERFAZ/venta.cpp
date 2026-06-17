
#include "venta.h"

namespace FarmaSystem {

	Venta::Venta(int id, int idCliente, Medicamento* medicamento, int cantidad, std::string fecha) {
		this->id = id;
		this->idCliente = idCliente;
		this->medicamento = medicamento;
		this->cantidad = cantidad;
		this->fecha = fecha;

		this->precioUnitario = medicamento->getPrecio();

		calcularTotal();
	}

	Venta::~Venta() {}

	void Venta::calcularTotal() {
		precioFinal = medicamento->calcularPrecioFinal(cantidad);
	}

	int Venta::getId() const {
		return id;
	}

	int Venta::getIdCliente() const {
		return idCliente;
	}

	std::string Venta::getNombreMedicamento() const {
		return medicamento->getNombre();
	}

	int Venta::getCantidad() const {
		return cantidad;
	}

	double Venta::getPrecioUnitario() const {
		return precioUnitario;
	}

	double Venta::getPrecioFinal() const {
		return precioFinal;
	}

	std::string Venta::getFecha() const {
		return fecha;
	}

} 