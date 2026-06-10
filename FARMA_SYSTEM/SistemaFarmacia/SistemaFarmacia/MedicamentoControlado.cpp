#include "MedicamentoControlado.h"
#include "Medicamento.h"
#include<string>

namespace FarmaSystem {
	MedicamentoControlado::MedicamentoControlado(int nivelControl, std::string dosisMaxima, bool receta, std::string nombre, double precio, int stock, int id, int IdProveedor):
   Medicamento(id,nombre,precio,stock,true,IdProveedor), nivelControl(nivelControl),dosisMaxima(dosisMaxima){ }
	                                  //true=receta en este caso

	MedicamentoControlado::~MedicamentoControlado() {}


	std::string MedicamentoControlado::getCategoria() const {




		return "Controlado";


	}

	double MedicamentoControlado::calcularPrecioFinal(int cantidad) const {
		
			double subtotal = precio * cantidad;
			double recargo = subtotal * 5 / 100;
			double total = subtotal + recargo;

			return total;
		
	}

	std::string MedicamentoControlado::getAdvertencia() const {

		std::string advertencia= "!ATENCION ! Medicamento Controlado\n" "Nivel de Control: " +std::to_string( nivelControl) + 
		" \n Dosis Maxima: " + dosisMaxima +"\n"+
		"Requiere Receta.\n"
		"Se aplica un recargo del 5%\n";
		return advertencia;
	}



	std::string MedicamentoControlado::lineaTexto() const {
		return "Controlado|" + std::to_string(id) + "|" + nombre + "|" + std::to_string(precio) + "|" +
			std::to_string(stock) + "|" + std::to_string(receta) + "|" + std::to_string(IdProveedor) + "|" +
			std::to_string(nivelControl) + "|" + dosisMaxima;
	}















}