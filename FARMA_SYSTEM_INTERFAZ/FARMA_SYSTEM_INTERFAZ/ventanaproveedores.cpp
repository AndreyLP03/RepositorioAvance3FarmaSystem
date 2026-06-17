#include "ventanaproveedores.h"
#include "ui_ventanaproveedores.h"

#include "Proveedor.h"
#include "Medicamento.h"
#include "SistemaFarmacia.h"


ventanaProveedores::ventanaProveedores(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ventanaProveedores)
{
    ui->setupUi(this);


    this->sistema = sistemaCentral;

    ui->tablaProveedores->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablaProveedores->setSelectionBehavior(QAbstractItemView::SelectRows);

    actualizarTabla();
}

ventanaProveedores::~ventanaProveedores()
{
    delete ui;
}

void ventanaProveedores::limpiarCampos()
{
    ui->txtId->clear();
    ui->txtNombre->clear();
    ui->txtTelefono->clear();
    ui->txtEmail->clear();
    ui->txtPais->clear();

    ui->txtId->setEnabled(true);
    ui->txtId->setFocus();
}

void ventanaProveedores::actualizarTabla(const std::string& filtro)
{
    ui->tablaProveedores->setRowCount(0);


    FarmaSystem::NodoProveedor* aux = sistema->getListaProveedores().getPrimero();
    int fila = 0;

    while(aux != nullptr) {
        FarmaSystem::Proveedor* p = aux->getProveedor();

        if (p != nullptr) {
            std::string idStr = std::to_string(p->getId());
            std::string nombre = p->getNombre();

            if (filtro.empty() || idStr.find(filtro) != std::string::npos || nombre.find(filtro) != std::string::npos) {
                ui->tablaProveedores->insertRow(fila);

                ui->tablaProveedores->setItem(fila, 0, new QTableWidgetItem(QString::number(p->getId())));
                ui->tablaProveedores->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString(p->getNombre())));
                ui->tablaProveedores->setItem(fila, 2, new QTableWidgetItem(QString::fromStdString(p->getTelefono())));
                ui->tablaProveedores->setItem(fila, 3, new QTableWidgetItem(QString::fromStdString(p->getEmail())));
                ui->tablaProveedores->setItem(fila, 4, new QTableWidgetItem(QString::fromStdString(p->getPais())));
                fila++;
            }
        }
        aux = aux->getSiguiente();
    }
}

void ventanaProveedores::on_btnGuardar_clicked()
{
    std::string idStr = ui->txtId->text().toStdString();
    std::string nombre = ui->txtNombre->text().toStdString();
    std::string telefono = ui->txtTelefono->text().toStdString();
    std::string email = ui->txtEmail->text().toStdString();
    std::string pais = ui->txtPais->text().toStdString();

    if(idStr.empty() || nombre.empty()) {
        QMessageBox msgVacios(this);
        msgVacios.setWindowTitle("Campos Vacíos");
        msgVacios.setText("El ID y el Nombre son obligatorios.");
        msgVacios.setIcon(QMessageBox::Warning);
        msgVacios.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
        msgVacios.exec();
        return;
    }

    int id;
    try {
        id = std::stoi(idStr);
    } catch (...) {
        QMessageBox msgTipo(this);
        msgTipo.setWindowTitle("Error de Tipo");
        msgTipo.setText("El ID debe ser un número entero válido.");
        msgTipo.setIcon(QMessageBox::Warning);
        msgTipo.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
        msgTipo.exec();
        return;
    }


    if(sistema->getListaProveedores().buscarPorId(id) != nullptr) {
        QMessageBox msgExiste(this);
        msgExiste.setWindowTitle("Error");
        msgExiste.setText("Ya existe un proveedor registrado con ese ID.");
        msgExiste.setIcon(QMessageBox::Critical);
        msgExiste.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
        msgExiste.exec();
        return;
    }

    FarmaSystem::Proveedor* nuevo = new FarmaSystem::Proveedor(id, nombre, telefono, email, pais);


    sistema->getListaProveedores().agregar(nuevo);

    QMessageBox msgExito(this);
    msgExito.setWindowTitle("Éxito");
    msgExito.setText("Proveedor registrado correctamente.");
    msgExito.setIcon(QMessageBox::Information);
    msgExito.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
    msgExito.exec();

    actualizarTabla();
    limpiarCampos();
}

void ventanaProveedores::on_btnActualizar_clicked()
{
    std::string idStr = ui->txtId->text().toStdString();
    std::string nombre = ui->txtNombre->text().toStdString();
    std::string telefono = ui->txtTelefono->text().toStdString();
    std::string email = ui->txtEmail->text().toStdString();
    std::string pais = ui->txtPais->text().toStdString();

    if(idStr.empty()) {
        QMessageBox msg(this);
        msg.setWindowTitle("Selección Vacía");
        msg.setText("Por favor, seleccione un proveedor de la tabla para editar.");
        msg.setIcon(QMessageBox::Warning);
        msg.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
        msg.exec();
        return;
    }

    int id = std::stoi(idStr);


    FarmaSystem::Proveedor* prov = sistema->getListaProveedores().buscarPorId(id);

    if(prov != nullptr) {
        prov->setNombre(nombre);
        prov->setTelefono(telefono);
        prov->setEmail(email);
        prov->setPais(pais);

        QMessageBox msg(this);
        msg.setWindowTitle("Éxito");
        msg.setText("Proveedor actualizado completamente en el sistema.");
        msg.setIcon(QMessageBox::Information);
        msg.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
        msg.exec();

        actualizarTabla();
        limpiarCampos();
    } else {
        QMessageBox msg(this);
        msg.setWindowTitle("Error");
        msg.setText("No se encontró el proveedor en la base de datos.");
        msg.setIcon(QMessageBox::Critical);
        msg.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
        msg.exec();
    }
}

void ventanaProveedores::on_btnEliminar_clicked()
{
    std::string idStr = ui->txtId->text().toStdString();

    if(idStr.empty()) {
        QMessageBox msg(this);
        msg.setWindowTitle("Selección Vacía");
        msg.setText("Seleccione un proveedor de la tabla para eliminar.");
        msg.setIcon(QMessageBox::Warning);
        msg.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
        msg.exec();
        return;
    }

    int id = std::stoi(idStr);


    bool tieneMedicamentosAsociados = false;
    int totalMedicamentos = sistema->getListaMedicamentos().cantidad();

    for (int i = 0; i < totalMedicamentos; ++i) {

        FarmaSystem::Medicamento* med = sistema->getListaMedicamentos().obtener(i);

        if (med != nullptr && med->getIdPROVEEDOR() == id) {
            tieneMedicamentosAsociados = true;
            break;
        }
    }

    if(tieneMedicamentosAsociados) {
        QMessageBox msg(this);
        msg.setWindowTitle("Restricción de Integridad");
        msg.setText("No se puede eliminar el proveedor porque tiene medicamentos registrados a su nombre.");
        msg.setIcon(QMessageBox::Critical);
        msg.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
        msg.exec();
        return;
    }

    QMessageBox msgConfirm(this);
    msgConfirm.setWindowTitle("Confirmar Eliminación");
    msgConfirm.setText("¿Está seguro de que desea eliminar este proveedor?");
    msgConfirm.setIcon(QMessageBox::Question);
    msgConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgConfirm.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");

    int respuesta = msgConfirm.exec();

    if(respuesta == QMessageBox::Yes) {

        if(sistema->getListaProveedores().eliminar(id)) {
            QMessageBox msgExito(this);
            msgExito.setWindowTitle("Éxito");
            msgExito.setText("Proveedor eliminado correctamente.");
            msgExito.setIcon(QMessageBox::Information);
            msgExito.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
            msgExito.exec();

            actualizarTabla();
            limpiarCampos();
        } else {
            QMessageBox msgError(this);
            msgError.setWindowTitle("Error");
            msgError.setText("No se pudo eliminar el proveedor.");
            msgError.setIcon(QMessageBox::Critical);
            msgError.setStyleSheet("QLabel { color: black; } QPushButton { color: black; }");
            msgError.exec();
        }
    }
}

void ventanaProveedores::on_btnLimpiar_clicked()
{
    limpiarCampos();
}

void ventanaProveedores::on_txtBuscar_textChanged(const QString &arg1)
{
    actualizarTabla(arg1.toStdString());
}

void ventanaProveedores::on_tablaProveedores_itemClicked(QTableWidgetItem *item)
{
    int filaSeleccionada = item->row();

    ui->txtId->setText(ui->tablaProveedores->item(filaSeleccionada, 0)->text());
    ui->txtNombre->setText(ui->tablaProveedores->item(filaSeleccionada, 1)->text());
    ui->txtTelefono->setText(ui->tablaProveedores->item(filaSeleccionada, 2)->text());
    ui->txtEmail->setText(ui->tablaProveedores->item(filaSeleccionada, 3)->text());
    ui->txtPais->setText(ui->tablaProveedores->item(filaSeleccionada, 4)->text());

    ui->txtId->setEnabled(false);
}