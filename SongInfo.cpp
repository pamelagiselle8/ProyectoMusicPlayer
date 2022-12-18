#include "Object.cpp"
#include <iostream>
using namespace std;

#pragma once
class SongInfo : public Object {
	protected:
		// Atributos
		string nombre, album, artista, genero, ruta;
		int codigo;
    public:
		// Constructores
		SongInfo() {}
		SongInfo(string nombre, string album, string artista, string genero, string ruta)
                : nombre(nombre), album(album), artista(artista), genero(genero), ruta(ruta) {}
		SongInfo(string nombre, string album, string artista,
				string genero, string ruta, int codigo)
                	: nombre(nombre), album(album), artista(artista),
					genero(genero), ruta(ruta), codigo(codigo) {}
		
		// Metodos de administracion
		virtual bool equals(Object* obj) {
			if (dynamic_cast<SongInfo*>(obj)) {
                if (!strcmp(this->ruta.data(), ((SongInfo*)obj)->getRuta().data()))
                    return true;
            }
            return false;
		}
		virtual string toString() {
			return nombre
				+ "\nAlbum: " + album
				+ "\nArtista: " + artista
				+ "\nGenero: " + genero
				+ "\nRuta: " + ruta + "\n";
		}

		// Getters y setters
		string getNombre() { return nombre; }
		string getDisco() { return album; }
		string getArtista() { return artista; }
		string getGenero() { return genero; }
		string getRuta() { return ruta; }
		void setNombre(string nombre) { this->nombre = nombre; }
		void setDisco(string album) { this->album = album; }
		void setArtista(string artista) { this->artista = artista; }
		void setGenero(string genero) { this->genero = genero; }
		void setRuta(string ruta) { this->ruta = ruta; }
		int getCodigo() { return codigo; }
        void setCodigo(int codigo) { this->codigo = codigo; }
};