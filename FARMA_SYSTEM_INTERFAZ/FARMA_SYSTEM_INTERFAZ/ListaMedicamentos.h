#pragma once
#include "NodoMedicamento.h"
#include <string>

using namespace std;

namespace FarmaSystem {
class ListaMedicamentos
{
private:

    NodoMedicamento* primero;
    int contador;

public:

    ListaMedicamentos();
    ~ListaMedicamentos();

    //funciones

    void agregar(Medicamento* medicamento);
    Medicamento* obtener(int indice) const;
    Medicamento* buscarPorId(int id) const;

    //demas funciones
    Medicamento* buscarPorNombre(string texto) const;
    bool Eliminar(int id) ;
    int cantidad() const;
    bool limpiar() ;

    bool actualizarStockPorId(int id, int nuevoStock) ;

    NodoMedicamento* getPrimero() const { return primero; }

};
}