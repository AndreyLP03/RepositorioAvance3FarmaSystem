#ifndef VENTAS_H
#define VENTAS_H

#include <QDialog>
#include "SistemaFarmacia.h"


namespace FarmaSystem {
class SistemaFarmacia;
class NodoVenta;
}

namespace Ui {
class Ventas;
}

class Ventas : public QDialog
{
    Q_OBJECT

public:

    explicit Ventas(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent = nullptr);
    ~Ventas();

private slots:
    void on_btnVerificar_clicked();
    void on_btnFacturar_clicked();
    void on_btnLimpiar_clicked();
    void on_btnSiguienteVenta_clicked();
    void on_btnAnteriorVenta_clicked();
    void on_btnFiltrar_clicked();
    void on_btnLimpiarFiltro_clicked();

private:
    Ui::Ventas *ui;


    FarmaSystem::SistemaFarmacia* sistema;


    void actualizarTablaHistorial(int filtroClienteId = -1);


    FarmaSystem::NodoVenta* nodoExplorador;
    void mostrarVentaEnExplorador();
};

#endif