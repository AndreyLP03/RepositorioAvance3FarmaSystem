#include "paneldeestadisticas.h"
#include "ui_paneldeestadisticas.h"
#include "SistemaFarmacia.h"

#include "MedicamentoGenerico.h"
#include "MedicamentoMarca.h"
#include "MedicamentoControlado.h"

#include <QString>
#include <QDebug>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <map>

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>

PaneldeEstadisticas::PaneldeEstadisticas(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PaneldeEstadisticas)
{
    ui->setupUi(this);
    this->sistema = sistemaCentral;

    ui->tableWidgetCategorias->setColumnCount(2);
    QStringList cabecera;
    cabecera << "Categoría" << "Cantidad Disponible";
    ui->tableWidgetCategorias->setHorizontalHeaderLabels(cabecera);

    ui->tableWidgetCategorias->verticalHeader()->setVisible(false);
    ui->tableWidgetCategorias->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetCategorias->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if (ui->btnActualizarDatos) {
        connect(ui->btnActualizarDatos, &QPushButton::clicked, this, &PaneldeEstadisticas::on_btnActualizarDatos_clicked);
    }

    on_btnActualizarDatos_clicked();
}

PaneldeEstadisticas::~PaneldeEstadisticas()
{
    delete ui;
}

void PaneldeEstadisticas::on_btnActualizarDatos_clicked()
{
    calcularMenorStock();
    cargarTablaCategorias();
    calcularFinanzasYVentas();
}

void PaneldeEstadisticas::calcularMenorStock()
{
    if (sistema == nullptr || sistema->getListaMedicamentos().getPrimero() == nullptr) {
        ui->lblMenorStock->setText("Sin Productos");
        return;
    }

    FarmaSystem::NodoMedicamento* aux = sistema->getListaMedicamentos().getPrimero();
    int stockMinimo = 999999;
    std::string nombreMinimo = "Ninguno";

    while (aux != nullptr) {
        if (aux->meds != nullptr) {
            int stockActual = aux->meds->getStock();
            if (stockActual < stockMinimo) {
                stockMinimo = stockActual;
                nombreMinimo = aux->meds->getNombre();
            }
        }
        aux = aux->siguienteMed;
    }

    QString resultado = QString::fromStdString(nombreMinimo) + " (" + QString::number(stockMinimo) + " uds)";
    ui->lblMenorStock->setText(resultado);
}

void PaneldeEstadisticas::cargarTablaCategorias()
{
    ui->tableWidgetCategorias->setRowCount(3);
    int countGenericos = 0, countDeMarca = 0, countControlados = 0;

    if (sistema != nullptr) {
        FarmaSystem::NodoMedicamento* aux = sistema->getListaMedicamentos().getPrimero();
        while (aux != nullptr) {
            FarmaSystem::Medicamento* med = aux->meds;
            if (med != nullptr) {
                int stockActual = med->getStock();

                if (dynamic_cast<FarmaSystem::MedicamentoGenerico*>(med)) {
                    countGenericos += stockActual;
                } else if (dynamic_cast<FarmaSystem::MedicamentoMarca*>(med)) {
                    countDeMarca += stockActual;
                } else if (dynamic_cast<FarmaSystem::MedicamentoControlado*>(med)) {
                    countControlados += stockActual;
                } else {
                    std::string cat = med->getCategoria();
                    if (cat == "Generico" || cat == "Genérico" || cat == "generico" || cat == "GENERICO" || cat == "Genericos") {
                        countGenericos += stockActual;
                    } else if (cat == "De Marca" || cat == "Marca" || cat == "marca" || cat == "MedicamentoMarca") {
                        countDeMarca += stockActual;
                    } else if (cat == "Controlado" || cat == "Controlados" || cat == "controlado" || cat == "MedicamentoControlado") {
                        countControlados += stockActual;
                    }
                }
            }
            aux = aux->siguienteMed;
        }
    }

    ui->tableWidgetCategorias->setItem(0, 0, new QTableWidgetItem("Genéricos"));
    ui->tableWidgetCategorias->setItem(0, 1, new QTableWidgetItem(QString::number(countGenericos) + " uds"));
    ui->tableWidgetCategorias->setItem(1, 0, new QTableWidgetItem("De Marca"));
    ui->tableWidgetCategorias->setItem(1, 1, new QTableWidgetItem(QString::number(countDeMarca) + " uds"));
    ui->tableWidgetCategorias->setItem(2, 0, new QTableWidgetItem("Controlados"));
    ui->tableWidgetCategorias->setItem(2, 1, new QTableWidgetItem(QString::number(countControlados) + " uds"));
}

void PaneldeEstadisticas::calcularFinanzasYVentas()
{
    if (sistema == nullptr || sistema->getListaVentas().getPrimero() == nullptr) {
        ui->lblIngresosTotales->setText("₡0.00");
        ui->lblMasVendido->setText("Sin Ventas");
        ui->lblClienteEstrella->setText("Sin Ventas");
        return;
    }

    FarmaSystem::NodoVenta* primero = sistema->getListaVentas().getPrimero();
    FarmaSystem::NodoVenta* aux = primero;

    double sumaIngresosTotales = 0.0;
    std::map<std::string, int> mapaFrecuencia;
    std::map<int, double> mapaClientes;

    do {
        if (aux != nullptr && aux->getVenta() != nullptr) {
            const FarmaSystem::Venta* v = aux->getVenta();

            std::string medNombre = v->getNombreMedicamento();
            int cantidad = v->getCantidad();
            int idCliente = v->getIdCliente();
            double montoVenta = v->getPrecioFinal();

            if (montoVenta <= 0 && cantidad > 0) {
                montoVenta = v->getPrecioUnitario() * cantidad;
            }

            sumaIngresosTotales += montoVenta;

            if (!medNombre.empty() && cantidad > 0) {
                mapaFrecuencia[medNombre] += cantidad;
            }

            if (idCliente > 0) {
                mapaClientes[idCliente] += montoVenta;
            }
        }

        aux = aux->getSiguiente();
        if (aux == nullptr) break;

    } while (aux != primero);

    ui->lblIngresosTotales->setText("₡" + QString::number(sumaIngresosTotales, 'f', 2));

    std::string topMed = "Ninguno";
    int maxUnidades = 0;
    for (const auto& elemento : mapaFrecuencia) {
        if (elemento.second > maxUnidades) {
            maxUnidades = elemento.second;
            topMed = elemento.first;
        }
    }

    if (maxUnidades > 0) {
        ui->lblMasVendido->setText(QString::fromStdString(topMed) + " (" + QString::number(maxUnidades) + " uds)");
    } else {
        ui->lblMasVendido->setText("Sin Ventas");
    }

    int idClienteEstrella = -1;
    double maxDineroCliente = 0.0;
    for (const auto& par : mapaClientes) {
        if (par.second > maxDineroCliente) {
            maxDineroCliente = par.second;
            idClienteEstrella = par.first;
        }
    }

    if (idClienteEstrella != -1) {
        ui->lblClienteEstrella->setText("ID: " + QString::number(idClienteEstrella));
    } else {
        ui->lblClienteEstrella->setText("Sin Ventas");
    }
}

void PaneldeEstadisticas::on_btnGuardarCambios_clicked()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(
        this,
        "Guardar Reporte",
        "Reporte_Estadisticas",
        "Archivos de Texto (*.txt)"
        );

    if (nombreArchivo.isEmpty()) return;

    QFile archivo(nombreArchivo);
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo crear el archivo.");
        return;
    }

    QTextStream salida(&archivo);
    QString fechaHoraActual = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss AP");

    salida << "REPORTE DE ESTADISTICAS - FARMA-SYSTEM\n";
    salida << "Generado el: " << fechaHoraActual << "\n";
    salida << "---------------------------------------------\n\n";

    salida << "Medicamento con Menor Stock: " << ui->lblMenorStock->text() << "\n";
    salida << "Medicamento Mas Vendido: " << ui->lblMasVendido->text() << "\n";
    salida << "Cliente Estrella (ID): " << ui->lblClienteEstrella->text() << "\n";
    salida << "Total Ingresos: " << ui->lblIngresosTotales->text() << "\n\n";

    salida << "CANTIDADES POR CATEGORIA:\n";
    for (int fila = 0; fila < ui->tableWidgetCategorias->rowCount(); ++fila) {
        QTableWidgetItem* itemCategoria = ui->tableWidgetCategorias->item(fila, 0);
        QTableWidgetItem* itemCantidad = ui->tableWidgetCategorias->item(fila, 1);

        if (itemCategoria != nullptr && itemCantidad != nullptr) {
            salida << "- " << itemCategoria->text() << ": " << itemCantidad->text() << "\n";
        }
    }

    archivo.close();
    QMessageBox::information(this, "Guardar", "Reporte exportado exitosamente.");
}

void PaneldeEstadisticas::on_btnCerrarPanel_clicked()
{
    this->close();
}