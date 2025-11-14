#define _CRT_SECURE_NO_WARNINGS
#include "GestorArchivos.h"
#include <iostream>

GestorArchivos::GestorArchivos(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {
}

bool GestorArchivos::guardar(int puntaje) {
    FILE* pFile;
    bool result = false;
    
    // Intentar múltiples rutas como con las fuentes
    std::string ruta1 = _nombreArchivo;
    std::string ruta2 = "../" + _nombreArchivo;
    std::string ruta3 = "../../" + _nombreArchivo;
    const char* rutas[] = {
        ruta1.c_str(),
        ruta2.c_str(),
        ruta3.c_str()
    };
    
    for (int i = 0; i < 3; i++) {
        pFile = fopen(rutas[i], "ab");
        if (pFile != nullptr) {
            result = fwrite(&puntaje, sizeof(int), 1, pFile);
            fclose(pFile);
            if (result) return true;
        }
    }
    
    return false;
}

int GestorArchivos::leer(int pos) const {
    FILE* pFile;
    int puntaje = -1;
    
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    
    if (pFile == nullptr) {
        return -1;
    }
    
    fseek(pFile, pos * sizeof(int), SEEK_SET);
    
    if (!fread(&puntaje, sizeof(int), 1, pFile)) {
        puntaje = -1;
    }
    
    fclose(pFile);
    
    return puntaje;
}

int GestorArchivos::leerTodos(int puntajes[], int cantidad) const {
    FILE* pFile;
    int result = 0;
    
    // Intentar múltiples rutas como con las fuentes
    std::string ruta1 = _nombreArchivo;
    std::string ruta2 = "../" + _nombreArchivo;
    std::string ruta3 = "../../" + _nombreArchivo;
    const char* rutas[] = {
        ruta1.c_str(),
        ruta2.c_str(),
        ruta3.c_str()
    };
    
    for (int i = 0; i < 3; i++) {
        pFile = fopen(rutas[i], "rb");
        if (pFile != nullptr) {
            result = fread(puntajes, sizeof(int), cantidad, pFile);
            fclose(pFile);
            if (result > 0) return result;
        }
    }
    
    return 0;
}

int GestorArchivos::getCantidadRegistros() const {
    FILE* pFile;
    int cantidad = 0;
    
    // Intentar múltiples rutas como con las fuentes
    std::string ruta1 = _nombreArchivo;
    std::string ruta2 = "../" + _nombreArchivo;
    std::string ruta3 = "../../" + _nombreArchivo;
    const char* rutas[] = {
        ruta1.c_str(),
        ruta2.c_str(),
        ruta3.c_str()
    };
    
    for (int i = 0; i < 3; i++) {
        pFile = fopen(rutas[i], "rb");
        if (pFile != nullptr) {
            fseek(pFile, 0, SEEK_END);
            cantidad = ftell(pFile) / sizeof(int);
            fclose(pFile);
            return cantidad;
        }
    }
    
    return 0;
}

void GestorArchivos::mostrarPuntajes() const {
    int cantidad = getCantidadRegistros();
    
    if (cantidad == 0) {
        std::cout << "No hay puntajes guardados aun." << std::endl;
        return;
    }
    
    // leer todos los puntajes de una vez
    int* puntajes = new int[cantidad];
    int leidos = leerTodos(puntajes, cantidad);
    
    std::cout << "=== PUNTAJES GUARDADOS ===" << std::endl;
    std::cout << "Cantidad de puntajes: " << leidos << std::endl;
    std::cout << "------------------------" << std::endl;
    
    for (int i = 0; i < leidos; i++) {
        std::cout << (i + 1) << ". " << puntajes[i] << " puntos" << std::endl;
    }
    
    std::cout << "=========================" << std::endl;
    
    delete[] puntajes;
}



