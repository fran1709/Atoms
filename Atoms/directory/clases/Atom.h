#ifndef _ATOM_
#define _ATOM_ 

#include <iostream>
#include "INodo.h"

using namespace std;

static int cont = 0;
class Atom: public INodo {
    public:
        Atom() {
            this->setId(cont++);
        }

        string getNombre() {
            return this->nombre;
        }

        void setNombre(string pNombre) {
            this->nombre = pNombre;
        }

        string getRelation() {
            return this->relation;
        }

        void setRelation(string pRelation) {
            this->relation = pRelation;
        }

    private:
        string nombre;
        string relation;
};

#endif  // _ATOM_