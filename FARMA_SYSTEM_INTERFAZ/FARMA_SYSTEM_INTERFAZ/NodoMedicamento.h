#pragma once

#include "Medicamento.h"

#include <string>

namespace FarmaSystem {
	struct NodoMedicamento
	{
	

		Medicamento* meds;
		NodoMedicamento* siguienteMed;


		NodoMedicamento(Medicamento* medicamento);
			


	};

}