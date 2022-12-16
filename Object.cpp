#include <iostream>
using namespace std;

#pragma once
class Object {
    public:
        // Constructores
        Object() {}

        // Metodos de administracion
        virtual bool equals(Object*)=0;
		virtual string toString()=0;
};