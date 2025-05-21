#ifndef BSTTREE_H
#define BSTTREE_H

#include "NODEtree.h"

#include <iostream>

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
        void printPreorder(const NODEtree<Key,Value>* n = nullptr) const; 
        void printInorder(const NODEtree<Key,Value>* n = nullptr) const; 
        void printPostorder(const NODEtree<Key,Value>* n = nullptr) const; 
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
    
}

// Destructor
template <class Key, class Value>
BSTtree <Key, Value>::~BSTtree() {
    // Al imolementar el destructor de forma recursiva he volgut crear un mètode auxiliar perquè tot sigui més llegible
    esborrarArbre(root);
}

// Mètodes auxiliars
template <class Key, class Value>
void esborrarArbre (NODEtree<Key, Value>* node) {
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

        size = size + 1;
        return root;
    }

    NODEtree <Key, Value>* nodeActual = root; // Li assignem aquest valor per defecte
    NODEtree <Key, Value>* nodeAuxiliar = nullptr; // Valor per defecte

    while (nodeActual != nullptr) {
        // Cas on una 
        if (key == current->getKey()) {
            current -> insertValue(value);
            return current;
        // Cas més petit
        } else if (key < current -> getKey()) {
            nodeAuxiliar = nodeActual;
            nodeActual = nodeActual -> getLeft();
        // Cas més gran
        } else {
            nodeAuxiliar = nodeActual;
            nodeActual = nodeActual -> getRight();
        }
    }
    
    // Creem el nou node a partir del nodeActual i l'auxiliar
    NODEtree <Value, Key>* nouNode = new NODEtree<Value, Key>(key)
    nouNode -> setValue(value);
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

#endif /* BSTTREE_H */