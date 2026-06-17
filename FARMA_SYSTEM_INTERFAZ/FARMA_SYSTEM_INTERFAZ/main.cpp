#include "ventanaprincipal.h"
#include "SistemaFarmacia.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    FarmaSystem::SistemaFarmacia sistema;


    VentanaPrincipal w(&sistema);
    w.show();

    return QCoreApplication::exec();

}