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
    Atom fourth = primalAtoms->top();
    primalAtoms->pop();
    Atom five = primalAtoms->top();
    primalAtoms->pop();
    Atom six = primalAtoms->top();
    primalAtoms->pop();

    // Agregamos los nodos al grafo.
    Atom allAtoms[] = {first, second, third, fourth, five, six};
    for(int i=0; i<6; i++) { // para cada nodo
        pGrafo.addNode(&allAtoms[i]);   
    }

    // Agregando arcos a los nodos
    vector<NodoGrafo*> nodos = pGrafo.getNodos();
    //pGrafo.addArc(&first, &third, 15);
    //pGrafo.addArc(&second, &first, 10);
     //pGrafo.addArc(&second, &third, 70);
    //pGrafo.addArc(&third, &second, 1);
    for (std::vector<NodoGrafo*>::iterator current = nodos.begin() ; current != nodos.end(); ++current) {
        int weight = rand() % 25 + 1; 
        int weight2 = rand() % 25 + 1;  
        NodoGrafo* actual = (*current);
        int idDest = rand() % 6; 
        int idDes2 = rand() % 6;
        int cont = 0;
        for (std::vector<NodoGrafo*>::iterator curre = nodos.begin() ; curre != nodos.end(); ++curre) {
            if (idDest == cont) {
                NodoGrafo* actu = (*curre);
                pGrafo.addArc(actual, actu, weight);
            } else if (idDes2 == cont) {
                NodoGrafo* actu = (*curre);
                pGrafo.addArc(actual, actu, weight2);
            }
            cont++;
        }
    }

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
    for (int it=0; it < pGrafo.getSize(); it++) {
        pGrafo.dijkstra(matrix.getMatrix(),it);
    }
    
}

#endif // _UPDATING_