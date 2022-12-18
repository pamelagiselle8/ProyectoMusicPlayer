#include <iostream>
#include <vector>
#include "Playlist.cpp"
#include "SongInfo.cpp"
#include "TDAArchivo.cpp"
using namespace std;

#pragma once
class SongxPlaylistFile : public TDAArchivo {
    private:
        // Atributos
        vector<Playlist*> playlists;
        vector<SongInfo*> canciones;
        int sizeCodigo = 4;
    public:
        // Constructores
        SongxPlaylistFile() {}
        SongxPlaylistFile(string fileName) : TDAArchivo(fileName) {}

        // Getters y setters
        vector<Playlist*> getPlaylists() { return playlists; }
        void setPlaylists(vector<Playlist*> playlist) { this->playlists = playlist; }
        vector<SongInfo*> getCanciones() { return canciones; }
        void setCanciones(vector<SongInfo*> canciones) { this->canciones = canciones; }

        // Metodos de administracion
        virtual bool Leer() {
            if (file.is_open()) {
                string buffer = "";
                // Leer en bloques
                getline(file, buffer);
                for (int i = 0; i < buffer.length(); i += sizeCodigo*2) {
                    // Obtener el codigo de la playlist y el de la cancion
                    int codigoPlaylist = stoi(buffer.substr(i, sizeCodigo)),
                        codigoCancion = stoi(buffer.substr(i+sizeCodigo, sizeCodigo));

                    // Buscar playlist por codigo
                    for (int j = 0; j < playlists.size(); j++) {
                        Playlist* playlist = playlists.at(j);
                        if (codigoPlaylist == playlist->getCodigo()) {

                            // Buscar cancion por codigo
                            for (int k = 0; k < canciones.size(); k++){
                                SongInfo* cancion = canciones.at(k);

                                // Agregar cancion a playlist
                                if (codigoCancion == cancion->getCodigo())
                                    playlist->agregarCancion(cancion);
                            }
                            
                        }
                    }
                }
            }
            return file.is_open();
        }

        // Metodo para rellenar codigo con ceros
        string truncarCodigo(int codigoPlaylist, int capacidad) {
            string codigoTruncado = "", codigo = to_string(codigoPlaylist);
            codigoTruncado.append(sizeCodigo - codigo.size(), '0');
            codigoTruncado.append(codigo);
            return codigoTruncado;
        }
        virtual bool Escribir() {
            if (file.is_open()) {
                string buffer = "";
                // Construir buffer
                for (int i = 0; i < playlists.size(); i++) {
                    // Recuperar los campos del registro
                    
                    Playlist* playlist = dynamic_cast<Playlist*>(playlists[i]);
                    if (playlist)
                        // Guardar codigo de la playlist
                        buffer.append(truncarCodigo(playlist->getCodigo(), sizeCodigo));

                    SongInfo* cancion = dynamic_cast<SongInfo*>(canciones[i]);
                    if (cancion)
                        // Guardar codigo de la cancion
                        buffer.append(truncarCodigo(cancion->getCodigo(), sizeCodigo));
                }
                // Escribir en el archivo
                file.write(buffer.data(), buffer.size());
            }
            return file.is_open();
        }
};