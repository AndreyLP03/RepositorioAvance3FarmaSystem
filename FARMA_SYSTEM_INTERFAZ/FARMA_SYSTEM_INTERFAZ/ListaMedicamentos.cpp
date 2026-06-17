#include "ListaMedicamentos.h"
#include "NodoMedicamento.h"
namespace FarmaSystem {

	ListaMedicamentos::ListaMedicamentos() {

		primero = nullptr;
		contador = 0;
	}


	ListaMedicamentos::~ListaMedicamentos()
	{
		limpiar(); 
	}





	void ListaMedicamentos::agregar(Medicamento* medicamento) {

		NodoMedicamento* nuevo = new NodoMedicamento(medicamento);


		if (primero == nullptr) {

			primero = nuevo;


		}
		else if (primero != nullptr) {

			NodoMedicamento* actual;

			actual = primero;

			while (actual->siguienteMed != nullptr) {

				actual = actual->siguienteMed;


			}
			actual->siguienteMed = nuevo;

		}
		contador++;
	}



	Medicamento* ListaMedicamentos::obtener(int indice) const {
		if (indice < 0 || indice >= contador) {

			return nullptr;
		}
		else {
			NodoMedicamento* actual;

			actual = primero;

			for (int i = 0; i < indice; i++) {

				actual = actual->siguienteMed;


			}

			return actual->meds;
		}

	}




	Medicamento* ListaMedicamentos::buscarPorId(int id) const {
		NodoMedicamento* actual = primero;

		while (actual != nullptr) {

			if (actual->meds != nullptr && actual->meds->getId() == id) {
				return actual->meds;

			}
			actual = actual->siguienteMed;


		}
		return nullptr;
	}


	int ListaMedicamentos::cantidad() const {


		return contador;

	}




	Medicamento* ListaMedicamentos::buscarPorNombre(string texto) const {
		NodoMedicamento* actual = primero;

		while (actual != nullptr) {


			if (actual->meds && actual->meds->getNombre() == texto) {

				return actual->meds;
			}


			actual = actual->siguienteMed;

		}



		return nullptr;


	}




	bool ListaMedicamentos::actualizarStockPorId(int id, int nuevoStock) {
			
			Medicamento* med = buscarPorId(id);

			if (med != nullptr) {
				med->setStock(nuevoStock);
				return true; 
			}

			return false; 
		}

	   


	bool ListaMedicamentos::Eliminar(int id) {
		if (primero == nullptr) {
			return false;
		}

		NodoMedicamento* actual = primero;
		NodoMedicamento* anterior = nullptr;

		
		while (actual != nullptr && actual->meds->getId() != id) {
			anterior = actual;
			actual = actual->siguienteMed;
		}

		
		if (actual == nullptr) {
			return false;
		}

		
		if (anterior == nullptr) {
			primero = primero->siguienteMed;
		}
		else {
			
			anterior->siguienteMed = actual->siguienteMed;
		}

		
		delete actual->meds;
		delete actual;

		return true;




	}


	bool ListaMedicamentos::limpiar() {

		if (primero == nullptr) {
			return true;
		}

		NodoMedicamento* actual = primero;

		
		while (actual != nullptr) {
			
			NodoMedicamento* siguienteMed = actual->siguienteMed;

			
			if (actual->meds != nullptr) {
				delete actual->meds;
			}

			
			delete actual;

			
			actual = siguienteMed;
		}

		
		primero = nullptr;

		return true; 

	}
















	}