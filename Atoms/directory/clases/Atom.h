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

        int getQuantity() {
            return this->quantity;
        }

        void setQuantity(int pQuantity) {
            this->quantity = pQuantity;
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

        int getIdDestination() {
            return this->idDestination;
        }

        void setIdDestination(int pId) {
            this->idDestination = pId;
        }

    private:
        string nombre;
        string relation;
        int quantity;
        int idDestination;
};

#endif  // _ATOM_