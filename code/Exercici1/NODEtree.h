#ifndef NODETREE_H
#define NODETREE_H

#include <iostream>

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

        void setRight(Node<Key, Value>* right);
        void setLeft(Node<Key, Value>* left);

        /* Consultors */
        // Declareu-hi aquí els consultors (getters) dels atributs que manquen
        const Key& getKey() const;
        const vector<Value>& getValue() const;

        const Node<Key, Value>* getRight() const;
        const Node<Key, Value>* getLeft() const;

        /* Operacions */
        bool isRoot() const;
        bool hasLeft() const;
        bool hasRight() const;
        bool isExternal() const;
        
        void insertValue(const V& v);
        int depth() const;
        int height() const;
        bool operator==(const BSTNode<Key, Value>& node) const;

    private:
        Key key;
        vector<Value> values;
        // Afegiu-hi aquí els atributs que manquen
        Node<Key, Value>* right;
        Node<Key, Value>* left;

};

#endif /* NODETREE_H */