#include "ventanaprincipal.h"
#include "SistemaFarmacia.h" // <--- Inyectamos el motor central

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Instanciamos el sistema único en memoria.
    // Al crearse aquí, el constructor va a leer automáticamente los archivos .txt
    FarmaSystem::SistemaFarmacia sistema;

    // Le pasamos el sistema a la ventana principal por dirección (&sistema)
    VentanaPrincipal w(&sistema);
    w.show();

    return QCoreApplication::exec();
    // Al cerrarse la app y morir la variable "sistema",
    // el destructor guardará todo automáticamente en los archivos .txt
}