#include "ventanaclientes.h"
#include "ui_cliente.h"
#include <QMessageBox>

VentanaClientes::VentanaClientes(FarmaSystem::ListaClientes* listaInyectada, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cliente)
    , miListaClientes(listaInyectada)
{
    ui->setupUi(this);
    actualizarTabla();
}

VentanaClientes::~VentanaClientes()
{
    delete ui;
}


void VentanaClientes::on_btnGuardar_clicked()
{
    if (ui->txtID_2->text().isEmpty() || ui->txtNombre->text().isEmpty() || ui->txtCedula->text().isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor complete todos los campos obligatorios.");
        return;
    }

    int id = ui->txtID_2->text().toInt();
    std::string nombre = ui->txtNombre->text().toStdString();
    std::string cedula = ui->txtCedula->text().toStdString();
    bool fidelidad = ui->chkFidelidad->isChecked();

    if (miListaClientes->buscarPorCedula(cedula) != nullptr) {
        QMessageBox::critical(this, "Error", "Ya existe un cliente registrado con esa cédula.");
        return;
    }

    FarmaSystem::Cliente* nuevoCliente = new FarmaSystem::Cliente(id, nombre, cedula);
    nuevoCliente->setFidelidad(fidelidad);

    if (miListaClientes != nullptr) {
        miListaClientes->agregar(nuevoCliente);
        QMessageBox::information(this, "Éxito", "Cliente registrado correctamente.");
        actualizarTabla();
        on_btnLimpiar_clicked();
    } else {
        QMessageBox::critical(this, "Error", "Error crítico: Lista de clientes no inicializada.");
    }
}

void VentanaClientes::on_btnActualizar_clicked()
{


    int fila = ui->tablaClientes->currentRow();
    if (fila < 0) {
        QMessageBox::warning(this, "Atención", "Seleccione un cliente en la tabla primero para actualizarlo.");
        return;
    }


    std::string cedulaOriginal = ui->tablaClientes->item(fila, 1)->text().toStdString();


    std::string nuevaCedula = ui->txtCedula->text().toStdString();
    std::string nuevoNombre = ui->txtNombre->text().toStdString();


    if (nuevaCedula.empty() || nuevoNombre.empty()) {
        QMessageBox::warning(this, "Campos Vacíos", "El nombre y la cédula no pueden quedar vacíos.");
        return;
    }


    if (miListaClientes->editar(cedulaOriginal, nuevoNombre, nuevaCedula)) {


        FarmaSystem::Cliente* c = miListaClientes->buscarPorCedula(nuevaCedula);
        if (c != nullptr) {
            c->setFidelidad(ui->chkFidelidad->isChecked());
        }

        QMessageBox::information(this, "Éxito", "Datos del cliente actualizados correctamente.");
        actualizarTabla();
        on_btnLimpiar_clicked();
    } else {
        QMessageBox::warning(this, "Error", "Ocurrió un problema al intentar actualizar el cliente.");
    }


}

void VentanaClientes::on_btnEliminar_clicked()
{
    std::string cedula = ui->txtCedula->text().toStdString();

    if (cedula.empty()) {
        QMessageBox::warning(this, "Atención", "Ingrese la cédula del cliente que desea eliminar.");
        return;
    }

    QMessageBox::StandardButton respuesta = QMessageBox::question(this, "Confirmar", "¿Está seguro de eliminar a este cliente?",
                                                                  QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        if (miListaClientes->eliminar(cedula)) {
            QMessageBox::information(this, "Eliminado", "Cliente removido del sistema.");
            actualizarTabla();
            on_btnLimpiar_clicked();
        } else {
            QMessageBox::warning(this, "Error", "No se encontró el cliente con la cédula especificada.");
        }
    }
}




void VentanaClientes::on_tablaClientes_cellClicked(int row, int column)
{

    QString cedula = ui->tablaClientes->item(row, 1)->text();
    FarmaSystem::Cliente* c = miListaClientes->buscarPorCedula(cedula.toStdString());

    if (c != nullptr) {
        ui->txtID_2->setText(QString::number(c->getID()));
        ui->txtCedula->setText(QString::fromStdString(c->getCedula()));
        ui->txtNombre->setText(QString::fromStdString(c->getNombre()));
        ui->chkFidelidad->setChecked(c->getFidelidad());

        ui->txtID_2->setEnabled(false);
    }
}



void VentanaClientes::on_txtBuscar_textChanged(const QString &arg1)
{

    QString textoBuscado = arg1.toLower();

    ui->tablaClientes->setRowCount(0);

    int total = miListaClientes->cantidad();
    for (int i = 0; i < total; i++) {
        FarmaSystem::Cliente* c = miListaClientes->obtener(i);
        if (c != nullptr) {

            QString nombre = QString::fromStdString(c->getNombre()).toLower();
            QString cedula = QString::fromStdString(c->getCedula());
            QString id = QString::number(c->getID());


            if (nombre.contains(textoBuscado) || cedula.contains(textoBuscado) || id.contains(textoBuscado)) {

                int fila = ui->tablaClientes->rowCount();
                ui->tablaClientes->insertRow(fila);

                ui->tablaClientes->setItem(fila, 0, new QTableWidgetItem(id));
                ui->tablaClientes->setItem(fila, 1, new QTableWidgetItem(cedula));
                ui->tablaClientes->setItem(fila, 2, new QTableWidgetItem(QString::fromStdString(c->getNombre())));
                ui->tablaClientes->setItem(fila, 3, new QTableWidgetItem(c->getFidelidad() ? "Sí" : "No"));
            }
        }
    }


















}

void VentanaClientes::on_btnLimpiar_clicked()
{
    ui->txtID_2->clear();
    ui->txtNombre->clear();
    ui->txtCedula->clear();
    ui->chkFidelidad->setChecked(false);
    ui->txtID_2->setEnabled(true);
    actualizarTabla();
}

void VentanaClientes::actualizarTabla()
{
    ui->tablaClientes->setRowCount(0);
    int total = miListaClientes->cantidad();
    for (int i = 0; i < total; i++) {
        FarmaSystem::Cliente* c = miListaClientes->obtener(i);
        if (c != nullptr) {
            int fila = ui->tablaClientes->rowCount();
            ui->tablaClientes->insertRow(fila);
            ui->tablaClientes->setItem(fila, 0, new QTableWidgetItem(QString::number(c->getID())));
            ui->tablaClientes->setItem(fila, 2, new QTableWidgetItem(QString::fromStdString(c->getNombre())));
            ui->tablaClientes->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString(c->getCedula())));
            ui->tablaClientes->setItem(fila, 3, new QTableWidgetItem(c->getFidelidad() ? "Sí" : "No"));
        }
    }
}