#include <iostream>
#include <fstream>
using namespace std;

#pragma once
class TDAArchivo {
    protected:
        // Atributos
        char *data;
        int size;
        string fileName;
        fstream file;
        
        // Constructores
        TDAArchivo() {}
        TDAArchivo(string fileName) : fileName(fileName) {}
        TDAArchivo(char* data, int size, string fileName)
            : data(data), size(size), fileName(fileName) {}

    public:
        // Metodos de administracion
        virtual void Cerrar() { file.close(); }
        virtual bool Abrir() {
            file.open(fileName, std::fstream::in | std::fstream::out);
            return file.is_open();
        }
        virtual bool Escribir() = 0;
        virtual bool Leer() = 0;

        // Getters y setters
        char* GetData() const { return data; }
        void SetData(char* data) { this->data = data; }
        int GetSize() const { return size; }
        void SetSize(int size) { this->size = size; }
        string GetFileName() const { return fileName; }
        void SetFileName(string fileName) { this->fileName = fileName; }
    
};