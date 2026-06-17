#include "MedicamentoGenerico.h"
#include "Medicamento.h"
#include<string>
namespace FarmaSystem {



	MedicamentoGenerico::MedicamentoGenerico(std::string principioActivo, int id, std::string nombre, double precio, int stock, bool receta,int IdProveedor) : Medicamento(id, nombre, precio, stock, receta, IdProveedor), principioActivo(principioActivo) {}


	MedicamentoGenerico::~MedicamentoGenerico() {}


	std::string MedicamentoGenerico::getCategoria() const {

		return "Generico";
	}

	double MedicamentoGenerico::calcularPrecioFinal(int cantidad) const {
		double subtotal = precio * cantidad;
		double descuento = subtotal * 10 / 100;
		double precioFinal = subtotal - descuento;

		return precioFinal;
	}

	std::string MedicamentoGenerico::getAdvertencia() const {

		std::string advertencia = "Principio activo: "+ principioActivo + "\n" "Los Medicamentos Genericos,conservan  el mismo principio activo que los de marca \n "
			"Estos son los Genericos por lo que se les aplica un 10% de descuento\n";


		return advertencia;

	}
}