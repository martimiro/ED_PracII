#ifndef LINKEDHASHENTRY_H
#define LINKEDHASHENTRY_H

#include <vector>
#include <iostream>

using namespace std;

template <class Key, class Value> 
class LinkedHashEntry { 
private: 
    Key key; 
    vector<Value> values; 
    LinkedHashEntry* next; 
public: 
    LinkedHashEntry(Key key);     
    ~LinkedHashEntry();     
    Key getKey();     
    vector<Value>& getValue();     
    void setValue(const Value& value); 
    LinkedHashEntry *getNext();     
    void setNext(LinkedHashEntry *next);     
    void toString() const; 
};

// Constructor
template <class Key, class Value>
LinkedHashEntry<Key, Value>::LinkedHashEntry(Key key) {
    this -> key = key;
    this -> next = nullptr;
}

// Destructor
template <class Key, class Value>
LinkedHashEntry<Key, Value>::~LinkedHashEntry() {
    delete next;
}

// Getters
template <class Key, class Value>
Key LinkedHashEntry<Key, Value>::getKey() {
    return key;
}

template <class Key, class Value>
vector<Value>& LinkedHashEntry<Key, Value>::getValue() {
    return values;
}

template <class Key, class Value>
LinkedHashEntry<Key, Value>* LinkedHashEntry<Key, Value>::getNext() {
    return next;
}

// Setters
template <class Key, class Value>
void LinkedHashEntry<Key, Value>::setValue(const Value& value) {
    this->values.push_back(value);
}

template <class Key, class Value>
void LinkedHashEntry<Key, Value>::setNext(LinkedHashEntry *next) {
    this -> next = next;
}

// Altres mètodes
template <class Key, class Value>
void LinkedHashEntry<Key, Value>::toString() const {
    cout << "Clau: " << key << " | Valors: ";
    for (int value : values) {
        cout << value << " ";
    }
    cout << endl;
}

#endif /*LINKEDHASHENTRY_H*/