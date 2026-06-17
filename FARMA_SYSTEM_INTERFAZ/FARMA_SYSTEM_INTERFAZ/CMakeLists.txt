cmake_minimum_required(VERSION 3.19)
project(FARMA_SYSTEM_INTERFAZ LANGUAGES CXX)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

qt_add_executable(FARMA_SYSTEM_INTERFAZ
    main.cpp
    ventanaprincipal.cpp ventanaprincipal.h ventanaprincipal.ui
    cliente.cpp cliente.h cliente.ui
    inventariomedicamentos.cpp inventariomedicamentos.h inventariomedicamentos.ui
    ListaClientes.cpp ListaClientes.h ListaMedicamentos.cpp ListaMedicamentos.h
    ListaProveedores.cpp ListaProveedores.h ListaVentas.cpp ListaVentas.h


    NodoCliente.cpp NodoCliente.h NodoMedicamento.cpp NodoMedicamento.h
    NodoProveedor.cpp NodoProveedor.h NodoVenta.cpp NodoVenta.h
    paneldeestadisticas.cpp paneldeestadisticas.h paneldeestadisticas.ui
    Proveedor.cpp Proveedor.h
    registromedicamentos.cpp registromedicamentos.h registromedicamentos.ui
    SistemaFarmacia.h venta.cpp venta.h
    ventanaclientes.cpp ventanaclientes.h ventanaprincipal.cpp ventanaprincipal.h ventanaprincipal.ui
    ventanaproveedores.cpp ventanaproveedores.h ventanaproveedores.ui ventas.cpp ventas.h ventas.ui
    medicamento.h
    medicamento.cpp
    MedicamentoGenerico.h
    MedicamentoGenerico.cpp
    MedicamentoControlado.h
    MedicamentoControlado.cpp
    MedicamentoMarca.h
    MedicamentoMarca.cpp
    ICONOS.qrc
    cliente.cpp cliente.h cliente.ui inventariomedicamentos.cpp inventariomedicamentos.h inventariomedicamentos.ui
    ListaClientes.cpp ListaClientes.h ListaMedicamentos.cpp ListaMedicamentos.h ListaProveedores.cpp ListaProveedores.h
    ListaVentas.cpp ListaVentas.h medicamento.cpp medicamento.h MedicamentoControlado.cpp MedicamentoControlado.h
    MedicamentoGenerico.cpp MedicamentoGenerico.h MedicamentoMarca.cpp MedicamentoMarca.h NodoCliente.cpp NodoCliente.h NodoMedicamento.cpp NodoMedicamento.h NodoProveedor.cpp NodoProveedor.h NodoVenta.cpp NodoVenta.h
    paneldeestadisticas.cpp paneldeestadisticas.h paneldeestadisticas.ui Proveedor.cpp Proveedor.h registromedicamentos.cpp registromedicamentos.h
    SistemaFarmacia.h
    venta.cpp venta.h
    ventanaclientes.cpp ventanaclientes.h
    ventanaclientes.cpp ventanaclientes.h
    ventanaprincipal.cpp ventanaprincipal.h ventanaproveedores.cpp ventanaproveedores.h ventanaproveedores.ui
    ventanaproveedores.cpp ventanaproveedores.h ventas.cpp ventas.h
    main.cpp
    SistemaFarmacia.cpp
    cliente.cpp cliente.h inventariomedicamentos.cpp inventariomedicamentos.h ListaClientes.cpp ListaClientes.h ListaMedicamentos.cpp ListaMedicamentos.h ListaProveedores.cpp ListaProveedores.h ListaVentas.cpp ListaVentas.h main.cpp medicamento.cpp medicamento.h MedicamentoControlado.cpp MedicamentoControlado.h MedicamentoGenerico.cpp MedicamentoGenerico.h MedicamentoMarca.cpp MedicamentoMarca.h NodoCliente.h NodoMedicamento.cpp NodoMedicamento.h NodoProveedor.cpp NodoProveedor.h NodoVenta.cpp NodoVenta.h paneldeestadisticas.cpp paneldeestadisticas.h Proveedor.cpp Proveedor.h registromedicamentos.cpp registromedicamentos.h SistemaFarmacia.cpp SistemaFarmacia.h venta.cpp venta.h ventanaclientes.cpp ventanaclientes.h ventanaprincipal.cpp ventanaprincipal.h ventanaproveedores.cpp ventanaproveedores.h ventas.cpp ventas.h
    cliente.cpp cliente.h inventariomedicamentos.cpp inventariomedicamentos.h ListaClientes.cpp ListaClientes.h ListaMedicamentos.cpp ListaMedicamentos.h ListaProveedores.cpp ListaProveedores.h ListaVentas.cpp ListaVentas.h main.cpp medicamento.cpp medicamento.h MedicamentoControlado.cpp MedicamentoControlado.h MedicamentoGenerico.cpp MedicamentoGenerico.h MedicamentoMarca.cpp MedicamentoMarca.h NodoCliente.cpp NodoCliente.h NodoMedicamento.cpp NodoMedicamento.h NodoProveedor.cpp NodoProveedor.h NodoVenta.cpp NodoVenta.h paneldeestadisticas.cpp paneldeestadisticas.h Proveedor.cpp Proveedor.h registromedicamentos.cpp registromedicamentos.h registromedicamentos.ui SistemaFarmacia.cpp SistemaFarmacia.h venta.cpp venta.h ventanaclientes.cpp ventanaclientes.h ventanaprincipal.cpp ventanaprincipal.h ventanaproveedores.cpp ventanaproveedores.h ventas.cpp ventas.h
    cliente.cpp cliente.h inventariomedicamentos.cpp inventariomedicamentos.h inventariomedicamentos.ui ListaClientes.cpp ListaClientes.h ListaMedicamentos.cpp ListaMedicamentos.h ListaProveedores.cpp ListaProveedores.h ListaVentas.cpp ListaVentas.h main.cpp medicamento.cpp medicamento.h MedicamentoControlado.cpp MedicamentoControlado.h MedicamentoGenerico.cpp MedicamentoGenerico.h MedicamentoMarca.cpp MedicamentoMarca.h NodoCliente.cpp NodoCliente.h NodoMedicamento.cpp NodoMedicamento.h NodoProveedor.cpp NodoProveedor.h NodoVenta.cpp NodoVenta.h paneldeestadisticas.cpp paneldeestadisticas.h paneldeestadisticas.ui Proveedor.cpp Proveedor.h registromedicamentos.cpp registromedicamentos.h registromedicamentos.ui SistemaFarmacia.cpp SistemaFarmacia.h venta.cpp venta.h ventanaclientes.cpp ventanaclientes.h ventanaprincipal.cpp ventanaprincipal.h ventanaproveedores.cpp ventanaproveedores.h ventas.cpp ventas.h
    
)

target_link_libraries(FARMA_SYSTEM_INTERFAZ PRIVATE Qt::Core Qt::Widgets)
