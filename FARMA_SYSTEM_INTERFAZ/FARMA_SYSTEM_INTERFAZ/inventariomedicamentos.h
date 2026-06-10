#ifndef INVENTARIOMEDICAMENTOS_H
#define INVENTARIOMEDICAMENTOS_H
#include "registromedicamentos.h"
#include "listamedicamentos.h"

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class InventarioMedicamentos;
}

class InventarioMedicamentos : public QDialog
{
    Q_OBJECT

public:
    explicit InventarioMedicamentos(FarmaSystem::ListaMedicamentos* listaCompartida,FarmaSystem::ListaProveedores* listaProv,QWidget *parent = nullptr);
    ~InventarioMedicamentos();

private slots:
    void on_btnRegistrarNuevoMedicamento_clicked();

    void on_btnListar_clicked();

    void on_btnBuscar_clicked();

    void on_btnActualizarStock_clicked();
    void on_btnEditar_clicked();
    void on_TblInventario_itemChanged(QTableWidgetItem *item);
    void on_btnEliminar_clicked();

private:
    Ui::InventarioMedicamentos *ui;
    registromedicamentos *ventanaRegistro;

    FarmaSystem::ListaMedicamentos* miLista;
    FarmaSystem::ListaProveedores* misProveedores;
};

#endif // INVENTARIOMEDICAMENTOS_H
