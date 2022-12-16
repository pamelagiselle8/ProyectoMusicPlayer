#include <iostream>
#include <vector>
#include "SongInfo.cpp"

#pragma once
class Playlist {
	protected:
        // Atributos
		string nombre;
        vector<SongInfo> canciones;
    public:
        // Constructores
		Playlist() {}

        // Getters y setters
		string getNombre() { return nombre; }
		void setNombre(string nombre) { this->nombre = nombre; }
		vector<SongInfo> getCanciones() { return canciones; }
		void setCanciones(vector<SongInfo> canciones) {
            this->canciones = canciones;
        }
};