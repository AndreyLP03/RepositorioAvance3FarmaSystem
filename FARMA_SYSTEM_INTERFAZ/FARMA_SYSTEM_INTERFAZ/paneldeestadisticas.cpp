#include "paneldeestadisticas.h"
#include "ui_paneldeestadisticas.h"
#include <QString>
#include <QDebug>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <map>

PaneldeEstadisticas::PaneldeEstadisticas(FarmaSystem::ListaMedicamentos* inventarioReal,
                                         FarmaSystem::ListaCircularVentas* ventasReal,
                                         QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PaneldeEstadisticas)
    , inventario(inventarioReal)
    , historialVentas(ventasReal)
{
    ui->setupUi(this);

    // Configuración inicial de la tabla de categorías
    ui->tableWidgetCategorias->setColumnCount(2);
    QStringList cabecera;
    cabecera << "Categoría" << "Cantidad Disponible";
    ui->tableWidgetCategorias->setHorizontalHeaderLabels(cabecera);

    ui->tableWidgetCategorias->verticalHeader()->setVisible(false);
    ui->tableWidgetCategorias->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Carga inicial automática de datos al abrir el panel
    on_btnActualizarDatos_clicked();
}

PaneldeEstadisticas::~PaneldeEstadisticas()
{
    delete ui;
}

void PaneldeEstadisticas::on_btnActualizarDatos_clicked()
{
    qDebug() << "Sincronizando todas las métricas en caliente...";

    // Ejecución secuencial de los tres algoritmos de cálculo
    calcularMenorStock();
    cargarTablaCategorias();
    calcularFinanzasYVentas();
}

void PaneldeEstadisticas::calcularMenorStock()
{
    if (inventario == nullptr || inventario->getPrimero() == nullptr) {
        ui->lblMenorStock->setText("Sin Productos");
        return;
    }

    FarmaSystem::NodoMedicamento* aux = inventario->getPrimero();
    int stockMinimo = 999999;
    std::string nombreMinimo = "Ninguno";

    // Recorrido lineal simple de la lista de medicamentos
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

    if (inventario != nullptr) {
        FarmaSystem::NodoMedicamento* aux = inventario->getPrimero();
        while (aux != nullptr) {
            if (aux->meds != nullptr) {
                std::string cat = aux->meds->getCategoria();
                int stockActual = aux->meds->getStock();

                // Validación de strings cubriendo variaciones de tildes
                if (cat == "Generico" || cat == "Genéricos" || cat == "Genérico") countGenericos += stockActual;
                else if (cat == "De Marca" || cat == "Marca" || cat == "MedicamentoMarca") countDeMarca += stockActual;
                else if (cat == "Controlado" || cat == "Controlados" || cat == "MedicamentoControlado") countControlados += stockActual;
            }
            aux = aux->siguienteMed;
        }
    }

    // Actualización de las celdas de la tabla en la interfaz gráfica
    ui->tableWidgetCategorias->setItem(0, 0, new QTableWidgetItem("Genéricos"));
    ui->tableWidgetCategorias->setItem(0, 1, new QTableWidgetItem(QString::number(countGenericos) + " uds"));
    ui->tableWidgetCategorias->setItem(1, 0, new QTableWidgetItem("De Marca"));
    ui->tableWidgetCategorias->setItem(1, 1, new QTableWidgetItem(QString::number(countDeMarca) + " uds"));
    ui->tableWidgetCategorias->setItem(2, 0, new QTableWidgetItem("Controlados"));
    ui->tableWidgetCategorias->setItem(2, 1, new QTableWidgetItem(QString::number(countControlados) + " uds"));
}

void PaneldeEstadisticas::calcularFinanzasYVentas()
{
    // Verificación de seguridad de la estructura circular compartida
    if (historialVentas == nullptr || historialVentas->getPrimero() == nullptr) {
        ui->lblIngresosTotales->setText("₡0.00");
        ui->lblMasVendido->setText("Sin Ventas");
        ui->lblClienteEstrella->setText("Sin Ventas");
        return;
    }

    FarmaSystem::NodoVenta* primero = historialVentas->getPrimero();
    FarmaSystem::NodoVenta* aux = primero;

    double sumaIngresosTotales = 0.0;
    std::map<std::string, int> mapaFrecuencia; // Almacena cantidades por nombre de medicamento
    std::map<int, double> mapaClientes;         // Almacena dinero acumulado por ID de cliente

    // Recorrido robusto de la lista circular utilizando puntero constante
    do {
        if (aux != nullptr && aux->getVenta() != nullptr) {
            const FarmaSystem::Venta* v = aux->getVenta(); // Enfoque seguro 'const' para acople de métodos

            std::string medNombre = v->getNombreMedicamento();
            int cantidad = v->getCantidad();
            int idCliente = v->getIdCliente();
            double montoVenta = v->getPrecioFinal();

            // Mecanismo de respaldo: si getPrecioFinal() es inválido o retorna 0, se calcula localmente
            if (montoVenta <= 0 && cantidad > 0) {
                montoVenta = v->getPrecioUnitario() * cantidad;
            }

            // Acumulaciones en estructuras temporales
            sumaIngresosTotales += montoVenta;

            if (!medNombre.empty() && cantidad > 0) {
                mapaFrecuencia[medNombre] += cantidad;
            }

            if (idCliente > 0) {
                mapaClientes[idCliente] += montoVenta;
            }
        }
        aux = aux->getSiguiente();
    } while (aux != nullptr && aux != primero); // Rompe el ciclo circular correctamente al regresar al inicio

    // 1. Mostrar Ingresos Totales
    ui->lblIngresosTotales->setText("₡" + QString::number(sumaIngresosTotales, 'f', 2));

    // 2. Determinar Medicamento Más Vendido (Ciclo corregido con 'elemento')
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

    // 3. Determinar Cliente Estrella Dinámico
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
    // Reservado para persistencia en archivos de texto o serialización futura
}

void PaneldeEstadisticas::on_btnCerrarPanel_clicked()
{
    this->close();
}