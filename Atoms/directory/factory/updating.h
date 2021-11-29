#if !defined(_UPDATING_)
#define _UPDATING_

#include <stack>
#include "jasonData.h"
#include "MatrizAdyacencia.h"
#include "../clases/grafo.h"

// Prototypes
void craftUniverse(Grafo &pGrafo, int pQuantity);
void bigBang(Grafo &pGrafo, int pQuantity, vector<NodoGrafo*> pNodos);
void reproduction(Grafo &pGrafo, vector<NodoGrafo*> pNodos);

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
        cout << actual->getInfo()->getName()<<endl;
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

    // big bang 
    bigBang(pGrafo, pQuantity, nodos);
    
}

/**
 * @brief Creación de n generaciones a partir del grafo creado inicialmente. 
 * 
 * @param pGrafo
 * @param pQuantity 
 */
void bigBang(Grafo &pGrafo, int pQuantity, vector<NodoGrafo*> pNodos) {
    for (int iter=0; iter<pQuantity; iter++) {
        reproduction(pGrafo, pNodos);
    }
}

/**
 * @brief Reproduce los atomos segun las reglas.
 * 
 * @param pGrafo 
 * @param pNodos
 */
int getShorter(NodoGrafo * node1, NodoGrafo * node2){ //recibe 2 nodos y retorna el tamano del arco mas pequeno de los 2
    vector<Arco*> * adyacentes = node1->getArcs();
    Arco * primerArco = adyacentes->at(0);
    int peso = primerArco->getPeso();
    for (std::vector<Arco*>::iterator current = adyacentes->begin() ; current != adyacentes->end(); ++current){
        cout << "Peso iteracion: " << peso << endl;
        Arco * actual = (*current);
        int pesoActual = actual->getPeso();
        if (pesoActual < peso){
            peso = pesoActual;
        }
    }
    vector<Arco*> * adyacentes2 = node2->getArcs();
    for (std::vector<Arco*>::iterator current = adyacentes2->begin() ; current != adyacentes2->end(); ++current){
        cout << "Peso iteracion: " << peso << endl;
        Arco * actual = (*current);
        int pesoActual = actual->getPeso();
        if (pesoActual < peso){
            peso = pesoActual;
        }
    }
    return peso;
}

INodo * getClosestSame(NodoGrafo * inicio, Grafo &pGrafo){//recibe un nodo y retorna el nodo del mismo tipo mas cercano a el
    vector<INodo*> deepPath = pGrafo.deepPath(inicio->getInfo());
    string nombreBuscado = inicio->getInfo()->getName();
    for (std::vector<INodo*>::iterator current = deepPath.begin(); current != deepPath.end(); current++){
        INodo * actual = (*current);
        if (actual->getName() == nombreBuscado){
            return actual;
        }
    }
}

void reproduction(Grafo &pGrafo, vector<NodoGrafo*> pNodos) {
    // variables necesarios
    int weightLonger;
    int weightShorter;
    NodoGrafo* node = NULL;
    
    // selecciono uno
    int cont = 0;
    int randChoice = rand() % pNodos.size();
    node = pNodos.at(randChoice); 

    // muestro cual es el nodo seleccionado
    cout << node->getInfo()->getName()<<endl;

    // busco el nodo del mismo atomo mas cercano
    

    // buscar el nodo mas cercano de cualquier tipo
    getShorter(pGrafo.getNodo(0),pGrafo.getNodo(3));
}

#endif // _UPDATING_