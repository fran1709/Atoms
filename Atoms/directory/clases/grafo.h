#ifndef _GRAFO_
#define _GRAFO_ 
#include <vector>
#include "NodoGrafo.h"
#include "INodo.h"
#include <map>
#include <queue>
#include "Arco.h"
#include <climits>
#include "Report.h"

using namespace std;

class Grafo {
    private:
        vector<NodoGrafo*> listaNodos;
        bool esDirigido = true;
        std::map<int,NodoGrafo*> hashNodos;
        vector<Arco*> caminos;
        // registro del universo.
        Report* registro = new Report();

        void resetNodes() {
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                actual->setProcesado(false);
                actual->setVisitado(false);
            }
        }

        NodoGrafo* findNotVisited() {
            NodoGrafo* result = nullptr;
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                if (!actual->getVisitado()) {
                    result = actual;
                    break;
                }
            }
            return result;
        }

    public:
        
        Grafo(bool pDirigido) {
            this->esDirigido =  pDirigido;
        }

        vector<Arco*> getCamino() {
            return this->caminos;
        }
        int getSize() {
            return this->listaNodos.size();
        }

         vector<NodoGrafo*> getNodos() {
            return this->listaNodos;
        }

        void addNode(INodo* pNodo) {
            NodoGrafo* nuevoNodo = new NodoGrafo(pNodo);
            this->listaNodos.push_back(nuevoNodo);
            hashNodos.insert(pair<int,NodoGrafo*>(pNodo->getId(),nuevoNodo));
        }

        void addArc(NodoGrafo* pOrigen, NodoGrafo* pDestino) {
            this->addArc(pOrigen, pDestino, 0);
        }

        void addArc(NodoGrafo* pOrigen, NodoGrafo* pDestino, int pPeso) {
            Arco* newArc = new Arco(pOrigen, pDestino, pPeso);

            pOrigen->addArc(newArc);
            if (!this->esDirigido) {
                Arco* reverseArc =  new Arco(pDestino, pOrigen , pPeso);
                pDestino->addArc(reverseArc);
            }
        }

        void addArc(INodo* pOrigen, INodo* pDestino) {
            this->addArc(pOrigen->getId(), pDestino->getId(), 0);
        }

        void addArc(INodo* pOrigen, INodo* pDestino, int pPeso) {
            this->addArc(pOrigen->getId(), pDestino->getId(), pPeso);
        }

        void addArc(int pOrigen, int pDestino) {
            this->addArc(pOrigen, pDestino, 0);
        }

        void addArc(int pOrigen, int pDestino, int pPeso) {
            this->addArc(this->getNodo(pOrigen), this->getNodo(pDestino), pPeso);
        }

        NodoGrafo* getNodo(int pId) { 
            return hashNodos.at(pId);
        }

        vector<INodo*> deepPath(INodo* pOrigen) {  //recorrido en profundidad
            vector<INodo*> result;
            stack<NodoGrafo*> nodosProcesados;
            int visitados = 0;

            resetNodes();

            NodoGrafo* puntoPartida = this->getNodo(pOrigen->getId());
            nodosProcesados.push(puntoPartida);
            puntoPartida->setProcesado(true);

            do {
                while (!nodosProcesados.empty()) {
                    NodoGrafo* actual = nodosProcesados.top();
                    nodosProcesados.pop();

                    actual->setVisitado(true);
                    visitados++;
                    result.push_back(actual->getInfo());

                    vector<Arco*> *adyacentes = actual->getArcs();

                    for (int indiceArcos=0; indiceArcos<adyacentes->size(); ++indiceArcos) {
                        Arco* arco = adyacentes->at(indiceArcos);
                        NodoGrafo* adyacente = (NodoGrafo*)arco->getDestino();
                        if (!adyacente->getProcesado()) {
                            nodosProcesados.push(adyacente);
                            adyacente->setProcesado(true);
                        }
                    }
                }

                if (visitados<this->getSize()) {
                    puntoPartida = this->findNotVisited();
                    nodosProcesados.push(puntoPartida);
                    puntoPartida->setProcesado(true);
                }
            } while (visitados<this->getSize());
            
            return result;
        } 

        vector<INodo*> broadPath(INodo* pOrigen) {
            vector<INodo*> result;
            queue<NodoGrafo*> nodosProcesados;
            int visitados = 0;
            
            resetNodes();

            NodoGrafo* puntoPartida = this->getNodo(pOrigen->getId());
            nodosProcesados.push(puntoPartida);
            puntoPartida->setProcesado(true);
            
            do {
                while (!nodosProcesados.empty()) {
                    NodoGrafo* actual = nodosProcesados.front();
                    nodosProcesados.pop();

                    actual->setVisitado(true);
                    visitados++;
                    result.push_back(actual->getInfo());

                    vector<Arco*> *adyacentes = actual->getArcs();

                    for (int indiceArcos=0; indiceArcos<adyacentes->size(); ++indiceArcos) {
                        Arco* arco = adyacentes->at(indiceArcos);
                        NodoGrafo* adyacente = (NodoGrafo*)arco->getDestino();
                        if (!adyacente->getProcesado()) {
                            nodosProcesados.push(adyacente);
                            adyacente->setProcesado(true);
                        }
                    }
                }

                if (visitados<this->getSize()) {
                    puntoPartida = this->findNotVisited();
                    nodosProcesados.push(puntoPartida);
                    puntoPartida->setProcesado(true);
                }
            } while (visitados<this->getSize()); 

            return result;
        }


        vector<INodo*> path(INodo* pOrigen, INodo* pDestino) { // debe retornar un camino, el primero que encuentre estre el nodo oriegn y destino
            // en caso de que no haya camino, result se retorna vacío
            vector<INodo*> result1 = deepPath(pOrigen);
            vector<INodo*> result2 = broadPath(pOrigen);
            bool isNodo = false;
            vector<INodo*> finalPath1;
            vector<INodo*> finalPath2;
            vector<INodo*> bestPath;

            for (std::vector<INodo*>::iterator current = result1.begin() ; current != result1.end(); ++current) {
                INodo* actual = (*current);
                finalPath1.push_back(actual);
                if (actual->getId() == pDestino->getId()) {
                    isNodo = true;
                    break;
                }
            }

            for (std::vector<INodo*>::iterator current = result2.begin() ; current != result2.end(); ++current) {
                INodo* actual = (*current);
                finalPath2.push_back(actual);
                if (actual->getId() == pDestino->getId()) {
                    isNodo = true;
                    break;
                }
            }

            if (finalPath1.size() < finalPath2.size()) {
                bestPath = finalPath1;
            }
            else {
                bestPath = finalPath2;
            }
            
            if (isNodo == false) {
                bestPath.clear();
            }

            return bestPath;
        }

        void printCounters() {
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                cout << actual->getInfo()->getId() << " tiene " << actual->getArcs()->size() << endl;
            }
        }

        int* getIds() {
            int ids[listaNodos.size()];
            int it = 0;
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                ids[it] = actual->getInfo()->getId();
                it++;
            }
            int *point = ids;
            return point;
        }

        Report* getRegistro() {
            return this->registro;
        }

        /**
         * @brief Find the path with the smallest weight value.
         * 
         * @param pDistance 
         * @param pVertex 
         * @return int 
         */
        int minDistance(int pDistance[], bool pVertex[]){
            int min = INT_MAX;
            int minIndex;
            for (int i = 0; i < this->getSize(); i++){
                if (pVertex[i] == false && pDistance[i] <= min){
                    min = pDistance[i], minIndex = i;
                }
            }
            return minIndex;
        }

        /**
         * @brief Show the created path.
         * 
         * @param pDistance 
         */
        void showPath(int pDistance[]){
            this->caminos.clear();
            cout << "Distancia mas corta de un nodo a todos." << endl;
            for (int i = 0; i < this->getSize(); i++) {
                cout << i << "\t\t" << pDistance[i] << endl;
                Arco* camino = new  Arco(i, pDistance[i]);
                //cout << camino->getOrigen() << camino->getPeso()<<endl;
                this->caminos.push_back(camino);
            }
        }

        /**
         * @brief Find and create the shortest paths to all nodes in a graph.
         * 
         * @param pMatrix 
         * @param pStart 
         */
        void dijkstra(int **pMatrix, int pStart){
            int size = this->getSize();
            int route[size];
            bool vertex[size];

            // sets all distances to infinity and sets all as unvisited = false
            for (int iter = 0; iter < size; iter++){
                route[iter] = INT_MAX;
                vertex[iter] = false;
            }

            // you define the distance to itself.
            route[pStart] = 0;

            // updates the arrays of the tour according to their weights and marks the nodes as visited.
            for (int iter = 0; iter < size - 1; iter++){
                int x = minDistance(route, vertex);
                vertex[x] = true;

                for (int p = 0; p < size; p++){
                    if (!vertex[p] && pMatrix[x][p] && route[x] != INT_MAX && route[x] + pMatrix[x][p] < route[p]) {    
                        route[p] = route[x] + pMatrix[x][p];
                    }
                }
            }
            // show the paths
            //showPath(route);
            this->caminos.clear();
            for (int i = 0; i < this->getSize(); i++) {
                Arco* camino = new  Arco(i, route[i]);
                //cout << camino->getOrigen() << camino->getPeso()<<endl;
                this->caminos.push_back(camino);
            }
        }
};

#endif