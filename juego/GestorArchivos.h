#pragma once
#include <cstdio>
#include <string>

class GestorArchivos {
public:
    GestorArchivos(std::string nombreArchivo = "puntajes.dat");
    
    bool guardar(int puntaje);
    int leer(int pos);
    int leerTodos(int puntajes[], int cantidad);
    int getCantidadRegistros();
    void mostrarPuntajes();

private:
    std::string _nombreArchivo;
};



