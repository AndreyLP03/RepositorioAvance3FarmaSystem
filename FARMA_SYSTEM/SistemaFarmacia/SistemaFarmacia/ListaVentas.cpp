#include "ListaVentas.h"
#include <fstream>
#include <string>
#include "ListaMedicamentos.h"




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
    bool ListaCircularVentas::guardarEnArchivo(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) return false;


        if (primero == nullptr) {
            archivo.close();
            return true;
        }

        NodoVenta* actual = primero;
        do {
            Venta* ventas = actual->getVenta();
            if (ventas != nullptr) {

                archivo << ventas->getId() << "|"
                    << ventas->getIdCliente() << "|"
                    << ventas->getNombreMedicamento() << "|" // Guardamos el nombre para buscarlo al cargar
                    << ventas->getCantidad() << "|"
                    << ventas->getPrecioUnitario() << "|"
                    << ventas->getPrecioFinal() << "|"
                    << ventas->getFecha() << "\n";
            }
            actual = actual->getSiguiente();
        } while (actual != primero);

        archivo.close();
        return true;
    }



    bool ListaCircularVentas::cargarDesdeArchivo(const std::string& nombreArchivo, ListaMedicamentos& listaMedis) {
        std::ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) return true;

        std::string linea;
        while (std::getline(archivo, linea)) {
            if (linea.empty()) continue;

            size_t pos = 0;
            size_t sigPos;

            // ID Venta
            sigPos = linea.find('|', pos);
            if (sigPos == std::string::npos) continue;
            int id = std::stoi(linea.substr(pos, sigPos - pos));
            pos = sigPos + 1;

            // ID Cliente
            sigPos = linea.find('|', pos);
            if (sigPos == std::string::npos) continue;
            int idCliente = std::stoi(linea.substr(pos, sigPos - pos));
            pos = sigPos + 1;

            //Nombre del Medicamento
            sigPos = linea.find('|', pos);
            if (sigPos == std::string::npos) continue;
            std::string nombreMedi = linea.substr(pos, sigPos - pos);
            pos = sigPos + 1;

            //Cantidad
            sigPos = linea.find('|', pos);
            if (sigPos == std::string::npos) continue;
            int cantidad = std::stoi(linea.substr(pos, sigPos - pos));
            pos = sigPos + 1;

            // Precio
            sigPos = linea.find('|', pos);
            if (sigPos == std::string::npos) continue;
            double precioUnitario = std::stod(linea.substr(pos, sigPos - pos));
            pos = sigPos + 1;

            // Precio Final
            sigPos = linea.find('|', pos);
            if (sigPos == std::string::npos) continue;
            double precioFinal = std::stod(linea.substr(pos, sigPos - pos));
            pos = sigPos + 1;

            // Fecha
            std::string fecha = linea.substr(pos);


            // aqui se busca el medicamento en la lista que ya cargamos previamente en memoria
            Medicamento* mediAsociado = listaMedis.buscarPorNombre(nombreMedi);

            if (mediAsociado != nullptr) {
                //reconstruccion de la venta
                Venta* nuevaVenta = new Venta(id, idCliente, mediAsociado, cantidad, fecha);
                this->agregar(nuevaVenta);
            }

        }

        archivo.close();
        return true;
    }



}
