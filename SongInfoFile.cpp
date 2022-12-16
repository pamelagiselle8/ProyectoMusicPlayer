#include <iostream>
#include <vector>
#include "Object.cpp"
using namespace std;

#pragma once
class SongInfoFile {
    private:
        // Atributos
        vector<Object*> objects;
    public:
        // Constructores
        SongInfoFile() {}

        // Getters y setters
        vector<Object*> getObjects() { return objects; }
        void setObjects(vector<Object*> objects) { this->objects = objects; }
        
        // Metodos de administracion
        void leer() {}
        void escribir() {}
};