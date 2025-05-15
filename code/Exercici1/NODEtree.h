#ifndef NODETREE_H
#define NODETREE_H

#include <iostream>
#include <vector>

using namespace std;

template <class Key, class Value>
class NODEtree {
    public:
        NODEtree(const Key& key);
        NODEtree(const NODEtree<Key,Value>& orig);
        virtual ~NODEtree();

        /* Modificadors */
        // Declareu-hi aquí els modificadors (setters) dels atributs que manquen
        void setKey(Key key);
        void setValue(Value value);

        void setRight(NODEtree* right);
        void setLeft(NODEtree* left);
        void setParent(NODEtree* parent);

        /* Consultors */
        // Declareu-hi aquí els consultors (getters) dels atributs que manquen
        const Key& getKey() const;
        const vector<Value>& getValue() const;

        const NODEtree* getRight() const;
        const NODEtree* getLeft() const;
        const NODEtree* getParent() const;

        /* Operacions */
        bool isRoot() const;
        bool hasLeft() const;
        bool hasRight() const;
        bool isExternal() const;
        
        void insertValue(const Value& v); // Preguntar si es value o no
        int depth() const;
        int height() const;
        bool operator==(const NODEtree<Key, Value> &node) const; // Preguntar

    private:
        Key key;
        vector<Value> values;
        // Afegiu-hi aquí els atributs que manquen
        NODEtree* right;
        NODEtree* left;
        NODEtree* parent;
};

// Constructor
template <class Key, class Value>
NODEtree <Key, Value>::NODEtree(const Key& key) {}

// Constructor còpia
template <class Key, class Value>
NODEtree <Key, Value>::NODEtree(const NODEtree<Key,Value>& orig) {}

// Destructor
template <class Key, class Value>
NODEtree <Key, Value>::~NODEtree() {}

// Setters
template <class Key, class Value>
void NODEtree <Key, Value>::setKey(Key key) {
    this -> key = key;
}

template <class Key, class Value>
void NODEtree <Key, Value>::setValue(Value value) {
    this -> value = value;
}

template <class Key, class Value>
void NODEtree <Key, Value>::setRight(NODEtree* right) {
    this -> right = right;
}

template <class Key, class Value>
void NODEtree <Key, Value>::setLeft(NODEtree* left) {
    this -> left = left;
}

template <class Key, class Value>
void NODEtree <Key, Value>::setParent(NODEtree* parent) {
    this -> parent = parent;
}

// Getters
template <class Key, class Value>
const Key& NODEtree<Key, Value>::getKey() const {
    return key;
}

template <class Key, class Value>
const vector<Value>& NODEtree<Key, Value>::getValue() const {
    return values;
}

template <class Key, class Value>
const NODEtree<Key, Value>* NODEtree<Key, Value>::getRight() const {
    return right;
}

template <class Key, class Value>
const NODEtree<Key, Value>* NODEtree<Key, Value>::getLeft() const {
    return left;
}

template <class Key, class Value>
const NODEtree<Key, Value>* NODEtree<Key, Value>::getParent() const {
    return parent;
}

// Altres mètodes
template <class Key, class Value>
bool NODEtree<Key, Value>::isRoot() const {
    if (this->getParent() == nullptr) {
        return true;
    } else {
        return false;
    }
}

template <class Key, class Value>
bool NODEtree<Key, Value>::hasLeft() const {
    if (this->getLeft() == nullptr) {
        return false;
    } else {
        return true;
    }

}

template <class Key, class Value>
bool NODEtree<Key, Value>::hasRight() const {
    if (this->getRight() == nullptr) {
        return false;
    } else {
        return true;
    }
}

template <class Key, class Value>
bool NODEtree<Key, Value>::isExternal() const {
    if (this->getLeft() == nullptr && this->getRight() == nullptr) {
        return true;
    } else {
        return false;
    }
}

template <class Key, class Value>
void NODEtree<Key, Value>::insertValue(const Value& v) {
    this -> values.push_back(v);
}

template <class Key, class Value>
int NODEtree<Key, Value>::depth() const {
    if (this->getParent() == nullptr) {
        return 0;
    } else {
        return 1 + getParent() -> depth();
    }
}

template <class Key, class Value>
int NODEtree<Key, Value>::height() const {
    if (this -> getRight() == nullptr && this -> getLeft() == nullptr) {
        return 0;
    } else {
        int heightEsq = 0;
        int heightDrt = 0;

        if (this -> getLeft() != nullptr) {
            heightEsq = this -> getLeft() -> height();
        }

        if (this -> getRight() != nullptr) {
            heightDrt = this -> getRight() -> height();
        }

        if (heightDrt > heightEsq) {
            return heightDrt;
        } else {
            return heightEsq;
        }
    }
}

template <class Key, class Value>
bool NODEtree<Key, Value>::operator==(const NODEtree<Key, Value>& node) const {
    if (this -> getKey() == node -> getKey() && this -> getValue() == node -> getValue()) {
        return true;
    } else {
        return false;
    }
}

#endif /* NODETREE_H */