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
            if (file.is_open()) {
                string buffer = "";
                // Leer en bloques
                getline(file, buffer);
                for (int i = 0; i < buffer.length(); i += 140)
                    agregarCancion(new SongInfo(
                        buffer.substr(i, 20),       // Nombre
                        buffer.substr(i+20, 20),    // Artista
                        buffer.substr(i+40, 20),    // Album
                        buffer.substr(i+60, 20),    // Genero
                        buffer.substr(i+80, 60)));  // Ruta
                // trim_right(buffer);
            }
            return file.is_open();
        }

        // Metodo para rellenar el espacio no utilizado
        string truncarDato(string dato, int capacidad) {
            string datoTruncado = dato.substr(0, 20);
            datoTruncado.append(capacidad - datoTruncado.size(), ' ');
            return datoTruncado;
        }

        virtual bool Escribir() {
            if (file.is_open()) {
                string buffer = "";
                // Construir buffer
                for (int i = 0; i < canciones.size(); i++) {

                    // Recuperar los campos del registro
                    SongInfo* cancion = canciones[i];
                    if (cancion) {
                        string nombre = cancion->getNombre(),
                            artista = cancion->getArtista(),
                            album = cancion->getDisco(),
                            genero = cancion->getGenero(),
                            ruta = cancion->getRuta();

                        // Rellenar el espacio no utilizado
                        buffer.append(truncarDato(nombre, 20));
                        buffer.append(truncarDato(artista, 20));
                        buffer.append(truncarDato(album, 20));
                        buffer.append(truncarDato(genero, 20));
                        buffer.append(truncarDato(ruta, 60));
                    }
                }
                // Escribir en el archivo
                file.write(buffer.data(), buffer.size());
            }
            return file.is_open();
        }
};