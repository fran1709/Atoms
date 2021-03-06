#if !defined(_UPDATING_)
#define _UPDATING_

#include <stack>
#include "jasonData.h"
#include "MatrizAdyacencia.h"

// Prototypes
void craftUniverse(Grafo *&pGrafo, int pQuantity);
void bigBang(Grafo *&pGrafo, int pQuantity, MatrixAdjacency* pMatrix);
void reproduction(Grafo *&pGrafo, MatrixAdjacency* pMatrix);

/**
 * @brief Creación inicial del grafo.
 * 
 * @param pGrafo 
 * @param pQuantity
 */
void craftUniverse(Grafo *&pGrafo, int pQuantity) {
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
        pGrafo->addNode(&allAtoms[i]);  
        pGrafo->getRegistro()->addAtomos(1);
    }

    // Agregando arcos a los nodos
    vector<NodoGrafo*> nodos = pGrafo->getNodos();
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
                pGrafo->addArc(actual, actu, weight);
                break;
            } else {
                if (idDest == cont) {
                    pGrafo->addArc(actual, actu, weight);
                } else if (idDes2 == cont) {
                    pGrafo->addArc(actual, actu, weight2);
                } else if(idDes3 == cont ) {
                    pGrafo->addArc(actual, actu, weight3);
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

    pGrafo->printCounters();

    // matriz adyacencia
    MatrixAdjacency *matrix = new MatrixAdjacency();
    matrix->updateMatriz(pGrafo);

    // dijkstra
    // for (int it=0; it < pGrafo.getSize(); it++) {
    //     pGrafo.dijkstra(matrix.getMatrix(),it);
    // }

    // big bang 
    bigBang(pGrafo, pQuantity, matrix);  
}

/**
 * @brief Creación de n generaciones a partir del grafo creado inicialmente. 
 * 
 * @param pGrafo
 * @param pQuantity 
 * @param pMatrix
 */
void bigBang(Grafo *&pGrafo, int pQuantity, MatrixAdjacency* pMatrix) {
    for (int iter=0; iter<pQuantity; iter++) {
        reproduction(pGrafo, pMatrix);
    }
    //pMatrix->updateMatriz(*&pGrafo);
    cout<<"Cantidad de Atomos: " <<pGrafo->getRegistro()->getCantAtomos() <<endl;
    // MatrixAdjacency two = MatrixAdjacency();
    // two.updateMatriz(pGrafo);
    //pMatrix->updateMatriz(pGrafo);

}

/**
 * @brief Reproduce los atomos segun las reglas.
 * 
 * @param pGrafo 
 * @param pNodos
 * @param pMatrix
 */
void reproduction(Grafo *&pGrafo, MatrixAdjacency* pMatrix) {
    // variables necesarios
    int weightLonger;
    int weightShorter;
    NodoGrafo* node = NULL;
    NodoGrafo* node2 = NULL;
    vector<NodoGrafo*> atomosIguales;
    
    // selecciono uno
    //int cont = 0;
    int size = pGrafo->getNodos().size();
    //int randChoice = rand() % size;
    //node = pGrafo->getNodos().at(randChoice);
    //atomosIguales.push_back(node);

    // muestro cual es el nodo seleccionado
    // cout<<"nuevo"<<endl;
    // cout << node->getInfo()->getName()<<"->"<<node->getInfo()->getId()<<endl;
    for (int itera=0; itera<size; itera++) {
        atomosIguales.clear();
        node = pGrafo->getNodos().at(itera);
        atomosIguales.push_back(node);
        // busco nodos del mismo tipo
        
        for (int iter=0; iter<size; iter++) {
            if(pGrafo->getNodos().at(iter)->getInfo()->getName().compare(node->getInfo()->getName())==0 && 
                pGrafo->getNodos().at(iter)->getInfo()->getId() != node->getInfo()->getId()) {
                node2 = pGrafo->getNodos().at(iter);
                atomosIguales.push_back(pGrafo->getNodos().at(iter));
                //cout << node2->getInfo()->getName()<<"->"<<node2->getInfo()->getId()<<endl;
            }
        }

        cout << "Nodos en lista"<<endl;
        for (std::vector<NodoGrafo*>::iterator current = atomosIguales.begin() ; current != atomosIguales.end(); ++current) {
            NodoGrafo* actual = (*current);
            cout << actual->getInfo()->getName() << "--" <<actual->getInfo()->getId()<<endl;
        }

        //obtencio de caminos dijkstra a todos los nodos.
        pGrafo->dijkstra(pMatrix->getMatrix(), node->getInfo()->getId());
        vector<Arco*> caminos= pGrafo->getCamino();
        // tratando de leer el mismo camino
        //cout<< "mismo camino"<<endl;
        for (int i = 0; i < size; i++) {
            //cout << i << "\t\t" << caminos.at(i)->getPeso() << endl;
            if(i == node2->getInfo()->getId() && (caminos.at(i)->getPeso()<25 || caminos.at(i)->getPeso()<INT_MAX)){ 
                // si hay camino se crea un nuevo arco entre ellos
                pGrafo->addArc(node, node2, caminos.at(i)->getPeso());
                // se reproducen
                Atom* newAtom = new Atom(node->getInfo()->getName());
                newAtom->setNombre(node->getInfo()->getName());
                pGrafo->addNode(newAtom);
                // se direcciona al arco padre
                pGrafo->addArc(newAtom, node->getInfo(), caminos.at(i)->getPeso());
                //pMatrix->updateMatriz(pGrafo);
                pGrafo->getRegistro()->addAtomos(1);
                // se crea otra matriz y se sobre escribe en la anterior
                cout << "Nuevo Atomo creado"<<endl;
                MatrixAdjacency *matrix = new MatrixAdjacency();
                matrix->updateMatriz(pGrafo);
                pMatrix = matrix;
            }
        }

        pGrafo->printCounters();
        //pGrafo->dijkstra(pMatrix->getMatrix(), node->getInfo()->getId());
    }
}

#endif // _UPDATING_