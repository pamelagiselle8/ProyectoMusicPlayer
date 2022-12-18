#include <iostream>
#include <vector>
#include "Playlist.cpp"
#include "TDAArchivo.cpp"
using namespace std;

#pragma once
class PlaylistFile : public TDAArchivo {
    private:
        // Atributos
        vector<Playlist*> playlists;
        int sizeNombre = 40, sizeCodigo = 4;
    public:
        // Constructores
        PlaylistFile() {}
        PlaylistFile(string fileName) : TDAArchivo(fileName) {}
        ~PlaylistFile() {
            for (int i = 0; i < playlists.size(); i++) {
                delete playlists[i];
            }
            playlists.clear();
        }

        // Getters y setters
        vector<Playlist*> getPlaylists() { return playlists; }
        void setPlaylists(vector<Playlist*> playlist) { this->playlists = playlist; }

        // Metodos de administracion
        bool agregarPlaylist(Playlist* playlist) {
            // Agrega una playlist validando que no se repita
            for (int i = 0; i < playlists.size(); i++)
                if (playlists[i]->equals(playlist))
                    return false;
            playlists.push_back(playlist);
            return true;
        }
        virtual bool Leer() {
            if (file.is_open()) {
                string buffer = "";
                // Leer en bloques
                getline(file, buffer);
                for (int i = 0; i < buffer.length(); i += sizeNombre+sizeCodigo) {
                    string  nombre = buffer.substr(i, sizeNombre),
                            codigo = buffer.substr(i+sizeNombre, sizeCodigo);
                    agregarPlaylist(new Playlist(nombre, stoi(codigo)));
                }
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
                for (int i = 0; i < playlists.size(); i++) {
                    // Recuperar los campos del registro
                    Playlist* playlist = dynamic_cast<Playlist*>(playlists[i]);
                    if (playlist) {
                        // Guardar nombre de la playlist
                        buffer.append(truncarDato(playlist->getNombre(), sizeNombre));

                        // Guardar codigo de la playlist
                        string datoTruncado = "", codigo = to_string(i); //playlist->getCodigo()
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