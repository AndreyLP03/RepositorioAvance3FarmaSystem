#ifndef VENTANAPROVEEDORES_H
#define VENTANAPROVEEDORES_H

#include <QDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <string>


namespace FarmaSystem {
class ListaProveedores;
class ListaMedicamentos;
}

namespace Ui {
class ventanaProveedores;
}

class ventanaProveedores : public QDialog
{
    Q_OBJECT

public:

    explicit ventanaProveedores(FarmaSystem::ListaProveedores* listaProv, FarmaSystem::ListaMedicamentos* listaMed, QWidget *parent = nullptr);
    ~ventanaProveedores();

private slots:
    void on_btnGuardar_clicked();
    void on_btnActualizar_clicked();
    void on_btnEliminar_clicked();
    void on_btnLimpiar_clicked();
    void on_txtBuscar_textChanged(const QString &arg1);
    void on_tablaProveedores_itemClicked(QTableWidgetItem *item);

private:
    Ui::ventanaProveedores *ui;


    FarmaSystem::ListaProveedores* losProveedores;
    FarmaSystem::ListaMedicamentos* losMedicamentos;

    void actualizarTabla(const std::string& filtro = "");
    void limpiarCampos();
};

#endif // VENTANAPROVEEDORES_H