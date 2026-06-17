#include "registromedicamentos.h"
#include "ui_registromedicamentos.h"

#include "medicamentogenerico.h"
#include "medicamentocontrolado.h"
#include "medicamentomarca.h"
#include "SistemaFarmacia.h"

#include <QDebug>
#include <QString>
#include <QMessageBox>

registromedicamentos::registromedicamentos(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent, int idEditar)
    : QDialog(parent)
    , ui(new Ui::registromedicamentos)
{
    ui->setupUi(this);
    this->sistema = sistemaCentral;
    this->idMedicamentoEdicion = idEditar;

    cargarProveedoresEnComboBox();

    if (this->idMedicamentoEdicion != -1) {
        this->setWindowTitle("Editar Medicamento");
        cargarDatosMedicamento();
    } else {
        this->setWindowTitle("Registrar Nuevo Medicamento");
    }
}

registromedicamentos::~registromedicamentos()
{
    delete ui;
}

void registromedicamentos::cargarProveedoresEnComboBox()
{
    ui->cmbProveedor->clear();

    if (sistema == nullptr || sistema->getListaProveedores().getPrimero() == nullptr) {
        ui->cmbProveedor->addItem("No hay proveedores registrados", -1);
        return;
    }

    FarmaSystem::NodoProveedor* aux = sistema->getListaProveedores().getPrimero();
    while (aux != nullptr) {
        FarmaSystem::Proveedor* p = aux->getProveedor();

        if (p != nullptr) {
            QString textoVisible = QString::number(p->getId()) + " - " + QString::fromStdString(p->getNombre());
            ui->cmbProveedor->addItem(textoVisible, p->getId());
        }
        aux = aux->getSiguiente();
    }
}

void registromedicamentos::cargarDatosMedicamento()
{
    if (sistema == nullptr) return;

    FarmaSystem::Medicamento* med = sistema->buscarMedicamento(idMedicamentoEdicion);
    if (med != nullptr) {
        ui->txtId->setText(QString::number(med->getId()));
        ui->txtId->setEnabled(false);
        ui->txtNombre->setText(QString::fromStdString(med->getNombre()));
        ui->txtPrecio->setText(QString::number(med->getPrecio(), 'f', 2));
        ui->spnStock->setValue(med->getStock());

        if (ui->cmbProveedor->count() > 0) {
            ui->cmbProveedor->setCurrentIndex(0);
        }

        if (dynamic_cast<FarmaSystem::MedicamentoGenerico*>(med)) {
            ui->cmbCategoria->setCurrentIndex(0);
        } else if (dynamic_cast<FarmaSystem::MedicamentoControlado*>(med)) {
            ui->cmbCategoria->setCurrentIndex(1);
        } else if (dynamic_cast<FarmaSystem::MedicamentoMarca*>(med)) {
            ui->cmbCategoria->setCurrentIndex(2);
        }
        ui->cmbCategoria->setEnabled(false);
    }
}

void registromedicamentos::on_btnIrInventario_clicked()
{
    this->reject();
}

void registromedicamentos::on_btnGuardar_clicked()
{
    bool idValido = false;
    int id = ui->txtId->text().toInt(&idValido);

    if (!idValido) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Error de Formato");
        msgBox.setText("El 'ID' del medicamento debe contener únicamente números (sin letras ni espacios).");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStyleSheet("QLabel, QPushButton { color: black; }");
        msgBox.exec();
        return;
    }

    if (idMedicamentoEdicion == -1 && sistema != nullptr && sistema->buscarMedicamento(id) != nullptr) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("ID Duplicado");
        msgBox.setText("Ya existe un medicamento registrado con este ID único. Ingrese un código diferente.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet("QLabel, QPushButton { color: black; }");
        msgBox.exec();
        return;
    }

    int idProveedor = ui->cmbProveedor->currentData().toInt();
    if (idProveedor == -1 || ui->cmbProveedor->currentIndex() == -1) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Proveedor Inválido");
        msgBox.setText("Debe seleccionar un proveedor válido de la lista desplegable.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStyleSheet("QLabel, QPushButton { color: black; }");
        msgBox.exec();
        return;
    }

    if (ui->txtNombre->text().isEmpty() || ui->txtPrecio->text().isEmpty()) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Campos Vacíos");
        msgBox.setText("Por favor, rellene todos los espacios antes de guardar.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet("QLabel, QPushButton { color: black; }");
        msgBox.exec();
        return;
    }

    QMessageBox msgConfirmar(this);
    msgConfirmar.setWindowTitle(idMedicamentoEdicion != -1 ? "Confirmar Edición" : "Confirmar Registro");
    msgConfirmar.setText(idMedicamentoEdicion != -1 ? "¿Está seguro de que desea guardar los cambios en este medicamento?" : "¿Está seguro de que desea registrar este medicamento en FarmaSystem?");
    msgConfirmar.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgConfirmar.setIcon(QMessageBox::Question);
    msgConfirmar.setStyleSheet("QLabel, QPushButton { color: black; }");

    int respuesta = msgConfirmar.exec();
    if (respuesta == QMessageBox::No) {
        return;
    }

    std::string nombre = ui->txtNombre->text().toStdString();
    double precio = ui->txtPrecio->text().toDouble();
    int stock = ui->spnStock->text().toInt();
    bool receta = false;

    if (idMedicamentoEdicion != -1) {
        FarmaSystem::Medicamento* med = sistema->buscarMedicamento(idMedicamentoEdicion);
        if (med != nullptr) {
            med->setNombre(nombre);
            med->setPrecio(precio);
            med->setStock(stock);

            QMessageBox msgExito(this);
            msgExito.setWindowTitle("Éxito");
            msgExito.setText("¡Medicamento modificado con éxito!");
            msgExito.setIcon(QMessageBox::Information);
            msgExito.setStyleSheet("QLabel, QPushButton { color: black; }");
            msgExito.exec();

            this->accept();
            return;
        }
    }

    FarmaSystem::Medicamento* nuevoMed = nullptr;
    int opcionSeleccionada = ui->cmbCategoria->currentIndex();

    if (opcionSeleccionada == 0) {
        std::string principioActivo = "No especificado";
        nuevoMed = new FarmaSystem::MedicamentoGenerico(principioActivo, id, nombre, precio, stock, receta, idProveedor);
    }
    else if (opcionSeleccionada == 1) {
        int nivelControl = 1;
        std::string dosisMaxima = "No especificada";
        receta = true;
        nuevoMed = new FarmaSystem::MedicamentoControlado(nivelControl, dosisMaxima, receta, nombre, precio, stock, id, idProveedor);
    }
    else if (opcionSeleccionada == 2) {
        std::string paisOrigen = "No especificado";
        bool enPromocion = ui->chkEnPromocion->isChecked();
        nuevoMed = new FarmaSystem::MedicamentoMarca(paisOrigen, enPromocion, id, precio, stock, nombre, receta, idProveedor);
    }

    if (sistema == nullptr) {
        QMessageBox msgError(this);
        msgError.setWindowTitle("Error de Sistema");
        msgError.setText("Error: 'sistema' es nullptr. El pasamanos de objetos falló.");
        msgError.setIcon(QMessageBox::Critical);
        msgError.setStyleSheet("QLabel, QPushButton { color: black; }");
        msgError.exec();
    }
    else if (nuevoMed == nullptr) {
        QMessageBox msgError(this);
        msgError.setWindowTitle("Error de Selección");
        msgError.setText("Error: El objeto medicamento no se pudo instanciar.\nVerifique los índices de las categorías en el ComboBox.");
        msgError.setIcon(QMessageBox::Critical);
        msgError.setStyleSheet("QLabel, QPushButton { color: black; }");
        msgError.exec();
    }
    else {
        sistema->registrarMedicamento(nuevoMed);

        QMessageBox msgExito(this);
        msgExito.setWindowTitle("Éxito");
        msgExito.setText("¡Medicamento registrado con éxito en el sistema!");
        msgExito.setIcon(QMessageBox::Information);
        msgExito.setStyleSheet("QLabel, QPushButton { color: black; }");
        msgExito.exec();

        on_btnLimpiar_clicked();
        this->accept();
    }
}

void registromedicamentos::on_btnLimpiar_clicked()
{
    if (idMedicamentoEdicion != -1) return;

    ui->txtId->clear();
    ui->txtNombre->clear();
    ui->txtPrecio->clear();

    if(ui->cmbProveedor->count() > 0) {
        ui->cmbProveedor->setCurrentIndex(0);
    }

    ui->spnStock->clear();
    ui->cmbCategoria->setCurrentIndex(0);
    ui->txtId->setFocus();
    ui->chkEnPromocion->setChecked(false);
}