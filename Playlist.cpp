#include <iostream>
#include <vector>
#include "SongInfo.cpp"

#pragma once
class Playlist : public Object {
	protected:
        // Atributos
		string nombre;
        vector<SongInfo*> canciones;
    public:
        // Constructores y destructor
		Playlist() {}
        Playlist(string nombre) : nombre(nombre) {}
        ~Playlist() {
            for (int i = 0; i < canciones.size(); i++) {
                delete canciones[i];
            }
            canciones.clear();
        }

        // Getters y setters
		string getNombre() { return nombre; }
		void setNombre(string nombre) { this->nombre = nombre; }
		vector<SongInfo*> getCanciones() { return canciones; }
		void setCanciones(vector<SongInfo*> canciones) {
            this->canciones = canciones;
        }

        // Metodos de administracion
        bool agregarCancion(SongInfo* cancion) {
            // Agrega una cancion validando que no se repita
            for (int i = 0; i < canciones.size(); i++)
                if (canciones[i]->equals(cancion))
                    return false;
            canciones.push_back(cancion);
            return true;
        }
        bool equals(Object* obj) {
            if (dynamic_cast<Playlist*>(obj)) {
                if (!strcmp(this->nombre.data(), dynamic_cast<Playlist*>(obj)->getNombre().data())) {
                    for (int i = 0; i < canciones.size(); i++)
                        if (!canciones[i]->equals(((Playlist*)obj)->getCanciones()[i]))
                            return false;
                    return true;
                }
            }
            return false;
        }
        string toString() {
            return nombre;
        }
};