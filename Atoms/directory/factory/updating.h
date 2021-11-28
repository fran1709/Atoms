#if !defined(_UPDATING_)
#define _UPDATING_

#include <stack>
#include "jasonData.h"
#include "MatrizAdyacencia.h"
#include "../clases/grafo.h"

void updateGrafo(Grafo &pGrafo) {
    // Identando los atomos primordiales.
    stack<Atom>* primalAtoms = atomPrimals();
    Atom first = primalAtoms->top();
    primalAtoms->pop();
    Atom second = primalAtoms->top();
    primalAtoms->pop();
    Atom third = primalAtoms->top();
    primalAtoms->pop();

    // Agregamos los nodos al grafo.
    Atom allAtoms[] = {first, second, third};
    for(int i=0; i<3; i++) {
        pGrafo.addNode(&allAtoms[i]);
    }

    // Agregando arcos a los nodos
    pGrafo.addArc(&first, &third, 25);
    pGrafo.addArc(&second, &first, 50);
    //pGrafo.addArc(&second, &third, 70);
    pGrafo.addArc(&third, &second, 100);

    //Imprimiendo
    cout <<"Atomo: " <<first.getNombre() << "\tVinculo: " << first.getRelation() << endl;
    cout <<"Atomo: " <<second.getNombre() << "\tVinculo: " << second.getRelation() << endl;
    cout <<"Atomo: " <<third.getNombre() << "\tVinculo: " << third.getRelation() << endl;
    cout <<endl;

    pGrafo.printCounters();
    // Imprimiendo DeepPath
    vector<INodo*> result = pGrafo.deepPath(&first);
    cout << "Imprimiendo DeepPath." << endl;
    for(int i=0; i<result.size(); i++) {
        Atom *city = (Atom*)(void*)result[i];
        cout << city->getId() << " -> " << city->getNombre() << endl;
    }
    cout << endl;

    // matriz adyacencia
    MatrixAdjacency matrix = MatrixAdjacency();
    matrix.updateMatriz(pGrafo);

    // dijkstra
    pGrafo.dijkstra(matrix.getMatrix(),0);
}

#endif // _UPDATING_