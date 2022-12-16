#include "Object.cpp"
#include <iostream>
using namespace std;

#pragma once
class SongInfo : public Object {
	protected:
		// Atributos
		string nombre;
		string disco;
		string artista;
		string ruta;
    public:
		// Constructores
		SongInfo() {}
		SongInfo(string nombre, string disco, string artista, string ruta)
                : nombre(nombre), disco(disco), artista(artista), ruta(ruta) {}
		
		// Metodos de administracion
		virtual bool equals(Object* obj) { return this == obj; }
		virtual string toString() { return ""; }

		// Getters y setters
		string getNombre() { return nombre; }
		string getDisco() { return disco; }
		string getArtista() { return artista; }
		string getRuta() { return ruta; }
		void setNombre(string nombre) { this->nombre = nombre; }
		void setDisco(string disco) { this->disco = disco; }
		void setArtista(string artista) { this->artista = artista; }
		void setRuta(string ruta) { this->ruta = ruta; }
	
};