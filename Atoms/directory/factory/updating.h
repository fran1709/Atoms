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

    // Agregando arcos a los nodos
    pGrafo.addArc(first, third);
    pGrafo.addArc(second, first);
    pGrafo.addArc(third, second);

    //Imprimiendo
    cout <<"Atomo: " <<first->getNombre() << "\tVinculo: " << first->getRelation() << endl;
    cout <<"Atomo: " <<second->getNombre() << "\tVinculo: " << second->getRelation() << endl;
    cout <<"Atomo: " <<third->getNombre() << "\tVinculo: " << third->getRelation() << endl;
    cout <<endl;

    //pGrafo.printCounters();
}

#endif // _UPDATING_
