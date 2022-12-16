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
    public:
        // Constructores
        PlaylistFile() {}
        PlaylistFile(string fileName) : TDAArchivo(fileName) {}

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
        Playlist* buscarPlaylist(string nombre) {
            for (int i = 0; i < playlists.size(); i++)
                if (!strcmp(playlists[i]->getNombre().data(), nombre.data()))
                    return playlists[i];
            return nullptr;
        }
        virtual bool Leer() {
            return true;
        }
        virtual bool Escribir() {
            return true;
        }
};