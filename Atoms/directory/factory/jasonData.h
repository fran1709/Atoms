#if !defined (_JASONDATA_)
#define _JASONDATA_

/**
 * @file jasonData.h
 * @author Francisco Javier Ovares Rojas.
 * @date 2021-11-16
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "../nlohmann/json.hpp" //Have to install library  

using namespace std;
using json = nlohmann::json;


// Prototypes of functions.
json readJsonAtoms();
void printJasonData(json pJson);
stack<Atom>* atomPrimals();


/**
 * @brief Read the information from the .json file of Atoms and load it into a Json file.
 * 
 * @return json 
 */
json readJsonAtoms() {

    std::ifstream jasonF("directory/files/atoms.json");
    json atomsData;
    jasonF >> atomsData;
    //printJasonData(atomsData);

    return atomsData;
}

/**
 * @brief Print the Json information.
 * 
 * @param pJson 
 */
void printJasonData(json pJson) {
    // iterate the array
    for (json::iterator it = pJson.begin(); it != pJson.end(); ++it) {
        cout << "Key: " <<it.key() << "\tValue: " << *it << '\n';
    }
}

/**
 * @brief Crea una pila de los atomos primordiales y devuele un puntero a la misma.
 * 
 * @return stack<Atom>* 
 */
stack<Atom>* atomPrimals() {

    json atomsData = readJsonAtoms();
    stack<Atom>* primalsAtoms = new stack<Atom>();

    for (json::iterator it = atomsData.begin(); it != atomsData.end(); ++it) {
        for (int j=0; j<it.value().at(1); j++) { // n cantidad de nodos
            Atom newAtom =  Atom(it.key());
            newAtom.setNombre(it.key());
            newAtom.setRelation(it.value().at(0));
            newAtom.setQuantity(it.value().at(1));
            newAtom.setIdDestination(it.value().at(2));
            primalsAtoms->push(*&newAtom);  
        }
        //cout << it.key() <<"  " << *it <<endl;
        //cout << newAtom->getNombre() <<" " << newAtom->getRelation()<<endl;
    }

    return primalsAtoms;
}


#endif // _JASONDATA_