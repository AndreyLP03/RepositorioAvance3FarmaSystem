#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include "SistemaFarmacia.h"


VentanaPrincipal::VentanaPrincipal(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

   
    this->sistema = sistemaCentral;

    this->centralWidget()->setStyleSheet(
        "QWidget#centralwidget {"
        "    border-image: url(:/n/fondofarmacia.png) 0 0 0 0 stretch stretch;"
        "}"
        );
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::on_btnGestionClient_clicked()
{

    ventanaGestionClientes = new VentanaClientes(this->sistema, this);
    ventanaGestionClientes->setAttribute(Qt::WA_DeleteOnClose);
    ventanaGestionClientes->show();
}

void VentanaPrincipal::on_btnGestionMedi_clicked()
{

    ventanaInventario = new InventarioMedicamentos(this->sistema, this);
    ventanaInventario->show();
}

void VentanaPrincipal::on_btnVenta_clicked()
{

    ventanaVentas = new Ventas(this->sistema, this);
    ventanaVentas->show();
}

void VentanaPrincipal::on_btnPanelEstadisticas_clicked()
{

    ventanaEstadisticas = new PaneldeEstadisticas(this->sistema, this);
    ventanaEstadisticas->exec();
}

void VentanaPrincipal::on_btnModuloProveedores_clicked()
{

    ventanaProv = new ventanaProveedores(this->sistema, this);
    ventanaProv->setAttribute(Qt::WA_DeleteOnClose);
    ventanaProv->show();
}