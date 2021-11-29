#if !defined(_UPDATING_)
#define _UPDATING_

#include <stack>
#include "jasonData.h"
#include "MatrizAdyacencia.h"
#include "../clases/grafo.h"

// Prototypes
void craftUniverse(Grafo &pGrafo, int pQuantity);
void bigBang(Grafo &pGrafo, int pQuantity, vector<NodoGrafo*> pNodos, int** matrix);
void reproduction(Grafo &pGrafo, vector<NodoGrafo*> pNodos, int** matrix);

/**
 * @brief Creación inicial del grafo.
 * 
 * @param pGrafo 
 * @param pQuantity
 */
void craftUniverse(Grafo &pGrafo, int pQuantity) {
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
    int cont = 0;
    for (std::vector<NodoGrafo*>::iterator current = nodos.begin() ; current != nodos.end(); ++current) {
        int weight = rand() % 25 + 1; 
        int weight2 = rand() % 25 + 1; 
        int weight3 = rand() % 25 + 1;
        NodoGrafo* actual = (*current);
        int idDest = rand() % 6; 
        int idDes2 = rand() % 6;
        int idDes3 = rand() % 6;
        cont = 0;
        cout << actual->getInfo()->getName()<<"--"<< actual->getInfo()->getId() <<endl;
        for (std::vector<NodoGrafo*>::iterator curre = nodos.begin() ; curre != nodos.end(); ++curre) {
            NodoGrafo* actu = (*curre);
            if (actual->getInfo()->getName().compare("Inti") == 0) {
                pGrafo.addArc(actual, actu, weight);
                break;
            } else {
                if (idDest == cont) {
                    pGrafo.addArc(actual, actu, weight);
                } else if (idDes2 == cont) {
                    pGrafo.addArc(actual, actu, weight2);
                } else if(idDes3 == cont ) {
                    pGrafo.addArc(actual, actu, weight3);
                }
            }
            cont++;
        }
    }

    //Imprimiendo
    // cout <<"Atomo: " <<first.getNombre() << "\tVinculo: " << first.getRelation() << endl;
    // cout <<"Atomo: " <<second.getNombre() << "\tVinculo: " << second.getRelation() << endl;
    // cout <<"Atomo: " <<third.getNombre() << "\tVinculo: " << third.getRelation() << endl;
    // cout <<endl;

    pGrafo.printCounters();

    // matriz adyacencia
    MatrixAdjacency matrix = MatrixAdjacency();
    matrix.updateMatriz(pGrafo);

    // dijkstra
    // for (int it=0; it < pGrafo.getSize(); it++) {
    //     pGrafo.dijkstra(matrix.getMatrix(),it);
    // }

    // big bang 
    bigBang(pGrafo, pQuantity, nodos, matrix.getMatrix());
    
}

/**
 * @brief Creación de n generaciones a partir del grafo creado inicialmente. 
 * 
 * @param pGrafo
 * @param pQuantity 
 * @param pMatrix
 */
void bigBang(Grafo &pGrafo, int pQuantity, vector<NodoGrafo*> pNodos, int** pMatrix) {
    for (int iter=0; iter<pQuantity; iter++) {
        reproduction(pGrafo, pNodos, pMatrix);
    }
}

/**
 * @brief Reproduce los atomos segun las reglas.
 * 
 * @param pGrafo 
 * @param pNodos
 * @param pMatrix
 */
void reproduction(Grafo &pGrafo, vector<NodoGrafo*> pNodos, int** pMatrix) {
    // variables necesarios
    int weightLonger;
    int weightShorter;
    NodoGrafo* node = NULL;
    NodoGrafo* node2 = NULL;
    vector<NodoGrafo*> atomosIguales;
    
    // selecciono uno
    int cont = 0;
    int randChoice = rand() % pNodos.size();
    node = pNodos.at(randChoice); 
    atomosIguales.push_back(node);

    // muestro cual es el nodo seleccionado
    // cout<<"nuevo"<<endl;
    // cout << node->getInfo()->getName()<<"->"<<node->getInfo()->getId()<<endl;

    // busco el nodo del mismo atomo mas cercano en sus arcos
    for (int iter=0; iter<pNodos.size(); iter++) {
        if(pNodos.at(iter)->getInfo()->getName().compare(node->getInfo()->getName())==0 && 
            pNodos.at(iter)->getInfo()->getId() != node->getInfo()->getId()) {
            node2 = pNodos.at(iter);
            atomosIguales.push_back(pNodos.at(iter));
            //cout << node2->getInfo()->getName()<<"->"<<node2->getInfo()->getId()<<endl;
        }
    }

    cout << "Nodos en lista"<<endl;
    for (std::vector<NodoGrafo*>::iterator current = atomosIguales.begin() ; current != atomosIguales.end(); ++current) {
        NodoGrafo* actual = (*current);
        cout << actual->getInfo()->getName() << "--" <<actual->getInfo()->getId()<<endl;
    }

    pGrafo.dijkstra(pMatrix, node->getInfo()->getId());
    vector<Arco*> caminos= pGrafo.getCamino();
    // tratando de leer el mismo camino
    cout<< "mismo camino"<<endl ;
    for (int i = 0; i < pNodos.size(); i++) {
        cout << i << "\t\t" << caminos.at(i)->getPeso() << endl;
    }
}

#endif // _UPDATING_