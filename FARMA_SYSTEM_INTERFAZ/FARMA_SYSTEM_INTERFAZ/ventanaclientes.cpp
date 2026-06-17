#include "ventanaclientes.h"
#include "ui_cliente.h"
#include "SistemaFarmacia.h"
#include <QMessageBox>

VentanaClientes::VentanaClientes(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cliente)
    , sistema(sistemaCentral)
{
    ui->setupUi(this);

    ui->tablaClientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablaClientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablaClientes->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->txtBuscar, &QLineEdit::textChanged, this, &VentanaClientes::on_txtBuscar_textChanged);

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

    if (sistema->getListaClientes().buscarPorCedula(cedula) != nullptr) {
        QMessageBox::critical(this, "Error", "Ya existe un cliente registrado con esa cédula.");
        return;
    }

    FarmaSystem::Cliente* nuevoCliente = new FarmaSystem::Cliente(id, nombre, cedula);
    nuevoCliente->setFidelidad(fidelidad);

    if (sistema != nullptr) {
        sistema->registrarCliente(nuevoCliente);
        QMessageBox::information(this, "Éxito", "Cliente registrado correctamente.");
        actualizarTabla();
        on_btnLimpiar_clicked();
    } else {
        QMessageBox::critical(this, "Error", "Error crítico: El sistema de farmacia no está inicializado.");
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
    std::string nuevaCedula = ui->txtCedula->text().trimmed().toStdString();
    std::string nuevoNombre = ui->txtNombre->text().trimmed().toStdString();

    if (nuevaCedula.empty() || nuevoNombre.empty()) {
        QMessageBox::warning(this, "Campos Vacíos", "El nombre y la cédula no pueden quedar vacíos.");
        return;
    }

    if (sistema->getListaClientes().editar(cedulaOriginal, nuevoNombre, nuevaCedula)) {
        FarmaSystem::Cliente* c = sistema->getListaClientes().buscarPorCedula(nuevaCedula);
        if (c != nullptr) {
            c->setFidelidad(ui->chkFidelidad->isChecked());
        }

        QMessageBox::information(this, "Éxito", "Datos del cliente actualizados correctamente desde los campos superiores.");
        actualizarTabla();
        on_btnLimpiar_clicked();
    } else {
        QMessageBox::warning(this, "Error", "Ocurrió un problema al intentar actualizar el cliente.");
    }
}

void VentanaClientes::on_btnEliminar_clicked()
{
    int fila = ui->tablaClientes->currentRow();
    if (fila < 0) {
        QMessageBox::warning(this, "Atención", "Seleccione directamente en la tabla al cliente que desea eliminar.");
        return;
    }

    std::string cedula = ui->tablaClientes->item(fila, 1)->text().toStdString();

    QMessageBox::StandardButton respuesta = QMessageBox::question(this, "Confirmar",
                                                                  "¿Está seguro de eliminar de forma permanente a este cliente?", QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        if (sistema->getListaClientes().eliminar(cedula)) {
            QMessageBox::information(this, "Eliminado", "Cliente removido del sistema.");
            actualizarTabla();
            on_btnLimpiar_clicked();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo eliminar al cliente seleccionado.");
        }
    }
}

void VentanaClientes::on_tablaClientes_cellClicked(int row, int column)
{
    Q_UNUSED(column);
    QString cedula = ui->tablaClientes->item(row, 1)->text();
    FarmaSystem::Cliente* c = sistema->getListaClientes().buscarPorCedula(cedula.toStdString());

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
    std::string filtro = arg1.trimmed().toStdString();
    ui->tablaClientes->setRowCount(0);

    if (sistema == nullptr) return;

    int total = sistema->getCantClientes();
    for (int i = 0; i < total; i++) {
        FarmaSystem::Cliente* c = sistema->getListaClientes().obtener(i);

        if (c != nullptr) {
            std::string nombre = c->getNombre();
            std::string cedula = c->getCedula();
            std::string idStr = std::to_string(c->getID());

            if (!filtro.empty()) {
                if (nombre.find(filtro) == std::string::npos && cedula.find(filtro) == std::string::npos && idStr != filtro) {
                    continue;
                }
            }

            int fila = ui->tablaClientes->rowCount();
            ui->tablaClientes->insertRow(fila);
            ui->tablaClientes->setItem(fila, 0, new QTableWidgetItem(QString::number(c->getID())));
            ui->tablaClientes->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString(c->getCedula())));
            ui->tablaClientes->setItem(fila, 2, new QTableWidgetItem(QString::fromStdString(c->getNombre())));
            ui->tablaClientes->setItem(fila, 3, new QTableWidgetItem(c->getFidelidad() ? "Sí" : "No"));
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
    ui->tablaClientes->clearSelection();
    ui->tablaClientes->setCurrentCell(-1, -1);
}

void VentanaClientes::actualizarTabla()
{
    on_txtBuscar_textChanged(ui->txtBuscar->text());
}