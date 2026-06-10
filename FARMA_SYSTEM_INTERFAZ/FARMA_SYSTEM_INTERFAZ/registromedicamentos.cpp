#include "registromedicamentos.h"
#include "ui_registromedicamentos.h"

#include "medicamentogenerico.h"
#include "medicamentocontrolado.h"
#include "medicamentomarca.h"

#include <QDebug>
#include <QString>
#include <QMessageBox>


registromedicamentos::registromedicamentos(FarmaSystem::ListaMedicamentos* listaCompartida, FarmaSystem::ListaProveedores* listaProv, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registromedicamentos)
{
    ui->setupUi(this);

    this->miLista = listaCompartida;
    this->losProveedores = listaProv;


    cargarProveedoresEnComboBox();
}

registromedicamentos::~registromedicamentos()
{
    delete ui;
}

void registromedicamentos::cargarProveedoresEnComboBox()
{
    ui->cmbProveedor->clear();

    if (losProveedores == nullptr || losProveedores->getPrimero() == nullptr) {
        ui->cmbProveedor->addItem("No hay proveedores registrados", -1);
        return;
    }


    FarmaSystem::NodoProveedor* aux = losProveedores->getPrimero();
    while (aux != nullptr) {
        FarmaSystem::Proveedor* p = aux->getProveedor();

        if (p != nullptr) {

            QString textoVisible = QString::number(p->getId()) + " - " + QString::fromStdString(p->getNombre());


            ui->cmbProveedor->addItem(textoVisible, p->getId());
        }
        aux = aux->getSiguiente();
    }
}

void registromedicamentos::on_btnIrInventario_clicked()
{
    if (this->parentWidget()) {
        this->parentWidget()->show();
    }

    this->close();
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


    if (ui->txtNombre->text().isEmpty() || ui->txtPrecio->text().isEmpty() || ui->spnStock->text().isEmpty()) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Campos Vacíos");
        msgBox.setText("Por favor, rellene todos los espacios antes de guardar.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet("QLabel, QPushButton { color: black; }");
        msgBox.exec();
        return;
    }


    QMessageBox msgConfirmar(this);
    msgConfirmar.setWindowTitle("Confirmar Registro");
    msgConfirmar.setText("¿Está seguro de que desea registrar este medicamento en FarmaSystem?");
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


    FarmaSystem::Medicamento* nuevoMed = nullptr;
    int opcionSeleccionada = ui->cmbCategoria->currentIndex();

    if (opcionSeleccionada == 0) { // Genérico
        std::string principioActivo = "No especificado";
        nuevoMed = new FarmaSystem::MedicamentoGenerico(principioActivo, id, nombre, precio, stock, receta, idProveedor);
    }
    else if (opcionSeleccionada == 1) { // Controlado
        int nivelControl = 1;
        std::string dosisMaxima = "No especificada";
        nuevoMed = new FarmaSystem::MedicamentoControlado(nivelControl, dosisMaxima, receta, nombre, precio, stock, id, idProveedor);
    }
    else if (opcionSeleccionada == 2) { // De Marca
        std::string paisOrigen = "No especificado";
        bool enPromocion = ui->chkEnPromocion->isChecked();
        nuevoMed = new FarmaSystem::MedicamentoMarca(paisOrigen, enPromocion, id, precio, stock, nombre, receta, idProveedor);
    }


    if (miLista == nullptr) {
        QMessageBox msgError(this);
        msgError.setWindowTitle("Error de Sistema");
        msgError.setText("Error: 'miLista' es nullptr. El pasamanos de objetos falló.");
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
        miLista->agregar(nuevoMed);

        QMessageBox msgExito(this);
        msgExito.setWindowTitle("Éxito");
        msgExito.setText("¡Medicamento registrado con éxito en el sistema!");
        msgExito.setIcon(QMessageBox::Information);
        msgExito.setStyleSheet("QLabel, QPushButton { color: black; }");
        msgExito.exec();


        on_btnLimpiar_clicked();
    }
}

void registromedicamentos::on_btnLimpiar_clicked()
{

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
