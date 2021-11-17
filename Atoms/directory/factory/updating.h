#if !defined(_UPDATING_)
#define _UPDATING_

#include <stack>
#include "jasonData.h"

void updateGrafo(Grafo pGrafo) {
    // Identando los atomos primordiales.
    stack<Atom>* primalAtoms = atomPrimals();
    Atom *first = &primalAtoms->top();
    primalAtoms->pop();
    Atom *second = &primalAtoms->top();
    primalAtoms->pop();
    Atom *third = &primalAtoms->top();
    primalAtoms->pop();

    // Agregamos los nodos al grafo.
    pGrafo.addNode(first);
    pGrafo.addNode(second);
    pGrafo.addNode(third);

    //cout <<first->getNombre();
}

#endif // _UPDATING_
