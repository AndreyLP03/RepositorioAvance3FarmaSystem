#pragma once
#include "Medicamento.h"
#include "MedicamentoGenerico.h"

namespace FarmaSystem {
	class MedicamentoMarca : public Medicamento
	{
	private:
		std::string paisOrigen;
		bool enPromocion;
	public:

		MedicamentoMarca(std::string paisOrigen, bool enPromocion, int id, double precio, int stock, std::string nombre, bool receta, int IdProveedor);
		~MedicamentoMarca() override;



		std::string getCategoria() const override;

		double calcularPrecioFinal(int cantidad) const override;

		std::string getAdvertencia() const override;


	};
}
