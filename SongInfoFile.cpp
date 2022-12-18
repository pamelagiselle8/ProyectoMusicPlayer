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
        int sizeDato = 40, sizeRuta = 60, sizeCodigo = 4;
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
                for (int i = 0; i < buffer.length(); i += (sizeDato*4)+sizeRuta+sizeCodigo) {
                    agregarCancion(new SongInfo(
                        buffer.substr(i, sizeDato),                                 // Nombre
                        buffer.substr(i+(sizeDato), sizeDato),                      // Artista
                        buffer.substr(i+(sizeDato*2), sizeDato),                    // Album
                        buffer.substr(i+(sizeDato*3), sizeDato),                    // Genero
                        buffer.substr(i+(sizeDato*4), sizeRuta),                  // Ruta
                        stoi(buffer.substr(i+(sizeDato*4)+sizeRuta, sizeCodigo))));   // Codigo
                }
                // trim_right(buffer);
            }
            return file.is_open();
        }

        // Metodo para rellenar el espacio no utilizado
        string truncarDato(string dato, int capacidad) {
            string datoTruncado = dato.substr(0, capacidad);
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
                        string datoTruncado = "",
                            nombre = cancion->getNombre(),
                            artista = cancion->getArtista(),
                            album = cancion->getDisco(),
                            genero = cancion->getGenero(),
                            ruta = cancion->getRuta(),
                            codigo = to_string(cancion->getCodigo());

                        // Rellenar el espacio no utilizado
                        buffer.append(truncarDato(nombre, sizeDato));
                        buffer.append(truncarDato(artista, sizeDato));
                        buffer.append(truncarDato(album, sizeDato));
                        buffer.append(truncarDato(genero, sizeDato));
                        buffer.append(truncarDato(ruta, sizeRuta));

                        // Guardar codigo de la cancion
                        datoTruncado.append(sizeCodigo - codigo.size(), '0');
                        datoTruncado.append(codigo);
                        buffer.append(datoTruncado);
                    }
                }
                // Escribir en el archivo
                file.write(buffer.data(), buffer.size());
            }
            return file.is_open();
        }
};