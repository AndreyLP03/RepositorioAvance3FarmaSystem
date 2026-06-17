#ifndef INVENTARIOMEDICAMENTOS_H
#define INVENTARIOMEDICAMENTOS_H

#include <QDialog>
#include <QTableWidgetItem>
#include "SistemaFarmacia.h"

namespace Ui {
class InventarioMedicamentos;
}

class InventarioMedicamentos : public QDialog
{
    Q_OBJECT

public:
    explicit InventarioMedicamentos(FarmaSystem::SistemaFarmacia* sistemaCentral, QWidget *parent = nullptr);
    ~InventarioMedicamentos();

    void actualizarTabla(const std::string &filtroBusqueda);

private slots:
    void on_btnRegistrarNuevoMedicamento_clicked();
    void on_btnBuscar_clicked();
    void on_btnEliminar_clicked();
    void on_btnListar_clicked();
    void on_btnEditar_clicked();
    void on_btnActualizarStock_clicked();

    void on_txtBuscar_textChanged(const QString &arg1);
    void on_TblInventario_itemClicked(QTableWidgetItem *item);

private:
    Ui::InventarioMedicamentos *ui;
    FarmaSystem::SistemaFarmacia* sistema;
};

#endif