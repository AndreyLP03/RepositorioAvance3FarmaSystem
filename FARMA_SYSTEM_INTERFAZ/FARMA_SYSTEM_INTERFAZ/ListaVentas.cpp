#include "ListaVentas.h"

namespace FarmaSystem {

    ListaCircularVentas::ListaCircularVentas() {
        this->primero = nullptr;
        this->ultimo = nullptr;
        this->contador = 0;
    }

    ListaCircularVentas::~ListaCircularVentas() {
        if (primero != nullptr) {
            NodoVenta* aux = primero;
            
            ultimo->setSiguiente(nullptr);

            while (aux != nullptr) {
                NodoVenta* aBorrar = aux;
                aux = aux->getSiguiente();
                delete aBorrar;
            }
        }
    }

    void ListaCircularVentas::agregar(Venta* nueva) {
        NodoVenta* nuevoNodo = new NodoVenta(nueva);

        if (primero == nullptr) {
            primero = nuevoNodo;
            ultimo = nuevoNodo;
           
            ultimo->setSiguiente(primero);
        }
        else {
            ultimo->setSiguiente(nuevoNodo);
            ultimo = nuevoNodo;
           
            ultimo->setSiguiente(primero);
        }
        contador++;
    }

    NodoVenta* ListaCircularVentas::getPrimero() const {
        return this->primero;
    }

    int ListaCircularVentas::getCantidad() const {
        return this->contador;
    }

    double ListaCircularVentas::calcularAcumuladoTotal() const {
        if (primero == nullptr) return 0.0;

        double total = 0.0;
        NodoVenta* aux = primero;

      
        do {
            if (aux->getVenta() != nullptr) {
                total += aux->getVenta()->getPrecioFinal();
            }
            aux = aux->getSiguiente();
        } while (aux != primero);

        return total;
    }

   
    double ListaCircularVentas::calcularAcumuladoPorCliente(int idCliente) const {
        if (primero == nullptr) return 0.0;

        double total = 0.0;
        NodoVenta* aux = primero;

        do {
            if (aux->getVenta() != nullptr && aux->getVenta()->getIdCliente() == idCliente) {
                total += aux->getVenta()->getPrecioFinal();
            }
            aux = aux->getSiguiente();
        } while (aux != primero);

        return total;
    }

    }
