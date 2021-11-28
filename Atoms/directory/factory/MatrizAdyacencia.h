#if !defined(_MatrixAdjacency_)
#define _MatrixAdjacency_

#include <iostream>
#include "../clases/grafo.h"

using namespace std;

/**
 * @author Francisco Javier Ovares Rojas
 */
class MatrixAdjacency {
    private:
		// geters & setters.
		std::map<int,int*> htNodos;
        int mSize = 0; 
        int **matrix;
		int cont = 0;
		// methods.
		void updateHashTable(Grafo &pGrafo);
		void updateWeights(Grafo &pGrafo);
		void defineMatrix(Grafo &pGrafo);
    public:
		/**
		 * @brief Construct a new Matriz Adyacencia object
		 */
        MatrixAdjacency();
		// methods.
        int getMSize();
        void setMSize(int pVertices);
		void updateMatriz(Grafo &pGrafo);
		int **getMatrix();
		void mostrarMatriz();
};

MatrixAdjacency::MatrixAdjacency(){
    ;
}

int MatrixAdjacency::getMSize() {
    return this->mSize;
}

int** MatrixAdjacency::getMatrix(){
	return this->matrix;
}

void MatrixAdjacency::setMSize(int pSize) {
    this->mSize = pSize;
}

/**
 * @brief Create and define the nxn matrix with 0 in all its spaces.
 * 
 * @param pGrafo 
 */
void MatrixAdjacency::defineMatrix(Grafo &pGrafo) {
	// Defining size of the array.
    this->mSize = pGrafo.getSize();
	
	// Process for creating the matrix matrix.
	this->matrix = new int*[this->mSize]; // matrix equals a new value of integer n.
	for (int i = 0; i <= mSize; i++) {
		this->matrix[i] = new int[mSize]; // matrix in position [i] is equal to a new integer n.
	}
	this->matrix[mSize][mSize]; // a matrix of size matrix [Size] [Size] is created, 
    							// which is a quadratic matrix of size mSize
	//Process for filling the matrix matrix with 0
	for (int f = 0; f < mSize; f++) { 
		for (int c = 0; c < mSize; c++) {
			matrix[f][c] = 0;
		}
	}
}

/**
 * @brief Load the hash table with the id as identifiers and the counter as value
 * 
 * @param pGrafo 
 */
void MatrixAdjacency::updateHashTable(Grafo &pGrafo) {
	// accedo a lista de nodos.
	vector<NodoGrafo*> nodos = pGrafo.getNodos();

	// agrega cada nodo al hash table con un indice numerico respectivo.
	cout << "Id\tPosicion en Matriz" <<endl;
	for (std::vector<NodoGrafo*>::iterator current = nodos.begin() ; current != nodos.end(); ++current) {
		int *newCont = new int(this->cont);	
		NodoGrafo* actual = (*current);
		int newId = actual->getInfo()->getId();
		cout <<newId  << "\t\t" << *newCont <<endl;
		this->htNodos.insert(pair<int,int*>(newId, newCont));
		this->cont++;
    }
	cout << endl;
}

/**
 * @brief Loads the weights of the nodes into their respective positions in the matrix
 * 
 * @param pGrafo 
 */
void MatrixAdjacency::updateWeights(Grafo &pGrafo) {
	// variables 
	vector<Arco*>* arcos;
	int primerId;
	int segundoId;
	int *fila;
	int *colum;
	int peso;

	// accedo a lista de nodos.
	vector<NodoGrafo*> nodos = pGrafo.getNodos();

	// recorro el vector y cargo la matriz
	for (std::vector<NodoGrafo*>::iterator current = nodos.begin() ; current != nodos.end(); ++current) {
		NodoGrafo* actual = (*current);
		primerId = actual->getInfo()->getId();
		fila = htNodos.at(primerId);
		//cout << *fila << endl;
		arcos = actual->getArcs();
		for (std::vector<Arco*>::iterator currentArc = arcos->begin() ; currentArc != arcos->end(); ++currentArc) {
			Arco* actualArc = (*currentArc);
			NodoGrafo* ady = (NodoGrafo*)actualArc->getDestino();
			segundoId = ady->getInfo()->getId();
			//cout << segundoId << endl;
			colum = htNodos.at(segundoId);
			peso = actualArc->getPeso();
			cout << *fila << "\t" << *colum << "\t"<< peso << endl;
			// actualizo la matriz ahora que poseo la fila y columna del peso
			this->matrix[*fila][*colum] = peso;
		}
    }
}

/**
 * @brief Update the array by creating it from 0
 * 
 * @param pGrafo 
 */
void MatrixAdjacency::updateMatriz(Grafo &pGrafo) {
	// I create the array of 0
	defineMatrix(pGrafo);

	// load the hash table
	updateHashTable(pGrafo);

	// I update the matrix with the weights.
	updateWeights(pGrafo);

	// I show the matrix
	mostrarMatriz();
}

/**
 * @brief Displays the adjacency matrix in console.
 * 
 */
void MatrixAdjacency::mostrarMatriz() {
	cout << endl;
	cout << endl;
	cout << "|--------------------------------------MATRIZ DE ADYACENCIA--------------------------------------|" << endl;
	cout << endl;
	// Process for sampling the adjacency matrix.
	for (int i = 0; i < this->mSize; i++) {
		for (int j = 0; j < this->mSize; j++) {
			cout << "|   " << this->matrix[i][j] << "   |";
		}
		cout << endl;
	}
}

#endif // _MatrixAdjacency_