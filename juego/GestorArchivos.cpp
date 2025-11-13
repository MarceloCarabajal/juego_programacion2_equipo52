#define _CRT_SECURE_NO_WARNINGS
#include "GestorArchivos.h"
#include <iostream>

GestorArchivos::GestorArchivos(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {
}

bool GestorArchivos::guardar(int puntaje) {
    FILE* pFile;
    bool result;
    
    pFile = fopen(_nombreArchivo.c_str(), "ab");
    
    if (pFile == nullptr) {
        return false;
    }
    
    result = fwrite(&puntaje, sizeof(int), 1, pFile);
    
    fclose(pFile);
    
    return result;
}

int GestorArchivos::leer(int pos) {
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

int GestorArchivos::leerTodos(int puntajes[], int cantidad) {
    FILE* pFile;
    int result;
    
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    
    if (pFile == nullptr) {
        return 0;
    }
    
    result = fread(puntajes, sizeof(int), cantidad, pFile);
    
    fclose(pFile);
    
    return result;
}

int GestorArchivos::getCantidadRegistros() {
    FILE* pFile;
    int cantidad;
    
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    
    if (pFile == nullptr) {
        return 0;
    }
    
    fseek(pFile, 0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(int);
    
    fclose(pFile);
    
    return cantidad;
}

void GestorArchivos::mostrarPuntajes() {
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



