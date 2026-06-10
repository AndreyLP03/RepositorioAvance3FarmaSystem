#ifndef PANELDEESTADISTICAS_H
#define PANELDEESTADISTICAS_H

#include <QDialog>
#include "listamedicamentos.h"
#include "ListaVentas.h"

namespace Ui {
class PaneldeEstadisticas;
}

class PaneldeEstadisticas : public QDialog
{
    Q_OBJECT

public:
    explicit PaneldeEstadisticas(FarmaSystem::ListaMedicamentos* inventarioReal,
                                 FarmaSystem::ListaCircularVentas* ventasReal,
                                 QWidget *parent = nullptr);
    ~PaneldeEstadisticas();

private slots:
    void on_btnActualizarDatos_clicked();
    void on_btnGuardarCambios_clicked();
    void on_btnCerrarPanel_clicked();

private:
    Ui::PaneldeEstadisticas *ui;

    // Punteros a los datos reales compartidos de la App
    FarmaSystem::ListaMedicamentos* inventario;
    FarmaSystem::ListaCircularVentas* historialVentas;

    // Métodos de procesamiento interno
    void calcularMenorStock();
    void cargarTablaCategorias();
    void calcularFinanzasYVentas();
};

#endif // PANELDEESTADISTICAS_H