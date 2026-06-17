#ifndef REGISTROMEDICAMENTOS_H
#define REGISTROMEDICAMENTOS_H

#include "SistemaFarmacia.h"
#include <QDialog>

namespace Ui {
class registromedicamentos;
}

class registromedicamentos : public QDialog
{
    Q_OBJECT

public:
    explicit registromedicamentos(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent = nullptr, int idEditar = -1);
    ~registromedicamentos();

private slots:
    void on_btnIrInventario_clicked();
    void on_btnGuardar_clicked();
    void on_btnLimpiar_clicked();

private:
    Ui::registromedicamentos *ui;
    FarmaSystem::SistemaFarmacia* sistema;
    int idMedicamentoEdicion;

    void cargarProveedoresEnComboBox();
    void cargarDatosMedicamento();
};

#endif