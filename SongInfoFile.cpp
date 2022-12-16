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

        string truncarDato(string dato) {
            string datoTruncado = dato.substr(0, 20);
            datoTruncado.append(20 - datoTruncado.size(), ' ');
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
                        string datoTruncado = nombre.substr(0, 20);
                        datoTruncado.append(20 - datoTruncado.size(), ' ');
                        buffer.append(datoTruncado);
                        datoTruncado = artista.substr(0, 20) ;
                        datoTruncado.append(20 - datoTruncado.size(), ' ');
                        buffer.append(datoTruncado);
                        datoTruncado = album.substr(0, 20) ;
                        datoTruncado.append(20 - datoTruncado.size(), ' ');
                        buffer.append(datoTruncado);
                        datoTruncado =  genero.substr(0, 20) ;
                        datoTruncado.append(20 - datoTruncado.size(), ' ');
                        buffer.append(datoTruncado);
                        datoTruncado = ruta.substr(0, 60);
                        datoTruncado.append(20 - datoTruncado.size(), ' ');
                        buffer.append(datoTruncado);
                    }
                }
                // Escribir en el archivo
                file.write(buffer.data(), buffer.size());
            }
            return file.is_open();
        }
};