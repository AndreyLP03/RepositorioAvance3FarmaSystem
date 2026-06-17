#include "inventariomedicamentos.h"
#include "ui_inventariomedicamentos.h"
#include "registromedicamentos.h"
#include "SistemaFarmacia.h"

#include "MedicamentoGenerico.h"
#include "MedicamentoMarca.h"
#include "MedicamentoControlado.h"

#include <QMessageBox>
#include <QString>
#include <string>

InventarioMedicamentos::InventarioMedicamentos(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InventarioMedicamentos)
{
    ui->setupUi(this);
    this->sistema = sistemaCentral;


    ui->TblInventario->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TblInventario->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TblInventario->setSelectionMode(QAbstractItemView::SingleSelection);

    actualizarTabla("");
}

InventarioMedicamentos::~InventarioMedicamentos()
{
    delete ui;
}

void InventarioMedicamentos::on_btnRegistrarNuevoMedicamento_clicked()
{
    registromedicamentos ventanaRegistro(sistema, this);
    if (ventanaRegistro.exec() == QDialog::Accepted) {
        actualizarTabla("");
    }
}

void InventarioMedicamentos::actualizarTabla(const std::string &filtroBusqueda)
{
    ui->TblInventario->setRowCount(0);
    if (sistema == nullptr) return;

    FarmaSystem::NodoMedicamento* aux = sistema->getListaMedicamentos().getPrimero();
    int fila = 0;

    while (aux != nullptr) {
        FarmaSystem::Medicamento* med = aux->meds;

        if (med != nullptr) {
            std::string nombreMed = med->getNombre();
            std::string idMed = std::to_string(med->getId());

            if (!filtroBusqueda.empty()) {
                if (nombreMed.find(filtroBusqueda) == std::string::npos && idMed != filtroBusqueda) {
                    aux = aux->siguienteMed;
                    continue;
                }
            }

            std::string tipoReal = "General";
            if (dynamic_cast<FarmaSystem::MedicamentoGenerico*>(med)) {
                tipoReal = "Generico";
            } else if (dynamic_cast<FarmaSystem::MedicamentoMarca*>(med)) {
                tipoReal = "Marca";
            } else if (dynamic_cast<FarmaSystem::MedicamentoControlado*>(med)) {
                tipoReal = "Controlado";
            } else {
                tipoReal = med->getCategoria();
            }

            ui->TblInventario->insertRow(fila);


            QTableWidgetItem *itemID = new QTableWidgetItem(QString::fromStdString(idMed));
            itemID->setFlags(itemID->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(fila, 0, itemID);

            QTableWidgetItem *itemNombre = new QTableWidgetItem(QString::fromStdString(nombreMed));
            itemNombre->setFlags(itemNombre->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(fila, 1, itemNombre);

            QTableWidgetItem *itemPrecio = new QTableWidgetItem(QString::number(med->getPrecio(), 'f', 2));
            itemPrecio->setFlags(itemPrecio->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(fila, 2, itemPrecio);

            QTableWidgetItem *itemStock = new QTableWidgetItem(QString::number(med->getStock()));
            itemStock->setFlags(itemStock->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(fila, 3, itemStock);

            QTableWidgetItem *itemTipo = new QTableWidgetItem(QString::fromStdString(tipoReal));
            itemTipo->setFlags(itemTipo->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(fila, 4, itemTipo);


            QString idProvFormateado = "Prov_" + QString::number(med->getIdPROVEEDOR()).rightJustified(2, '0');
            QTableWidgetItem *itemProv = new QTableWidgetItem(idProvFormateado);
            itemProv->setFlags(itemProv->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(fila, 5, itemProv);

            fila++;
        }
        aux = aux->siguienteMed;
    }
}

void InventarioMedicamentos::on_btnBuscar_clicked()
{
    std::string criterio = ui->txtBuscar->text().trimmed().toStdString();
    actualizarTabla(criterio);
}

void InventarioMedicamentos::on_btnEliminar_clicked()
{
    int filaSeleccionada = ui->TblInventario->currentRow();
    if (filaSeleccionada < 0) {
        QMessageBox::warning(this, "Eliminar", "Seleccione un medicamento de la tabla.");
        return;
    }

    int idEliminar = ui->TblInventario->item(filaSeleccionada, 0)->text().toInt();

    QMessageBox::StandardButton respuesta = QMessageBox::question(this, "Confirmar",
                                                                  "¿Está seguro de que desea eliminar este medicamento?", QMessageBox::Yes|QMessageBox::No);

    if (respuesta == QMessageBox::No) return;

    if (sistema->getListaMedicamentos().Eliminar(idEliminar)) {
        actualizarTabla("");
        QMessageBox::information(this, "Éxito", "Medicamento eliminado correctamente.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo eliminar el medicamento.");
    }
}

void InventarioMedicamentos::on_btnListar_clicked()
{
    ui->txtBuscar->clear();
    actualizarTabla("");
}


void InventarioMedicamentos::on_btnEditar_clicked()
{
    int filaSeleccionada = ui->TblInventario->currentRow();
    if (filaSeleccionada < 0) {
        QMessageBox::warning(this, "Editar", "Seleccione un medicamento de la tabla.");
        return;
    }

    QMessageBox::StandardButton respuesta = QMessageBox::question(this, "Confirmar Edición",
                                                                  "¿Seguro que quieres editar este medicamento?",
                                                                  QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {

        ui->TblInventario->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
        ui->TblInventario->setSelectionBehavior(QAbstractItemView::SelectItems);


        ui->TblInventario->item(filaSeleccionada, 1)->setFlags(ui->TblInventario->item(filaSeleccionada, 1)->flags() | Qt::ItemIsEditable);
        ui->TblInventario->item(filaSeleccionada, 2)->setFlags(ui->TblInventario->item(filaSeleccionada, 2)->flags() | Qt::ItemIsEditable);
        ui->TblInventario->item(filaSeleccionada, 3)->setFlags(ui->TblInventario->item(filaSeleccionada, 3)->flags() | Qt::ItemIsEditable);

        ui->TblInventario->editItem(ui->TblInventario->item(filaSeleccionada, 1));
    }
}


void InventarioMedicamentos::on_btnActualizarStock_clicked()
{
    int filaSeleccionada = ui->TblInventario->currentRow();
    if (filaSeleccionada < 0) {
        QMessageBox::warning(this, "Actualizar Datos", "Por favor, seleccione la fila que modificó antes de guardar.");
        return;
    }

    int idMedicamento = ui->TblInventario->item(filaSeleccionada, 0)->text().toInt();

    if (sistema == nullptr) return;

    FarmaSystem::Medicamento* med = sistema->buscarMedicamento(idMedicamento);

    if (med != nullptr) {
        std::string nuevoNombre = ui->TblInventario->item(filaSeleccionada, 1)->text().trimmed().toStdString();
        double nuevoPrecio = ui->TblInventario->item(filaSeleccionada, 2)->text().toDouble();
        int nuevoStock = ui->TblInventario->item(filaSeleccionada, 3)->text().toInt();


        med->setNombre(nuevoNombre);
        med->setPrecio(nuevoPrecio);
        med->setStock(nuevoStock);


        ui->TblInventario->item(filaSeleccionada, 1)->setFlags(ui->TblInventario->item(filaSeleccionada, 1)->flags() & ~Qt::ItemIsEditable);
        ui->TblInventario->item(filaSeleccionada, 2)->setFlags(ui->TblInventario->item(filaSeleccionada, 2)->flags() & ~Qt::ItemIsEditable);
        ui->TblInventario->item(filaSeleccionada, 3)->setFlags(ui->TblInventario->item(filaSeleccionada, 3)->flags() & ~Qt::ItemIsEditable);

        ui->TblInventario->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->TblInventario->setSelectionBehavior(QAbstractItemView::SelectRows);

        QMessageBox::information(this, "Éxito", "Los cambios introducidos en la fila se han actualizado y guardado correctamente.");
    } else {
        QMessageBox::critical(this, "Error", "No se encontró el medicamento en la estructura lógica del sistema.");
    }
}

void InventarioMedicamentos::on_txtBuscar_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
}

void InventarioMedicamentos::on_TblInventario_itemClicked(QTableWidgetItem *item)
{
    Q_UNUSED(item);
}