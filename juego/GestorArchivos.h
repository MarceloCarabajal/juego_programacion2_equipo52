#pragma once
#include <cstdio>
#include <string>

class GestorArchivos {
public:
    GestorArchivos(std::string nombreArchivo = "puntajes.dat");
    
    bool guardar(int puntaje);
    int leer(int pos) const;
    int leerTodos(int puntajes[], int cantidad) const;
    int getCantidadRegistros() const;
    void mostrarPuntajes() const;

private:
    std::string _nombreArchivo;
};



