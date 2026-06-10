#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include "ListaMedicamentos.h"
#include "ventanaclientes.h"
#include "ventanaproveedores.h"
#include "ListaProveedores.h"
#include "paneldeestadisticas.h"



VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)


{
    ui->setupUi(this);
    miLista = new FarmaSystem::ListaMedicamentos();
    miListaClientes = new FarmaSystem::ListaClientes();
    miListaProveedores = new FarmaSystem::ListaProveedores();
    this->miListaVentas = new FarmaSystem::ListaCircularVentas();

    this->centralWidget()->setStyleSheet(
        "QWidget#centralwidget {"
        "   border-image: url(:/n/fondofarmacia.png) 0 0 0 0 stretch stretch;"
        "}"
        );

}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::on_btnGestionClient_clicked()
{

    ventanaGestionClientes = new VentanaClientes(this->miListaClientes, this);
    ventanaGestionClientes->setAttribute(Qt::WA_DeleteOnClose);
    ventanaGestionClientes->show();

}


void VentanaPrincipal::on_btnGestionMedi_clicked()
{
    ventanaInventario = new InventarioMedicamentos(this->miLista,this->miListaProveedores);
    ventanaInventario->show();
}


void VentanaPrincipal::on_btnVenta_clicked()
{
    ventanaVentas = new Ventas(this->miLista, this->miListaClientes, this->miListaVentas, this);
    ventanaVentas->show();
}

void VentanaPrincipal::on_btnPanelEstadisticas_clicked()
{

    FarmaSystem::ListaCircularVentas* listaAUsar = this->miListaVentas;

    ventanaEstadisticas = new PaneldeEstadisticas(this->miLista, miListaVentas, this);
    ventanaEstadisticas->exec();
}

void VentanaPrincipal::on_btnModuloProveedores_clicked()
{
    ventanaProveedores *ventanaProv = new ventanaProveedores(this->miListaProveedores, this->miLista, this);


    ventanaProv->setAttribute(Qt::WA_DeleteOnClose);

    ventanaProv->show();

}

