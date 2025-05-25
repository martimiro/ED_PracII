#ifndef HASHMAP_H
#define HASHMAP_H

#include "LinkedHashEntry.h"

using namespace std;

template <class Key, class Value>  
class HashMap { 
    public:         
        const static int MAX_TABLE = 11; // Definir a ?? el valor que necessiteu 
        HashMap(); 
        virtual ~HashMap(); 
        int getHashCode (int key) const; 
        void put(const Key& key, const Value& value); 
        void print(); 
        const bool get(const Key& key) const; 
        int size() const; 
        LinkedHashEntry <Key,Value>* getPosition(const Key& element); 
        LinkedHashEntry<Key,Value>* getCell(int index) const;
        
        int cells() const;       
        int colisions() const;
 
    private: 
        LinkedHashEntry<Key,Value>* arrayElems[MAX_TABLE] = {}; // taula de hash 
        int mida;  // Nombre d’elements dins del HashMap 
        int celles; // Nombre de cel·les ocupades del HashMap 
        int colisioMax; // Profunditat màxima d’una cel·la a tot el HashMap       
 
};

// Constructor
template <class Key, class Value>
HashMap<Key, Value>::HashMap() {
    for (int i = 0; i < MAX_TABLE; i++) {
        arrayElems[i] = nullptr;
    }
    mida = 0;
    celles = 0;
    colisioMax = 0;
}

// Destructor
template <class Key, class Value>
HashMap<Key, Value>::~HashMap() {
    for (int i = 0; i < MAX_TABLE; i++) {
        delete arrayElems[i];
    }
}

// Getters
template <class Key, class Value>
int HashMap<Key, Value>::getHashCode(int key) const {
    return key % MAX_TABLE;
}

template <class Key, class Value>
LinkedHashEntry<Key, Value>* HashMap<Key, Value>::getCell(int index) const {
    if (index >= 0 && index < MAX_TABLE) {
        return arrayElems[index];
    }
    return nullptr;
}

template <class Key, class Value>
int HashMap<Key, Value>::size() const {
    return mida;
}

template <class Key, class Value>
LinkedHashEntry<Key, Value>* HashMap<Key, Value>::getPosition(const Key& key) {
    int i = getHashCode(key);
    LinkedHashEntry<Key, Value>* entrada = arrayElems[i];

    while (entrada != nullptr) {
        if (entrada->getKey() == key) {
            return entrada;
        }
        entrada = entrada->getNext();
    }
    return nullptr;
}

// Altres metodes
template <class Key, class Value>
void HashMap<Key, Value>::put(const Key& key, const Value& value) {
    int i = getHashCode(key);
    LinkedHashEntry<Key, Value>* entrada = arrayElems[i];
    int profunditat = 1;

    if (entrada == nullptr) {
        arrayElems[i] = new LinkedHashEntry<Key, Value>(key);
        arrayElems[i]->setValue(value);
        mida = mida + 1;
        celles = celles + 1;
    } else {
        LinkedHashEntry<Key, Value>* previ = nullptr;
        while (entrada != nullptr) {
            if (entrada->getKey() == key) {
                entrada->setValue(value);
                mida = mida + 1;
                colisioMax = max(colisioMax, profunditat);
                return;
            }
            previ = entrada;
            entrada = entrada->getNext();
            profunditat = profunditat + 1;
        }

        LinkedHashEntry<Key, Value>* entradaAux = new LinkedHashEntry<Key, Value>(key);
        entradaAux->setValue(value);
        previ->setNext(entradaAux);
        mida = mida + 1;
        colisioMax = max(colisioMax, profunditat);
    }
}

template <class Key, class Value>
const bool HashMap<Key, Value>::get(const Key& key) const {
    int index = getHashCode(key);
    LinkedHashEntry<Key, Value>* entrada = arrayElems[index];

    while (entrada != nullptr) {
        if (entrada->getKey() == key) {
            return true;
        }
        entrada = entrada->getNext();
    }
    return false;
}

template <class Key, class Value>
void HashMap<Key, Value>::print() {
    for (int i = 0; i < MAX_TABLE; i++) {
        LinkedHashEntry<Key, Value>* entrada = arrayElems[i];

        if (entrada != nullptr) {
            cout << "Índex " << i << ": ";

            while (entrada != nullptr) {
                entrada->toString();
                entrada = entrada->getNext();
            }
        }
    }
}

template <class Key, class Value>
int HashMap<Key, Value>::cells() const {
    return celles;
}

template <class Key, class Value>
int HashMap<Key, Value>::colisions() const {
    return colisioMax;
}

#endif /*HASHMAP_H*/