#ifndef PANELDEESTADISTICAS_H
#define PANELDEESTADISTICAS_H

#include <QDialog>
#include "SistemaFarmacia.h"

namespace Ui {
class PaneldeEstadisticas;
}

class PaneldeEstadisticas : public QDialog
{
    Q_OBJECT

public:

    explicit PaneldeEstadisticas(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent = nullptr);
    ~PaneldeEstadisticas();

private slots:
    void on_btnActualizarDatos_clicked();
    void on_btnGuardarCambios_clicked();
    void on_btnCerrarPanel_clicked();

private:
    Ui::PaneldeEstadisticas *ui;


    FarmaSystem::SistemaFarmacia* sistema;


    void calcularMenorStock();
    void cargarTablaCategorias();
    void calcularFinanzasYVentas();
};

#endif