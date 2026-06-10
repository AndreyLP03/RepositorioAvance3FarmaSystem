#include "ventas.h"
#include "ui_ventas.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>

Ventas::Ventas(FarmaSystem::ListaMedicamentos* listaMed, FarmaSystem::ListaClientes* listaCli, FarmaSystem::ListaCircularVentas* listaVen, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Ventas)
{
    ui->setupUi(this);

    this->miListaMed = listaMed;
    this->miListaCli = listaCli;
    this->miListaVen = listaVen;

    this->nodoExplorador = nullptr;


    ui->tablaHistorialVentas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablaHistorialVentas->setSelectionBehavior(QAbstractItemView::SelectRows);


    actualizarTablaHistorial();
}

Ventas::~Ventas()
{
    delete ui;
}



void Ventas::on_btnVerificar_clicked()
{
    std::string idCliStr = ui->txtIdCliente->text().toStdString();
    std::string idMedStr = ui->txtIdMedicamento->text().toStdString();
    int cantidad = ui->txtCantidad->text().toInt();


    if (idCliStr.empty() || idMedStr.empty() || cantidad <= 0) {


        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Datos Inválidos");
        msgBox.setText("Por favor ingrese el cliente, medicamento y una cantidad válida (mayor a 0).");
        msgBox.setStyleSheet("QLabel { color: black; }");
        msgBox.exec();
        return;

    }


    FarmaSystem::Cliente* cliente = miListaCli->buscarPorCedula(idCliStr);
    if (cliente == nullptr) {

        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        msgBox.setText("No existe ningún cliente registrado con esa cédula.");
        msgBox.setStyleSheet("QLabel { color: black; }");
        msgBox.exec();
        return;


    }


    FarmaSystem::Medicamento* med = miListaMed->buscarPorId(std::stoi(idMedStr));
    if (med == nullptr) {

        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        msgBox.setText("No existe ningún medicamento con ese ID.");
        msgBox.setStyleSheet("QLabel { color: black; }");
        msgBox.exec();
        return;

    }


    if (med->getStock() < cantidad) {



        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Stock Insuficiente");
        msgBox.setText(QString("No hay suficientes unidades. Stock actual: %1").arg(med->getStock()));
        msgBox.setStyleSheet("QLabel { color: black; }");
        msgBox.exec();
        return;



    }


    ui->lblInfoMedicamento->setText(QString::fromStdString(med->getNombre()));
    ui->lblPrecioUnitario_2->setText("₡" + QString::number(med->getPrecio(), 'f', 2));


    double totalNeto = med->calcularPrecioFinal(cantidad);
    ui->lblTotalPagar->setText("₡" + QString::number(totalNeto, 'f', 2));

    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Verificación Exitosa");
    msgBox.setText("Datos comprobados. Ya puede proceder a facturar.");
    msgBox.setStyleSheet("QLabel { color: black; }");
    msgBox.exec();

}

void Ventas::on_btnFacturar_clicked()
{

    std::string idVentaStr = ui->txtIdVenta->text().toStdString();
    std::string idCliStr = ui->txtIdCliente->text().toStdString();
    std::string idMedStr = ui->txtIdMedicamento->text().toStdString();
    int cantidad = ui->txtCantidad->text().toInt();
    std::string fecha = ui->txtFecha->text().toStdString();

    if (idVentaStr.empty() || fecha.empty()) {

        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Faltan Datos");
        msgBox.setText("Complete el ID de Venta y la Fecha.");
        msgBox.setStyleSheet("QLabel { color: black; }");
        msgBox.exec();
        return;

    }

    int idVenta = std::stoi(idVentaStr);
    int idClienteInt = std::stoi(idCliStr);

    FarmaSystem::Medicamento* med = miListaMed->buscarPorId(std::stoi(idMedStr));


    if (med == nullptr || med->getStock() < cantidad) {


        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error de Consistencia");
        msgBox.setText("Por favor, haga clic en 'Verificar' antes de facturar.");
        msgBox.setStyleSheet("QLabel { color: black; }");
        msgBox.exec();
        return;

    }


    FarmaSystem::Venta* nuevaVenta = new FarmaSystem::Venta(idVenta, idClienteInt, med, cantidad, fecha);


    miListaVen->agregar(nuevaVenta);


    miListaMed->actualizarStockPorId(med->getId(), med->getStock() - cantidad);

    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Factura Emitida");
    msgBox.setText("Venta registrada con éxito y stock descontado.");
    msgBox.setStyleSheet("QLabel { color: black; }");
    msgBox.exec();

    on_btnLimpiar_clicked();
    actualizarTablaHistorial();
}

void Ventas::on_btnLimpiar_clicked()
{
    ui->txtIdVenta->clear();
    ui->txtIdCliente->clear();
    ui->txtIdMedicamento->clear();
    ui->txtCantidad->clear();
    ui->txtFecha->clear();

    ui->lblInfoMedicamento->setText("Ninguno");
    ui->lblPrecioUnitario_2->setText("₡0.00");
    ui->lblTotalPagar->setText("₡0.00");
}



void Ventas::actualizarTablaHistorial(int filtroClienteId)
{
    ui->tablaHistorialVentas->setRowCount(0);

    FarmaSystem::NodoVenta* aux = miListaVen->getPrimero();

    if (aux == nullptr) {
        ui->lblMontoAcu->setText("₡0.00");
        return;
    }

    int fila = 0;


    do {
        FarmaSystem::Venta* v = aux->getVenta();


        if (filtroClienteId == -1 || v->getIdCliente() == filtroClienteId) {
            ui->tablaHistorialVentas->insertRow(fila);

            ui->tablaHistorialVentas->setItem(fila, 0, new QTableWidgetItem(QString::number(v->getId())));
            ui->tablaHistorialVentas->setItem(fila, 1, new QTableWidgetItem(QString::number(v->getIdCliente())));
            ui->tablaHistorialVentas->setItem(fila, 2, new QTableWidgetItem(QString::fromStdString(v->getNombreMedicamento())));
            ui->tablaHistorialVentas->setItem(fila, 3, new QTableWidgetItem(QString::number(v->getCantidad())));
            ui->tablaHistorialVentas->setItem(fila, 4, new QTableWidgetItem("₡" + QString::number(v->getPrecioUnitario(), 'f', 2)));
            ui->tablaHistorialVentas->setItem(fila, 5, new QTableWidgetItem("₡" + QString::number(v->getPrecioFinal(), 'f', 2)));
            ui->tablaHistorialVentas->setItem(fila, 6, new QTableWidgetItem(QString::fromStdString(v->getFecha())));
            fila++;
        }

        aux = aux->getSiguiente();
    } while (aux != miListaVen->getPrimero());

    // Calculamos los acumulados en tiempo real con las funciones que hiciste en ListaCircularVentas
    double acumulado = (filtroClienteId == -1)
                           ? miListaVen->calcularAcumuladoTotal()
                           : miListaVen->calcularAcumuladoPorCliente(filtroClienteId);

    ui->lblMontoAcu->setText("₡" + QString::number(acumulado, 'f', 2));


    this->nodoExplorador = miListaVen->getPrimero();
    mostrarVentaEnExplorador();
}

void Ventas::on_btnFiltrar_clicked()
{
    QString filtroStr = ui->txtFiltroCliente->text();
    if (filtroStr.isEmpty()) {
        actualizarTablaHistorial(-1);
    } else {
        actualizarTablaHistorial(filtroStr.toInt());
    }
}


void Ventas::mostrarVentaEnExplorador() {
    if (nodoExplorador == nullptr || nodoExplorador->getVenta() == nullptr) {
        ui->lblMontoAcu->setText("[Ninguna Venta]");
        return;
    }

    FarmaSystem::Venta* v = nodoExplorador->getVenta();
    QString texto = QString("Venta #%1 | Cliente: %2 | Monto: ₡%3")
                        .arg(v->getId())
                        .arg(v->getIdCliente())
                        .arg(v->getPrecioFinal(), 0, 'f', 2);

    ui->lbnlRegistroActual->setText(texto);
}


void Ventas::on_btnSiguienteVenta_clicked()
{
    if (nodoExplorador != nullptr) {

        nodoExplorador = nodoExplorador->getSiguiente();
        mostrarVentaEnExplorador();
    }
}


void Ventas::on_btnAnteriorVenta_clicked()
{

    if (nodoExplorador != nullptr) {

        FarmaSystem::NodoVenta* aux = miListaVen->getPrimero();

        while (aux->getSiguiente() != nodoExplorador) {
            aux = aux->getSiguiente();
        }

        nodoExplorador = aux;
        mostrarVentaEnExplorador();
    }

}





void Ventas::on_btnLimpiarFiltro_clicked()
{

    ui->txtFiltroCliente->clear();
    actualizarTablaHistorial(-1);


}

