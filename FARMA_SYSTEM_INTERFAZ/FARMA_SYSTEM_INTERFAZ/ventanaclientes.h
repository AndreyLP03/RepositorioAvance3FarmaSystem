#ifndef VENTANACLIENTES_H
#define VENTANACLIENTES_H

#include <QMainWindow>
#include "ListaClientes.h"

QT_BEGIN_NAMESPACE
namespace Ui { class cliente; }
QT_END_NAMESPACE

class VentanaClientes : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaClientes(FarmaSystem::ListaClientes* listaInyectada, QWidget *parent = nullptr);
    ~VentanaClientes() override;

private slots:
    void on_btnGuardar_clicked();
    void on_btnLimpiar_clicked();
    void on_btnEliminar_clicked();
    void on_btnActualizar_clicked();
    void on_txtBuscar_textChanged(const QString &arg1);
    void on_tablaClientes_cellClicked(int row, int column);

private:
    Ui::cliente *ui;
    FarmaSystem::ListaClientes* miListaClientes;

    void actualizarTabla();
};

#endif // VENTANACLIENTES_H