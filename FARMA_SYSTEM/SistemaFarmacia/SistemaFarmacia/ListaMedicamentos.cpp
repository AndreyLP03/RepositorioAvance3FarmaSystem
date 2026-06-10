#include "ListaMedicamentos.h"
#include "NodoMedicamento.h"

#include <fstream>
#include<string>

#include "MedicamentoGenerico.h"
#include "MedicamentoMarca.h"
#include "MedicamentoControlado.h"

using namespace std;



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



	bool ListaMedicamentos::guardarEnArchivo(const std::string& nombreArchivo) const {
		std::ofstream archivo(nombreArchivo);
		if (!archivo.is_open()) return false;

		int total = this->cantidad();
		for (int i = 0; i < this->contador; i++) {
			Medicamento* med = this->obtener(i);
			if (med != nullptr) {
				archivo << med->lineaTexto() << "\n"; 
			}
		}
		archivo.close();
		return true;

	}



	bool ListaMedicamentos::cargarDesdeArchivo(const std::string& nombreArchivo) {
		std::ifstream archivo(nombreArchivo);

		if (!archivo.is_open()) return false; // Inicia vacío si no existe 

		std::string linea;
		while (std::getline(archivo, linea)) {
			if (linea.empty()) continue;

			std::stringstream ss(linea);
			std::string tipo, token;

			std::getline(ss, tipo, '|');

			// Extraemos los 6 campos comunes
			int id, stock, idProveedor;
			std::string nombre;
			double precio;
			bool receta;

			std::getline(ss, token, '|'); id = std::stoi(token);
			std::getline(ss, nombre, '|');
			std::getline(ss, token, '|'); precio = std::stod(token);
			std::getline(ss, token, '|'); stock = std::stoi(token);
			std::getline(ss, token, '|'); receta = (std::stoi(token) == 1);
			std::getline(ss, token, '|'); idProveedor = std::stoi(token);

			if (tipo == "Generico") {
				std::string principioActivo;
				std::getline(ss, principioActivo, '|');
				this->agregar(new MedicamentoGenerico(principioActivo, id, nombre, precio, stock, receta, idProveedor));
			}
			else if (tipo == "Controlado") {
				int nivelControl;
				std::string dosisMaxima;
				std::getline(ss, token, '|'); nivelControl = std::stoi(token);
				std::getline(ss, dosisMaxima, '|');
				this->agregar(new MedicamentoControlado(nivelControl, dosisMaxima, receta, nombre, precio, stock, id, idProveedor));
			}
			else if (tipo == "Marca") {
				std::string paisOrigen;
				bool enPromocion;
				std::getline(ss, paisOrigen, '|');
				std::getline(ss, token, '|'); enPromocion = (std::stoi(token) == 1);
				this->agregar(new MedicamentoMarca(paisOrigen, enPromocion, id, precio, stock, nombre, receta, idProveedor));
			}
		}
		archivo.close();
		return true;
		


	}





	}

