#include <iostream>
#include <vector>
#include <stack>
#include "directory/clases/grafo.h"
#include "directory/clases/INodo.h"
#include "directory/clases/NodoGrafo.h"
#include "directory/clases/Arco.h"
#include "directory/clases/Atom.h"
#include "directory/factory/jasonData.h"
#include "directory/factory/updating.h"


//g++ main.cpp
//./a.exe
using namespace std;

int main() {
    // Identando el grafo.
    Grafo atomsGame(true);

    // solicitud de generaciones al usuario.
    int quantity;
    cout << "Cuántas generaciones desea ejecutar: ";
    cin >> quantity;

    // craft the universe.
    craftUniverse(atomsGame, quantity);
}