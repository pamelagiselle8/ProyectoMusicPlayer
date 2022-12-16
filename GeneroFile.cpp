#include <iostream>
#include <vector>
#include "Genero.cpp"
#include "TDAArchivo.cpp"
using namespace std;
// #include <boost/algorithm/string.hpp>
// using std::cout;
// using std::string;
// using std::endl;
// using namespace boost::algorithm;

#pragma once
class GeneroFile : public TDAArchivo {
    private:
        // Atributos
        int sizeNombre = 20;

    protected:
        // Atributos
        vector<Genero*> generos;

    public:
        // Constructores y destructor
        GeneroFile() {}
        GeneroFile(string fileName) : TDAArchivo(fileName) {}
        ~GeneroFile() {
            for (int i = 0; i < generos.size(); i++) {
                delete generos[i];
            }
            generos.clear();
        }
        vector<Genero*> getGeneros() { return generos; }

        // Metodos de administracion
        bool agregarGenero(Genero* genero) {
            // Agrega un genero cuidando no duplicar
            for (int i = 0; i < generos.size(); i++)
                if (generos[i]->equals(genero))
                    return false;
            generos.push_back(genero);
            return true;
        }

        bool eliminarGenero(Genero* genero) {
            string buffer = "";
            for (int i = 0; i < generos.size(); i++) {
                if (genero->equals(dynamic_cast<Genero*>(generos[i]))) {
                    // Marcar un genero como eliminado
                    buffer.append(sizeNombre, '$');
                    dynamic_cast<Genero*>(generos[i])->setNombre(buffer);
                }
            }
        }

        // bool modificarGenero(Genero* genero); // Modificar un genero


        virtual bool Leer() {
            if (file.is_open()) {
                string buffer = "";
                // Abrir en binario
                // Leer en bloques
                getline(file, buffer);
                for (int i = 0; i < buffer.length(); i += sizeNombre)
                    agregarGenero(new Genero(buffer.substr(i, sizeNombre)));
                // trim_right(buffer);
            }
            return file.is_open();
        }
        virtual bool Escribir() {
            if (file.is_open()) {
                string buffer = "";
                // Construir buffer
                for (int i = 0; i < generos.size(); i++) {
                    // Recuperar los campos del registro
                    Genero* genero = dynamic_cast<Genero*>(generos[i]);
                    if (genero) {
                        string dato = genero->getNombre();
                        // Rellenar el espacio no utilizado
                        string datoTruncado = dato.substr(0, sizeNombre);
                        datoTruncado.append(sizeNombre - datoTruncado.size(), ' ');
                        buffer.append(datoTruncado);
                    }
                }
                // Escribir en el archivo
                file.write(buffer.data(), buffer.size());
            }
            return file.is_open();
        }
};