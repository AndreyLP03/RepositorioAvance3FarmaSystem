#include "Medicamento.h"
#include<sstream>
namespace FarmaSystem {

	Medicamento::Medicamento(int id, std::string nombre, double precio, int stock, bool receta,int IdProveedor,std::string categoria): id(id), nombre(nombre)
		, precio(precio), stock(stock), receta(receta), IdProveedor(IdProveedor), categoria(categoria) { }

	Medicamento::~Medicamento(){}
	




	int Medicamento::getId() const { return id; }

	std::string Medicamento::getNombre() const { return nombre; }

	double Medicamento::getPrecio() const { return precio; }

	int Medicamento::getStock() const { return stock; }

	bool Medicamento::getReceta() const { return receta; }

	int Medicamento::getIdPROVEEDOR() const {
		return IdProveedor;
	}








	void Medicamento::setStock(int s) {
		if (s >= 0) stock = s;
	}




	void Medicamento::setNombre(std::string n) {
		if (!n.empty()) nombre = n;
	}

	void Medicamento::setPrecio(double p) {
		if (p >= 0) precio = p;
	}

	void Medicamento::setIdPROVEEDOR(int prov) {
		if (prov > 0) IdProveedor = prov;


	}

	void Medicamento:: setCategoria(std::string catego){

		if (!catego.empty()) {
			categoria = catego;
		}

	}



	std::string Medicamento::mostrar() const {
		return "ID: " + std::to_string(id) +
			" | " + nombre +
			" | Precio: " + std::to_string(precio) +
			" | Stock: " + std::to_string(stock) +
			" | Receta: " + (receta ? "Si" : "No");
	}
}