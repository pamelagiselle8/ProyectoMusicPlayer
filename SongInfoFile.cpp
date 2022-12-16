#include <iostream>
#include <vector>
#include "Object.cpp"
#include "TDAArchivo.cpp"
using namespace std;

#pragma once
class SongInfoFile : public TDAArchivo {
    private:
        // Atributos
        vector<SongInfo*> canciones;
    public:
        // Constructores y destructor
        SongInfoFile() {}
        SongInfoFile(string fileName) : TDAArchivo(fileName) {}
        ~SongInfoFile() {
            for (int i = 0; i < canciones.size(); i++) {
                delete canciones[i];
            }
            canciones.clear();
        }

        // Getters y setters
        vector<SongInfo*> getCanciones() { return canciones; }
        void setCanciones(vector<SongInfo*> canciones) { this->canciones = canciones; }
        
        // Metodos de administracion
        bool agregarCancion(SongInfo* cancion) {
            // Agrega una cancion validando que no se repita
            for (int i = 0; i < canciones.size(); i++)
                if (canciones[i]->equals(cancion))
                    return false;
            canciones.push_back(cancion);
            return true;
        }
        virtual bool Leer() {
            return true;
        }
        virtual bool Escribir() {
            return true;
        }
};