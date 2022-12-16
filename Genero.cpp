#include <iostream>
using namespace std;
#include "Object.cpp"

#pragma once
class Genero : public Object {
    private:
        // Atributos
        string nombre = ""; // Limitado a 20 bytes
    public:
        // Constructores y destructor
        Genero() {}
        Genero(string nombre) : nombre(nombre) {}
        ~Genero() {}

        // Getters y setters
        string getNombre() {
            return nombre;
        }
        void setNombre(string nombre) {
            this->nombre = nombre;
        }

        // Metodos de administracion
        bool equals(Object* obj) {
            if (dynamic_cast<Genero*>(obj))
                cout << "\nthis nombre: ->" << this->nombre << "<-";
                cout << "\nnombre obj: ->" << dynamic_cast<Genero*>(obj)->getNombre() << "<-";
                return !strcmp(this->nombre.data(), dynamic_cast<Genero*>(obj)->getNombre().data());
                // return this->nombre == dynamic_cast<Genero*>(obj)->getNombre();
            return false;
        }
        string toString() {
            return nombre;
        }
        
};

