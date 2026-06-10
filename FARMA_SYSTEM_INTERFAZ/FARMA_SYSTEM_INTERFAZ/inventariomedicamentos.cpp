#include "inventariomedicamentos.h"
#include "ui_inventariomedicamentos.h"
#include "Medicamento.h"
#include "registromedicamentos.h"

#include <QDebug>
#include <QMessageBox>

InventarioMedicamentos::InventarioMedicamentos(FarmaSystem::ListaMedicamentos* listaCompartida,FarmaSystem::ListaProveedores* listaProv,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InventarioMedicamentos)

{
    ui->setupUi(this);
    this->miLista = listaCompartida;
    this->misProveedores = listaProv;
}

InventarioMedicamentos::~InventarioMedicamentos()
{
    delete ui;
}

void InventarioMedicamentos::on_btnRegistrarNuevoMedicamento_clicked()
{

    registromedicamentos *ventanaRegistro = new registromedicamentos(this->miLista,this->misProveedores,this);



    this->hide();
    ventanaRegistro->show();

}





void InventarioMedicamentos::on_btnListar_clicked()
{
    ui->TblInventario->blockSignals(true);
    qDebug() << "¡El botón Listar sí se está presionando!";


    ui->TblInventario->setRowCount(0);


    if (miLista == nullptr) {
        qDebug() << "ALERTA: El puntero miLista es NULL";
        return;
    }

    int totalMedicamentos = miLista->cantidad();
    qDebug() << "Cantidad de medicamentos en la lista compartida:" << totalMedicamentos;


    for (int i = 0; i < totalMedicamentos; ++i) {

        FarmaSystem::Medicamento* med = miLista->obtener(i);

        if (med != nullptr) {

            int filaNueva = ui->TblInventario->rowCount();
            ui->TblInventario->insertRow(filaNueva);


            QTableWidgetItem* itemId = new QTableWidgetItem(QString::number(med->getId()));
            itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(filaNueva, 0, itemId);


            QTableWidgetItem* itemNombre = new QTableWidgetItem(QString::fromStdString(med->getNombre()));
            itemNombre->setFlags(itemNombre->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(filaNueva, 1, itemNombre);


            QTableWidgetItem* itemPrecio = new QTableWidgetItem(QString::number(med->getPrecio(), 'f', 2));
            itemPrecio->setFlags(itemPrecio->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(filaNueva, 2, itemPrecio);


            QTableWidgetItem* itemStock = new QTableWidgetItem(QString::number(med->getStock()));
            itemStock->setFlags(itemStock->flags() | Qt::ItemIsEditable);
            ui->TblInventario->setItem(filaNueva, 3, itemStock);


            QTableWidgetItem* itemCategoria = new QTableWidgetItem(QString::fromStdString(med->getCategoria()));
            itemCategoria->setFlags(itemCategoria->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(filaNueva, 4, itemCategoria);


            QTableWidgetItem* itemProveedor = new QTableWidgetItem(QString::number(med->getIdPROVEEDOR()));
            itemProveedor->setFlags(itemProveedor->flags() & ~Qt::ItemIsEditable);
            ui->TblInventario->setItem(filaNueva, 5, itemProveedor);
        }
    }

    ui->TblInventario->blockSignals(false);

}


void InventarioMedicamentos::on_btnBuscar_clicked()
{
    ui->TblInventario->blockSignals(true);

    QString textoBusqueda = ui->txtBuscar->text().trimmed();

    if (textoBusqueda.isEmpty()) {
        QMessageBox::warning(this, "Campo Vacío", "Por favor, ingrese un ID o Nombre para buscar.");
        return;
    }


    FarmaSystem::Medicamento* medEncontrado = nullptr;
    bool esNumero = false;

    int idBuscado = textoBusqueda.toInt(&esNumero);


    if (esNumero) {

        medEncontrado = miLista->buscarPorId(idBuscado);
    } else {

        medEncontrado = miLista->buscarPorNombre(textoBusqueda.toStdString());
    }




    if (medEncontrado != nullptr) {

        ui->TblInventario->setRowCount(0);
        ui->TblInventario->insertRow(0);


        ui->TblInventario->setItem(0, 0, new QTableWidgetItem(QString::number(medEncontrado->getId())));
        ui->TblInventario->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(medEncontrado->getNombre())));
        ui->TblInventario->setItem(0, 2, new QTableWidgetItem(QString::number(medEncontrado->getPrecio(), 'f', 2)));
        ui->TblInventario->setItem(0, 3, new QTableWidgetItem(QString::number(medEncontrado->getStock())));
        ui->TblInventario->setItem(0, 4, new QTableWidgetItem(QString::fromStdString(medEncontrado->getCategoria())));
        ui->TblInventario->setItem(0, 5, new QTableWidgetItem(QString::number(medEncontrado->getIdPROVEEDOR())));

    } else {

        QMessageBox::critical(this , "ERROR !", "No se encontró ningún medicamento que coincida con la búsqueda.");
    }


  ui->TblInventario->blockSignals(false);

}


void InventarioMedicamentos::on_btnActualizarStock_clicked()
{


    int filaSeleccionada = ui->TblInventario->currentRow();

    if (filaSeleccionada < 0) {
        QMessageBox::warning(this, "Selección Requerida",
                             "Por favor, haga clic en la fila del medicamento que modificó.");
        return;
    }


    int id = ui->TblInventario->item(filaSeleccionada, 0)->text().toInt();
    int nuevoStock = ui->TblInventario->item(filaSeleccionada, 3)->text().toInt();


    if (miLista->actualizarStockPorId(id, nuevoStock)) {
        QMessageBox::information(this, "Éxito", "¡El stock ha sido actualizado!");
        on_btnListar_clicked();
    }
    else {

        QMessageBox::critical(this, "Error", "No se pudo actualizar. Verifique que el stock no sea un número negativo.");
        on_btnListar_clicked();
    }


}






void InventarioMedicamentos::on_btnEditar_clicked()
{

    int filaSeleccionada = ui->TblInventario->currentRow();

    if (filaSeleccionada < 0) {
        QMessageBox::warning(this, "Selección Requerida",
                             "Por favor, haga clic en la fila del medicamento que desea editar.");
        return;
    }

    QMessageBox::information(this, "Edición Habilitada",
                             "Fila habilitada para Edición. Puede modificar Nombre, Precio, Tipo o Proveedor. El ID y el Stock están protegidos.");

    ui->TblInventario->blockSignals(true);


    for (int col = 0; col < ui->TblInventario->columnCount(); ++col) {
        QTableWidgetItem* item = ui->TblInventario->item(filaSeleccionada, col);
        if (item) item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    }


    int columnasEditables[] = {1, 2, 4, 5};
    for (int col : columnasEditables) {
        QTableWidgetItem* item = ui->TblInventario->item(filaSeleccionada, col);
        if (item) {
            item->setFlags(item->flags() | Qt::ItemIsEditable);
        }
    }

    ui->TblInventario->blockSignals(false);

}



void InventarioMedicamentos::on_TblInventario_itemChanged(QTableWidgetItem *item){

    if (!item || miLista == nullptr) return;


    ui->TblInventario->blockSignals(true);

    int fila = item->row();
    int columna = item->column();


    QTableWidgetItem* idItem = ui->TblInventario->item(fila, 0);
    if (!idItem) {
        ui->TblInventario->blockSignals(false);
        return;
    }
    int id = idItem->text().toInt();

    FarmaSystem::Medicamento* med = miLista->buscarPorId(id);
    if (med == nullptr) {
        ui->TblInventario->blockSignals(false);
        return;
    }

    bool edicionExitosa = false;

    if (columna == 1) { // Nombre
        std::string nuevoNombre = item->text().trimmed().toStdString();
        if (!nuevoNombre.empty()) {
            med->setNombre(nuevoNombre);
            edicionExitosa = true;
        } else {
            QMessageBox::critical(this, "Error de Validación", "El nombre no puede estar vacío.");
            item->setText(QString::fromStdString(med->getNombre()));
        }
    }
    else if (columna == 2) { // Precio
        bool ok;
        double nuevoPrecio = item->text().toDouble(&ok);
        if (ok && nuevoPrecio >= 0) {
            med->setPrecio(nuevoPrecio);
            edicionExitosa = true;
        } else {
            QMessageBox::critical(this, "Error de Validación", "Por favor ingrese un precio numérico válido.");
            item->setText(QString::number(med->getPrecio(), 'f', 2));
        }
    }
    else if (columna == 4) {
        std::string nuevaCatego = item->text().trimmed().toStdString();
        if (!nuevaCatego.empty()) {
            med->setCategoria(nuevaCatego);
            edicionExitosa = true;
        } else {
            QMessageBox::critical(this, "Error de Validación", "La categoría no puede estar vacía.");
            item->setText(QString::fromStdString(med->getCategoria()));
        }
    }
    else if (columna == 5) {
        bool ok;
        int nuevoProv = item->text().toInt(&ok);
        if (ok && nuevoProv > 0) {
            med->setIdPROVEEDOR(nuevoProv);
            edicionExitosa = true;
        } else {
            QMessageBox::critical(this, "Error de Validación", "El ID del Proveedor debe ser positivo.");
            item->setText(QString::number(med->getIdPROVEEDOR()));
        }
    }


    if (edicionExitosa) {
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->TblInventario->blockSignals(false);
        QMessageBox::information(this, "Éxito", "¡Medicamento editado con éxito!");
    } else {
        ui->TblInventario->blockSignals(false);
    }

}







void InventarioMedicamentos::on_btnEliminar_clicked()
{

    int filaSeleccionada = ui->TblInventario->currentRow();

    if (filaSeleccionada < 0) {
        QMessageBox::warning(this, "Selección Requerida",
                             "Por favor, seleccione el medicamento que desea eliminar de la tabla.");
        return;
    }


    QTableWidgetItem* idItem = ui->TblInventario->item(filaSeleccionada, 0);
    if (!idItem) return;
    int id = idItem->text().toInt();


    QString nombreMed = ui->TblInventario->item(filaSeleccionada, 1)->text();


    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Confirmar Eliminación",
                                      "¿Está completamente seguro de eliminar el medicamento: " + nombreMed + " (ID: " + QString::number(id) + ")?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::No) {
        return;
    }


    if (miLista != nullptr && miLista->Eliminar(id)) {


        ui->TblInventario->blockSignals(true);
        ui->TblInventario->removeRow(filaSeleccionada);
        ui->TblInventario->blockSignals(false);

        QMessageBox::information(this, "Éxito", "El medicamento ha sido eliminado correctamente del sistema.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo eliminar el medicamento de la lista interna.");
    }
















}

