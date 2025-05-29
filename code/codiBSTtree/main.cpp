#include "NODEtree.h"
#include "BSTtree.h"

#include <iostream>
#include <list>

using namespace std;

void mainExercici1(){ 
    BSTtree<int, int> tree1; 
    //int testKeys[] = {2, 0, 8, 45, 76, 5, 3, 40};  
    //int testValues[] = {5, 5, 1, 88, 99, 12, 9, 11}; 

    int testKeys[] = {10, 5, 3, 7, 15, 20};  
    int testValues[] = {1, 2, 3, 4, 5, 6}; 

    //int testKeys[] = {2, 1, 3};
    //int testValues[] = {1, 2, 3};
 
    for (int i = 0; i < 6 ; i++) {  // Canvio 8 per 3
        cout << "Inserta a l'arbre la key " << testKeys[i] << " amb valor " << 
testValues[i] << endl; 
        tree1.insert(testKeys[i], testValues[i]); 
    } 
     
    cout << "Preorder = ["; 
    tree1.printPreorder(); 
    cout << "]" << endl; 
    cout << "Inorder = ["; 
    tree1.printInorder(); 
    cout << "]" << endl; 
    cout << "Postorder = ["; 
    tree1.printPostorder(); 
    cout << "]" << endl; 
 
    tree1.printSecondLargestKey();  
    cout << "FULLES De l'arbre = ";  
    list<NODEtree<int,int> *> fulles = tree1.getLeafNodes();  
    cout << "{ " ; 
    for(NODEtree<int, int>* n: fulles){ 
         cout << n->getKey() << " "; 
    } 
    cout << "}" << endl<< endl; 

    vector<NODEtree<int, int>*> llista = tree1.printKeysAtLevel(1);
    cout << "Metode prova I: ";
    cout << " { ";
    for (vector<NODEtree<int, int>*>::iterator it = llista.begin(); it != llista.end(); ++it) {
        cout << (*it)->getKey() << " ";
    }
    cout << "}" << endl;
    BSTtree<int, int> tree2(tree1);

    int quantitat = tree1.countFullNodesAtLevel(2);
    cout << quantitat << endl;
    int quantitat2 = tree1.countFullNodesAtLevel(1);
    cout << quantitat2 << endl;
}

int main() {
    mainExercici1();

    return 0;
}