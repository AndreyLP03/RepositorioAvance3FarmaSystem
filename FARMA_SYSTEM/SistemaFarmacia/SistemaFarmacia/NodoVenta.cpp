#include "NodoVenta.h"



namespace FarmaSystem {

    NodoVenta::NodoVenta(Venta* v) {
        this->venta = v;
        this->siguiente = nullptr;
    }

    NodoVenta::~NodoVenta() {
        delete venta; 
    }

    Venta* NodoVenta::getVenta() const {
        return this->venta;
    }

    NodoVenta* NodoVenta::getSiguiente() const {
        return this->siguiente;
    }

    void NodoVenta::setSiguiente(NodoVenta* sig) {
        this->siguiente = sig;
    }
}
