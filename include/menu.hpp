#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "lista.hpp"
#include "cancion.hpp"
#include <iostream>

class Menu {
private:
    Lista<Cancion> canciones;

    void mostrarLista() const;
    void agregarCancion();
    void eliminarCancion();
    void insertarCancionEn();
    void limpiarLista();
    void guardarLista();
    void cargarLista();
    void buscarCancion();
    void ordenarCatalogo();
    void mostrarMenuBusqueda();
    void mostrarMenuOrdenamiento();
    void mostrarMenuAlgoritmo();
    void buscarPorNombre();
    void buscarPorInterprete();
    void cargarDatosEjemplo();
    
    int leerEntero(const std::string&) const;
    std::string leerCadena(const std::string&) const;
    void pausar() const;

public:
    Menu();
    void ejecutar();
};

#endif