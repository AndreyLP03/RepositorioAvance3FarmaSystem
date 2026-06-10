#ifndef REGISTROMEDICAMENTOS_H
#define REGISTROMEDICAMENTOS_H

#include "listamedicamentos.h"
#include "ListaProveedores.h"
#include <QDialog>

namespace Ui {
class registromedicamentos;
}

class registromedicamentos : public QDialog
{
    Q_OBJECT

public:

    explicit registromedicamentos(FarmaSystem::ListaMedicamentos* listaCompartida, FarmaSystem::ListaProveedores* listaProv, QWidget *parent = nullptr);
    ~registromedicamentos();

private slots:
    void on_btnIrInventario_clicked();
    void on_btnGuardar_clicked();
    void on_btnLimpiar_clicked();

private:
    Ui::registromedicamentos *ui;

    FarmaSystem::ListaMedicamentos* miLista;
    FarmaSystem::ListaProveedores* losProveedores;


    void cargarProveedoresEnComboBox();
};

#endif
