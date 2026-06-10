#pragma once
#include<string>
#include<sstream>
#include "Medicamento.h"

namespace FarmaSystem {
	class MedicamentoGenerico : public Medicamento
	{
	private:
		std::string principioActivo;

	public:

		MedicamentoGenerico(std::string principioActivo, int id, std::string nombre, double precio, int stock, bool receta, int IdProveedor);
		~MedicamentoGenerico() override;


		std::string getCategoria() const override;

		double calcularPrecioFinal(int cantidad) const override;

		std::string getAdvertencia() const override;

		std::string lineaTexto() const override;

	};
}

