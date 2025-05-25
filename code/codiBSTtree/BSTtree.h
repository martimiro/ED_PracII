#ifndef BSTTREE_H
#define BSTTREE_H

#include "NODEtree.h"

#include <iostream>
#include <iterator>
#include <vector>
#include <list>

using namespace std;

template <class Key, class Value>  
class BSTtree { 
    public: 
        BSTtree(); 
        BSTtree(const BSTtree<Key, Value>& orig); 
        virtual ~BSTtree(); 
         
        bool empty() const; 
        int size() const; 
        int height() const; 
 
        NODEtree<Key,Value>* insert(const Key& k, const Value& value);  
        const vector<Value>& valuesOf(const Key& k) const; 
        void printPreorder() const;
        void printPreorder(const NODEtree<Key, Value>* n) const;
        void printInorder() const;
        void printInorder(const NODEtree<Key, Value>* n) const; 
        void printPostorder() const; 
        void printPostorder(const NODEtree<Key, Value>* n) const;
        void printSecondLargestKey() const;  
        void mirrorTree();  
        list<NODEtree<Key, Value>*> getLeafNodes() const;
 
    protected: 
        NODEtree<Key,Value>* root; 
        NODEtree<Key,Value>* search(const Key& k) const; 
 
    private: 
        int _size;

        /* Mètodes auxiliars definiu aquí els que necessiteu */
        void esborrarArbre (NODEtree<Key, Value>* node);
        NODEtree<Key, Value>* clonarNode(NODEtree<Key, Value>* node) const;
        void getFulles(NODEtree<Key, Value>* node, list<NODEtree<Key, Value>*>& fulles) const;
        Key getSecondLargestKey(NODEtree<Key, Value>* nodeAux1, NODEtree<Key, Value>* nodeAux2) const;
        void mirrorTreeAux(NODEtree<Key, Value>* root);
};

// Constructor
template <class Key, class Value> 
BSTtree <Key, Value>::BSTtree() {
    root = nullptr;
    _size = 0;
}

// Constructor còpia
template <class Key, class Value>
BSTtree <Key, Value>::BSTtree(const BSTtree<Key, Value>& orig) {
    root = nullptr;
    _size = 0;

    root = clonarNode(orig.root);
    _size = orig._size;
}

template <class Key, class Value>
NODEtree<Key, Value>* BSTtree<Key, Value>::clonarNode(NODEtree<Key, Value>* node) const{
    if (node == nullptr) {
        return nullptr;
    }

    NODEtree<Key, Value>* nouNode = new NODEtree<Key, Value>(node->getKey());
    
    const vector<Value>& values = node ->getValue();
    // El compilador diu: need typename
    // Si values es const, retorna un const_iterator
    typename vector<Value>::const_iterator it;

    for (it = values.begin(); it != values.end(); ++it) {
        nouNode -> insertValue(*it);
    }

    nouNode->setLeft(clonarNode(node->getLeft()));
    if (nouNode->getLeft() != nullptr) {
        nouNode->getLeft()->setParent(nouNode);
    }

    nouNode->setRight(clonarNode(node->getRight()));
    if (nouNode->getRight() != nullptr) {
        nouNode->getRight()->setParent(nouNode);
    } 

    return nouNode;
}

// Destructor
template <class Key, class Value>
BSTtree <Key, Value>::~BSTtree() {
    // Al imolementar el destructor de forma recursiva he volgut crear un mètode auxiliar perquè tot sigui més llegible
    esborrarArbre(root);
}

// Mètodes auxiliars
template <class Key, class Value>
void BSTtree<Key, Value>::esborrarArbre (NODEtree<Key, Value>* node) {
    if (node != nullptr) {
        esborrarArbre(node -> getLeft());
        esborrarArbre(node -> getRight());
        delete node;
    }
}

// Altres mètodes
template <class Key, class Value>
bool BSTtree <Key, Value>::empty() const {
    if (_size != 0) {
        return false;
    } else {
        return true;
    }
}

template <class Key, class Value>
int BSTtree <Key, Value>::size() const {
    return _size;
}

template <class Key, class Value>
int BSTtree <Key, Value>::height() const {
    if(root == nullptr) {
        return 0;
    } else {
        return root->height();
    }
}

template <class Key, class Value>
NODEtree<Key, Value>* BSTtree<Key, Value>::insert(const Key& key, const Value& value) {
    // Cas base (arbre buit)
    if (root == nullptr) {
        root = new NODEtree<Key, Value>(key);
        root -> insertValue(value);

        _size = _size + 1;
        return root;
    }

    NODEtree <Key, Value>* nodeActual = root; // Li assignem aquest valor per defecte
    NODEtree <Key, Value>* nodeAuxiliar = nullptr; // Valor per defecte

    while (nodeActual != nullptr) {
        // Cas on una 
        if (key == nodeActual->getKey()) {
            nodeActual -> insertValue(value);
            return nodeActual;
        // Cas més petit
        } else if (key < nodeActual -> getKey()) {
            nodeAuxiliar = nodeActual;
            nodeActual = nodeActual -> getLeft();
        // Cas més gran
        } else {
            nodeAuxiliar = nodeActual;
            nodeActual = nodeActual -> getRight();
        }
    }
    
    if (nodeActual == nullptr) {
        // Creem el nou node a partir del nodeActual i l'auxiliar
        NODEtree <Key, Value>* nouNode = new NODEtree<Key, Value>(key);
        nouNode -> insertValue(value);
        nouNode -> setParent(nodeAuxiliar);

        // Escollim fill dret o fill esquerra
        if (key < nodeAuxiliar -> getKey()) {
            nodeAuxiliar -> setLeft(nouNode);
        } else {
            nodeAuxiliar -> setRight(nouNode);
        }

        _size = _size + 1;
        return nouNode;
    }

    return nullptr;
}

template <class Key, class Value>
const vector<Value>& BSTtree<Key, Value>::valuesOf(const Key& k) const {
    // Hem de buscar el valor per tot l'arbre, per tant el cas base (que el node sigui nullptr l'haurem de deixar pel final).

    // Creem un node auxiliar on recorrerem l'arbre amb aquest
    NODEtree <Key, Value>* nodeAux = root;

    while (nodeAux != nullptr) {
        if (nodeAux->getKey() == k) {
            return nodeAux->getValue();
        } else if (nodeAux->getKey() > k) {
            nodeAux =  nodeAux->getLeft();
        } else if (nodeAux->getKey() < k) {
            nodeAux = nodeAux -> getRight();
        }
    }

    cout << "No s'ha trobat la key" << endl;
    /*
    Com que he de retornar un vector, en aquest cas retornaré un vector buit.
    Aquest ha de ser static per que després de l'execució de la funció no desapareixi
    */
    static vector<Value> vectorBuit;
    return vectorBuit;
}

template <class Key, class Value>
void BSTtree<Key, Value>::printPreorder() const {
    printPreorder(root);
}

template <class Key, class Value>
void BSTtree<Key, Value>::printPreorder(const NODEtree<Key,Value>* n) const {
    if (n == nullptr) {
        return;
    }
    cout << n->getKey() << ", ";
    printPreorder(n->getLeft());
    printPreorder(n->getRight());
}

template <class Key, class Value>
void BSTtree<Key, Value>::printPostorder() const {
    printPostorder(root);
}

template <class Key, class Value>
void BSTtree<Key, Value> :: printPostorder(const NODEtree<Key, Value>* n) const {
    if (n == nullptr){
        return;
    }
    printPostorder(n->getLeft());
    printPostorder(n->getRight());
    cout << n->getKey() << ", ";
}

template <class Key, class Value>
void BSTtree<Key, Value>::printInorder() const {
    printInorder(root);
}

template <class Key, class Value>
void BSTtree<Key, Value> :: printInorder(const NODEtree<Key, Value>* n) const {
    if (n == nullptr){
        return;
    }
    printInorder(n->getLeft());
    cout << n->getKey() << ", ";
    printInorder(n->getRight());
}

template <class Key, class Value>
list<NODEtree<Key, Value>*> BSTtree<Key, Value>::getLeafNodes() const {
    list<NODEtree<Key, Value>*> fulles;
    getFulles(root, fulles);
    return fulles;
}

template <class Key, class Value>
void BSTtree<Key, Value>::getFulles(NODEtree<Key, Value>* node, list<NODEtree<Key, Value>*>& fulles) const {
    // Cas base (arbre buit)
    if (node == nullptr) {
        return;
    }

    if (node -> getLeft() == nullptr && node -> getRight() == nullptr){
        fulles.push_back(node);
    } else {
        getFulles(node ->getLeft(), fulles);
        getFulles(node -> getRight(), fulles);
    }
}

template <class Key, class Value>
void BSTtree<Key, Value>::printSecondLargestKey() const {
    if (root == nullptr || root -> getLeft() == nullptr && root -> getRight() == nullptr) {
        cout << "No hi ha segon node més gran." << endl;
        return;
    } else {
        NODEtree<Key, Value>* nodeAux1 = root;
        NODEtree<Key, Value>* nodeAux2 = nullptr;

        Key secondLargestKey = getSecondLargestKey(nodeAux1, nodeAux2);

        cout << "El segon node més gran és: " << secondLargestKey << endl;
    }
}

template <class Key, class Value>
Key BSTtree<Key, Value>::getSecondLargestKey(NODEtree<Key, Value>* nodeAux1, NODEtree<Key, Value>* nodeAux2) const{
    // Cas base
    if (nodeAux1 == nullptr) {
        return Key();
    }

    if (nodeAux1 -> getRight() == nullptr) {
        return nodeAux2 -> getKey();
    } 

    if (nodeAux1 -> getRight() -> getLeft() != nullptr || nodeAux1 -> getRight() -> getRight() != nullptr) {
        return getSecondLargestKey(nodeAux1 -> getRight(), nodeAux1);
    }

    return nodeAux1 -> getKey();
}

template <class Key, class Value>
void BSTtree<Key, Value>::mirrorTree() {
    mirrorTreeAux(root);
}

template <class Key, class Value>
void BSTtree<Key, Value>::mirrorTreeAux(NODEtree<Key, Value>* root) {
    // Cas base (arbre buit)
    if (root == nullptr) {
        return;
    }

    // Fem un intercanvi de variables usant un node auxiliar
    NODEtree<Key, Value>* nodeAux = root -> getLeft();
    root -> setLeft(root -> getRight());
    root -> setRight(nodeAux);

    mirrorTreeAux(root->getLeft());
    mirrorTreeAux(root->getRight());
}

template <class Key, class Value>
NODEtree<Key, Value>* BSTtree<Key, Value>::search(const Key& k) const {
    NODEtree<Key, Value>* nodeAux = root;

    while (nodeAux != nullptr) {
        if (nodeAux->getKey() == k) {
            return nodeAux;
        } else if (nodeAux->getKey() > k) {
            nodeAux = nodeAux ->getLeft();
        } else {
            nodeAux = nodeAux -> getRight();
        }
    }
    
    return nullptr;
}

#endif /* BSTTREE_H */