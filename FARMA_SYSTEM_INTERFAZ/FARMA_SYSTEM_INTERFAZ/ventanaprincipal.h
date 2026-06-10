#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H
#include "ListaProveedores.h"
#include "inventariomedicamentos.h"
#include "ventas.h"
#include "ventanaclientes.h"
#include "paneldeestadisticas.h"

#include <QMainWindow>

namespace FarmaSystem {
class ListaMedicamentos;
}


QT_BEGIN_NAMESPACE
namespace Ui {
class VentanaPrincipal;
}
QT_END_NAMESPACE

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal() override;

private slots:
    void on_btnGestionClient_clicked();

    void on_btnGestionMedi_clicked();

    void on_btnVenta_clicked();

    void on_btnPanelEstadisticas_clicked();

    void on_btnModuloProveedores_clicked();

private:
    Ui::VentanaPrincipal *ui;

    FarmaSystem::ListaMedicamentos* miLista;
    FarmaSystem::ListaClientes* miListaClientes;
    FarmaSystem::ListaProveedores* miListaProveedores;
    FarmaSystem::ListaCircularVentas* miListaVentas;


    InventarioMedicamentos *ventanaInventario;
    Ventas *ventanaVentas;
    VentanaClientes *ventanaGestionClientes;
    PaneldeEstadisticas* ventanaEstadisticas;

};
#endif // VENTANAPRINCIPAL_H
