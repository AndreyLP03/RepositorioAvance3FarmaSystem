#pragma once
#include <string>
#include<sstream>
namespace FarmaSystem {

	class Medicamento {
	protected:
		int id;
		std::string nombre;
		double precio;
		int stock;
		bool receta;
		int IdProveedor;
		std::string categoria;



	public:
		Medicamento(int id, std::string nombre, double precio, int stock, bool receta,int IdProveedor, std::string categoria = "");
		virtual ~Medicamento();


		//metodos virtuales

		virtual std::string getCategoria() const = 0;
		virtual double calcularPrecioFinal(int cantidad) const = 0;
		virtual std::string getAdvertencia() const = 0;
		virtual std::string lineaTexto() const = 0;

		//metodos no virtuales

	    int getId() const;
		std::string getNombre() const;
		double getPrecio() const;
		int getStock() const;
		bool getReceta() const;
		int getIdPROVEEDOR() const;

		void setStock(int stock);
		void setNombre(std::string n);
		void setPrecio(double p);
		void setIdPROVEEDOR(int prov);
		void setCategoria(std::string catego) ;

		std::string mostrar() const;



	};

}