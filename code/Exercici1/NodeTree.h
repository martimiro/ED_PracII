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
        /* Consultors */

        const Key& getKey() const;
        const vector<Value>& getValue() const;

        // Declareu-hi aquí els consultors (getters) dels atributs que manquen
        /* Operacions */
        bool isRoot() const;
        bool hasLeft() const;
        bool hasRight() const;
        bool isExternal() const;
        
        void insertValue(const V& v);
        int depth() const;
        int height() const;
        bool operator==(const BSTNode<K,V>& node) const;

    private:
        Key key;
        vector<Value> values;
        // Afegiu-hi aquí els atributs que manquen
};