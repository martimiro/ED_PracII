#ifndef PELI_H
#define PELI_H

#include <string>
#include <iostream>

using namespace std;

class Peli {
    private:
        int peliId;
        string titol;
        int durada;
        float valoracio;

    public:
        Peli();
        Peli(int peliId, string titol, int durada, float valoracio);

        int getPeliId() const;
        string getTitol() const;
        int getDurada() const;
        float getValoracio() const;

        void setPeliId(int peliId);
        void setTitol(string titol);
        void setDurada(int durada);
        void setValoracio(float valoracio);

        void printInfo() const;
};

// Constructors
Peli::Peli() {
    peliId = 0;
    titol = "";
    durada = 0;
    valoracio = 0.0f;
}

Peli::Peli(int peliId, string titol, int durada, float valoracio) {
    setPeliId(peliId);
    setTitol(titol);
    setDurada(durada);
    setValoracio(valoracio);
}
// Getters
int Peli::getPeliId() const {
    return peliId;
}

string Peli::getTitol() const {
    return titol;
}

int Peli::getDurada() const {
    return durada;
}

float Peli::getValoracio() const {
    return valoracio;
}

// Setters
void Peli::setPeliId(int peliId) {
    this -> peliId = peliId;
}

void Peli::setTitol(string titol) {
    this -> titol = titol;
}

void Peli::setDurada(int durada) {
    this -> durada = durada;
}

void Peli::setValoracio(float valoracio) {
    this -> valoracio = valoracio;
}

// Altres mètodes
void Peli::printInfo() const {
    cout << "Peli ID: " << getPeliId() << endl;
    cout << "Títol: " << getTitol() << endl;
    cout << "Durada: " << getDurada() << endl;
    cout << "Valoració: " << getValoracio() << endl;
}
#endif /*PELI_H*/