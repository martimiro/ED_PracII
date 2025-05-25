#ifndef BSTTREE_H
#define BSTTREE_H

#include "NODEtree.h" 

#include <iostream>
#include <iterator>
#include <vector>
#include <list>

using namespace std;

template <class Key, class Peli>  
class BSTtree { 
public: 
    BSTtree(); 
    BSTtree(const BSTtree<Key, Peli>& orig); 
    virtual ~BSTtree(); 
     
    bool empty() const; 
    int size() const; 
    int height() const; 

    NODEtree<Key, Peli>* insert(const Key& k, const Peli& value);  
    const vector<Peli>& valuesOf(const Key& k) const; 
    void printPreorder() const;
    void printPreorder(const NODEtree<Key, Peli>* n) const;
    void printInorder() const;
    void printInorder(const NODEtree<Key, Peli>* n) const; 
    void printPostorder() const; 
    void printPostorder(const NODEtree<Key, Peli>* n) const;
    void printSecondLargestKey() const;  
    void mirrorTree();  
    list<NODEtree<Key, Peli>*> getLeafNodes() const;

protected: 
    NODEtree<Key, Peli>* root; 
    NODEtree<Key, Peli>* search(const Key& k) const; 

private: 
    int _size;

    void esborrarArbre (NODEtree<Key, Peli>* node);
    NODEtree<Key, Peli>* clonarNode(NODEtree<Key, Peli>* node) const;
    void getFulles(NODEtree<Key, Peli>* node, list<NODEtree<Key, Peli>*>& fulles) const;
    Key getSecondLargestKey(NODEtree<Key, Peli>* nodeAux1, NODEtree<Key, Peli>* nodeAux2) const;
    void mirrorTreeAux(NODEtree<Key, Peli>* root);
};

// Constructor
template <class Key, class Peli> 
BSTtree<Key, Peli>::BSTtree() {
    root = nullptr;
    _size = 0;
}

// Constructor còpia
template <class Key, class Peli>  
BSTtree<Key, Peli>::BSTtree(const BSTtree<Key, Peli>& orig) {
    root = nullptr;
    _size = 0;

    root = clonarNode(orig.root);
    _size = orig._size;
}

template <class Key, class Peli>
NODEtree<Key, Peli>* BSTtree<Key, Peli>::clonarNode(NODEtree<Key, Peli>* node) const{
    if (node == nullptr) {
        return nullptr;
    }

    NODEtree<Key, Peli>* nouNode = new NODEtree<Key, Peli>(node->getKey());
    
    const vector<Peli>& values = node->getValue();
    typename vector<Peli>::const_iterator it;

    for (it = values.begin(); it != values.end(); ++it) {
        nouNode->insertValue(*it);
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
template <class Key, class Peli>
BSTtree<Key, Peli>::~BSTtree() {
    esborrarArbre(root);
}

// Mètodes auxiliars
template <class Key, class Peli> 
void BSTtree<Key, Peli>::esborrarArbre(NODEtree<Key, Peli>* node) {
    if (node != nullptr) {
        esborrarArbre(node->getLeft());
        esborrarArbre(node->getRight());
        delete node;
    }
}

// Altres mètodes
template <class Key, class Peli> 
bool BSTtree<Key, Peli>::empty() const {
    return _size == 0;
}

template <class Key, class Peli>
int BSTtree<Key, Peli>::size() const {
    return _size;
}

template <class Key, class Peli>
int BSTtree<Key, Peli>::height() const {
    return root == nullptr ? 0 : root->height();
}

template <class Key, class Peli>
NODEtree<Key, Peli>* BSTtree<Key, Peli>::insert(const Key& key, const Peli& value) {
    if (root == nullptr) {
        root = new NODEtree<Key, Peli>(key);
        root->insertValue(value);
        ++_size;
        return root;
    }

    NODEtree<Key, Peli>* nodeActual = root;
    NODEtree<Key, Peli>* nodeAuxiliar = nullptr;

    while (nodeActual != nullptr) {
        if (key == nodeActual->getKey()) {
            nodeActual->insertValue(value);
            return nodeActual;
        } else if (key < nodeActual->getKey()) {
            nodeAuxiliar = nodeActual;
            nodeActual = nodeActual->getLeft();
        } else {
            nodeAuxiliar = nodeActual;
            nodeActual = nodeActual->getRight();
        }
    }

    NODEtree<Key, Peli>* nouNode = new NODEtree<Key, Peli>(key);
    nouNode->insertValue(value);
    nouNode->setParent(nodeAuxiliar);

    if (key < nodeAuxiliar->getKey()) {
        nodeAuxiliar->setLeft(nouNode);
    } else {
        nodeAuxiliar->setRight(nouNode);
    }

    ++_size;
    return nouNode;
}

template <class Key, class Peli>
const vector<Peli>& BSTtree<Key, Peli>::valuesOf(const Key& k) const {
    NODEtree<Key, Peli>* nodeAux = root;

    while (nodeAux != nullptr) {
        if (nodeAux->getKey() == k) {
            return nodeAux->getValue();
        } else if (nodeAux->getKey() > k) {
            nodeAux = nodeAux->getLeft();
        } else {
            nodeAux = nodeAux->getRight();
        }
    }

    cout << "No s'ha trobat la key" << endl;
    static vector<Peli> vectorBuit;
    return vectorBuit;
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::printPreorder() const {
    printPreorder(root);
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::printPreorder(const NODEtree<Key, Peli>* n) const {
    if (n == nullptr) return;
    cout << n->getKey() << ", ";
    printPreorder(n->getLeft());
    printPreorder(n->getRight());
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::printPostorder() const {
    printPostorder(root);
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::printPostorder(const NODEtree<Key, Peli>* n) const {
    if (n == nullptr) return;
    printPostorder(n->getLeft());
    printPostorder(n->getRight());
    cout << n->getKey() << ", ";
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::printInorder() const {
    printInorder(root);
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::printInorder(const NODEtree<Key, Peli>* n) const {
    if (n == nullptr) return;
    printInorder(n->getLeft());
    cout << n->getKey() << ", ";
    printInorder(n->getRight());
}

template <class Key, class Peli>
list<NODEtree<Key, Peli>*> BSTtree<Key, Peli>::getLeafNodes() const {
    list<NODEtree<Key, Peli>*> fulles;
    getFulles(root, fulles);
    return fulles;
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::getFulles(NODEtree<Key, Peli>* node, list<NODEtree<Key, Peli>*>& fulles) const { // Ensure NODEtree is correctly defined with templates.
    if (node == nullptr) return;
    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        fulles.push_back(node);
    } else {
        getFulles(node->getLeft(), fulles);
        getFulles(node->getRight(), fulles);
    }
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::printSecondLargestKey() const {
    if (root == nullptr || (root->getLeft() == nullptr && root->getRight() == nullptr)) {
        cout << "No hi ha segon node més gran." << endl;
        return;
    } else {
        NODEtree<Key, Peli>* nodeAux1 = root;
        NODEtree<Key, Peli>* nodeAux2 = nullptr;

        Key secondLargestKey = getSecondLargestKey(nodeAux1, nodeAux2);
        cout << "El segon node més gran és: " << secondLargestKey << endl;
    }
}

template <class Key, class Peli>
Key BSTtree<Key, Peli>::getSecondLargestKey(NODEtree<Key, Peli>* nodeAux1, NODEtree<Key, Peli>* nodeAux2) const {
    if (nodeAux1 == nullptr) return Key();

    if (nodeAux1->getRight() == nullptr) {
        return nodeAux2->getKey();
    }

    if (nodeAux1->getRight()->getLeft() != nullptr || nodeAux1->getRight()->getRight() != nullptr) {
        return getSecondLargestKey(nodeAux1->getRight(), nodeAux1);
    }

    return nodeAux1->getKey();
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::mirrorTree() {
    mirrorTreeAux(root);
}

template <class Key, class Peli>
void BSTtree<Key, Peli>::mirrorTreeAux(NODEtree<Key, Peli>* root) {
    if (root == nullptr) return;

    NODEtree<Key, Peli>* nodeAux = root->getLeft();
    root->setLeft(root->getRight());
    root->setRight(nodeAux);

    mirrorTreeAux(root->getLeft());
    mirrorTreeAux(root->getRight());
}

template <class Key, class Peli>
NODEtree<Key, Peli>* BSTtree<Key, Peli>::search(const Key& k) const {
    NODEtree<Key, Peli>* nodeAux = root;

    while (nodeAux != nullptr) {
        if (nodeAux->getKey() == k) {
            return nodeAux;
        } else if (nodeAux->getKey() > k) {
            nodeAux = nodeAux->getLeft();
        } else {
            nodeAux = nodeAux->getRight();
        }
    }

    return nullptr;
}

#endif /* BSTTREE_H */
