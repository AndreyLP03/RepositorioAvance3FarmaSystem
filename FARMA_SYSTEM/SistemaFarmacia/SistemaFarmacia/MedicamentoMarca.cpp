#include "MedicamentoMarca.h"
#include "Medicamento.h"

namespace FarmaSystem {
	MedicamentoMarca::MedicamentoMarca(std::string paisOrigen, bool enPromocion, int id, double precio, int stock, std::string nombre, bool receta, int IdProveedor) :
		Medicamento(id, nombre, precio, stock, receta,IdProveedor), paisOrigen(paisOrigen), enPromocion(enPromocion) {
	};


	MedicamentoMarca::~MedicamentoMarca() {}



	std::string MedicamentoMarca::getCategoria() const {


		return "Marca";
	}

	double MedicamentoMarca::calcularPrecioFinal(int cantidad) const {

		if (enPromocion == true) {

			double subtotal = precio * cantidad;
			double descuento = subtotal * 15 / 100;

			double precioFinal = subtotal - descuento;
			return precioFinal;

		}
		else {
			return precio * cantidad;
		}

	}

	std::string MedicamentoMarca::getAdvertencia() const {
	
		std::string advertencia = " Pais de origen : " + paisOrigen;
	   
		if (enPromocion == true) {

			advertencia = advertencia + " \n!Producto en Promocion!";
		}


		return advertencia;
	
	
	}


	std::string MedicamentoMarca::lineaTexto() const {
		return "Marca|" + std::to_string(id) + "|" + nombre + "|" + std::to_string(precio) + "|" +
			std::to_string(stock) + "|" + std::to_string(receta) + "|" + std::to_string(IdProveedor) + "|" +
			paisOrigen + "|" + std::to_string(enPromocion);
	}















}