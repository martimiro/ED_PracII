#ifndef NODETREE_H
#define NODETREE_H

#include <iostream>
#include <vector>

using namespace std;

template <class Key, class Peli>
class NODEtree {
    public:
        NODEtree(const Key& key);
        NODEtree(const NODEtree& orig);
        virtual ~NODEtree();

        /* Modificadors */
        void setKey(const Key& key);
        void setValue(const Peli& peli);

        void setRight(NODEtree* right);
        void setLeft(NODEtree* left);
        void setParent(NODEtree* parent);

        /* Consultors */
        const Key& getKey() const;
        Key& getKey();
        const vector<Peli>& getValue() const;
        vector<Peli>& getValue();

        const NODEtree* getRight() const;
        NODEtree* getRight();
        const NODEtree* getLeft() const;
        NODEtree* getLeft();
        const NODEtree* getParent() const;
        NODEtree* getParent();

        /* Operacions */
        bool isRoot() const;
        bool hasLeft() const;
        bool hasRight() const;
        bool isExternal() const;

        void insertValue(const Peli& v);
        int depth() const;
        int height() const;
        bool operator==(const NODEtree& node) const;

    private:
        Key key;
        vector<Peli> values;
        NODEtree* right;
        NODEtree* left;
        NODEtree* parent;
};

template <class Key, class Peli>
NODEtree<Key, Peli>::NODEtree(const Key& key) {
    this->key = key;
    this->right = nullptr;
    this->left = nullptr;
    this->parent = nullptr;
}

template <class Key, class Peli>
NODEtree<Key, Peli>::NODEtree(const NODEtree& orig) {
    this->key = orig.key;
    this->values = orig.values;
    this->right = nullptr;
    this->left = nullptr;
    this->parent = nullptr;
}

template <class Key, class Peli>
NODEtree<Key, Peli>::~NODEtree() {
    delete left;
    delete right;
}

template <class Key, class Peli>
void NODEtree<Key, Peli>::setKey(const Key& key) {
    this->key = key;
}

template <class Key, class Peli>
void NODEtree<Key, Peli>::setValue(const Peli& value) {
    values.clear();
    values.push_back(value);
}

template <class Key, class Peli>
void NODEtree<Key, Peli>::setRight(NODEtree* right) {
    this->right = right;
}

template <class Key, class Peli>
void NODEtree<Key, Peli>::setLeft(NODEtree* left) {
    this->left = left;
}

template <class Key, class Peli>
void NODEtree<Key, Peli>::setParent(NODEtree* parent) {
    this->parent = parent;
}

template <class Key, class Peli>
const Key& NODEtree<Key, Peli>::getKey() const {
    return key;
}

template <class Key, class Peli>
Key& NODEtree<Key, Peli>::getKey() {
    return key;
}

template <class Key, class Peli>
const vector<Peli>& NODEtree<Key, Peli>::getValue() const {
    return values;
}

template <class Key, class Peli>
vector<Peli>& NODEtree<Key, Peli>::getValue() {
    return values;
}

template <class Key, class Peli>
const NODEtree<Key, Peli>* NODEtree<Key, Peli>::getRight() const {
    return right;
}

template <class Key, class Peli>
NODEtree<Key, Peli>* NODEtree<Key, Peli>::getRight() {
    return right;
}

template <class Key, class Peli>
const NODEtree<Key, Peli>* NODEtree<Key, Peli>::getLeft() const {
    return left;
}

template <class Key, class Peli>
NODEtree<Key, Peli>* NODEtree<Key, Peli>::getLeft() {
    return left;
}

template <class Key, class Peli>
const NODEtree<Key, Peli>* NODEtree<Key, Peli>::getParent() const {
    return parent;
}

template <class Key, class Peli>
NODEtree<Key, Peli>* NODEtree<Key, Peli>::getParent() {
    return parent;
}

template <class Key, class Peli>
bool NODEtree<Key, Peli>::isRoot() const {
    return this->getParent() == nullptr;
}

template <class Key, class Peli>
bool NODEtree<Key, Peli>::hasLeft() const {
    return this->getLeft() != nullptr;
}

template <class Key, class Peli>
bool NODEtree<Key, Peli>::hasRight() const {
    return this->getRight() != nullptr;
}

template <class Key, class Peli>
bool NODEtree<Key, Peli>::isExternal() const {
    return this->getLeft() == nullptr && this->getRight() == nullptr;
}

template <class Key, class Peli>
void NODEtree<Key, Peli>::insertValue(const Peli& v) {
    this->values.push_back(v);
}

template <class Key, class Peli>
int NODEtree<Key, Peli>::depth() const {
    if (this->getParent() == nullptr) {
        return 0;
    } else {
        return 1 + getParent()->depth();
    }
}

template <class Key, class Peli>
int NODEtree<Key, Peli>::height() const {
    if (this->getRight() == nullptr && this->getLeft() == nullptr) {
        return 1;
    } else {
        int heightEsq = 0;
        int heightDrt = 0;

        if (this->getLeft() != nullptr) {
            heightEsq = this->getLeft()->height();
        }

        if (this->getRight() != nullptr) {
            heightDrt = this->getRight()->height();
        }

        return 1 + max(heightEsq, heightDrt);
    }
}

template <class Key, class Peli>
bool NODEtree<Key, Peli>::operator==(const NODEtree& node) const {
    return this->getKey() == node.getKey() && this->getValue() == node.getValue();
}

#endif /* NODETREE_H */
