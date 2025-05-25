#include "NODEtree.h"
#include "BSTtree.h"
#include "Peli.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class MubiesflixBST : protected BSTtree<int, Peli> { 
    public: 
        enum AdditionStrategy { AFTER_LARGEST_ID, SMALLEST_NOTTAKEN_ID }; 
        MubiesflixBST(AdditionStrategy addition_strategy = AFTER_LARGEST_ID); 
        MubiesflixBST (AdditionStrategy addition_strategy, string file_path); 
        MubiesflixBST (const MubiesflixBST & orig); 
        virtual ~MubiesflixBST ();         
        void loadFromFile(string file_path); 
        void showAllPelis() const; 
        void showPelisByDirector(int director_id) const; 
        float getAverageValoracioOfDirector(int director_id) const; 
        void findLargestDirectorId() const; 
        void findSmallestNotTakenDirectorId() const; 
        void addPeli();
        
        void setStrategy(AdditionStrategy addition_strategy);
        static AdditionStrategy intToStrategy(int val);

    private: 
        AdditionStrategy addition_strategy; 
        /* Metodes auxiliars, definiu-los aquí sota */ 
};

// Constructors
MubiesflixBST::MubiesflixBST(AdditionStrategy addition_strategy) {
    // És l'únic que ens cal per poder incialitzar l'objecte
    this->addition_strategy = addition_strategy;
}

MubiesflixBST::MubiesflixBST (AdditionStrategy addition_strategy, string file_path) {
    this->addition_strategy = addition_strategy;
    loadFromFile(file_path);
}

// Constructor còpia
MubiesflixBST::MubiesflixBST(const MubiesflixBST& orig) {
    this->addition_strategy = orig.addition_strategy;
}

// Destructor
MubiesflixBST::~MubiesflixBST() {

}

// Setters
void MubiesflixBST::setStrategy(AdditionStrategy addition_strategy) {
    this -> addition_strategy = addition_strategy;
}

// Altres mètodes
void MubiesflixBST::loadFromFile(string file_path) {
    ifstream fitxer(file_path);

    if (!fitxer.is_open()) {
        cout << "No es pot trobar el fitxer: " << file_path << endl;
        return;
    }

    string aux;
    int liniaNum = 0;
    while (getline(fitxer, aux)) {
        liniaNum++;
        stringstream ss(aux);
        string camp;

        int peliId = -1;
        int directorId = -1;
        string titol;
        int durada = -1;
        float valoracio = -1.0f;

        try {
            // Pel·lí ID
            if (!getline(ss, camp, '|')) throw invalid_argument("Manca peliId");
            peliId = stoi(camp);

            // Director ID
            if (!getline(ss, camp, '|')) throw invalid_argument("Manca directorId");
            directorId = stoi(camp);

            // Títol
            if (!getline(ss, titol, '|')) throw invalid_argument("Manca titol");

            // Durada
            if (!getline(ss, camp, '|')) throw invalid_argument("Manca durada");
            durada = stoi(camp);

            // Valoració
            if (!getline(ss, camp, '|')) throw invalid_argument("Manca valoracio");
            valoracio = stof(camp);

            // Inserim la pel·lícula
            Peli p(peliId, titol, durada, valoracio);
            this->insert(directorId, p);
        }
        catch (const invalid_argument& e) {
            cout << "Error a la línia " << liniaNum << ": " << e.what() << endl;
        }
    }
    fitxer.close();
}


void MubiesflixBST::showPelisByDirector(int directorId) const {
    // Cas base (arbre buit)
    if (root == nullptr) {
        throw runtime_error("Arbre buit");
    }

    NODEtree<int, Peli>* nodeAux = root;
    bool trobat = false;
    int comptador = 0;

    while (nodeAux != nullptr) {
        if (directorId == nodeAux->getKey()) {
            trobat = true;
            vector<Peli>& pelis = nodeAux->getValue();
            // Recorrem totes les pel·lícules
            for (Peli& peli : pelis) {
                comptador = comptador + 1;
                cout << "La pel·lícula " << comptador << ": ";
                peli.printInfo();
                cout << endl;
            }
            // En cas que el trobem parem (no sé si podem fer ús del break)
            break;
        } else if (directorId < nodeAux->getKey()) {
            nodeAux = nodeAux->getLeft();
        } else {
            nodeAux = nodeAux->getRight();
        }
    }

    if (!trobat) {
        throw runtime_error("Director no trobat");
    }
}

float MubiesflixBST::getAverageValoracioOfDirector(int directorId) const {
    // Cas base (arbre buit)
    if (root == nullptr) {
        throw runtime_error("Arbre buit");
    }

    NODEtree<int, Peli>* nodeAux = root;
    bool trobat = false;
    float suma = 0.0f;
    int comptador = 0;

    // Cerca binària per director_id
    while (nodeAux != nullptr) {
        if (directorId == nodeAux->getKey()) {
            trobat = true;
            const vector<Peli>& pelis = nodeAux->getValue();

            if (pelis.empty()) { 
                throw runtime_error("Director sense pel·lícules");
            }
            for (const Peli& peli : pelis) {
                suma = suma + peli.getValoracio();
                comptador = comptador + 1;
            }
            // En cas que el trobem parem (no sé si podem fer ús del break)
            break;
        } else if (directorId < nodeAux->getKey()) {
            nodeAux = nodeAux->getLeft();
        } else {
            nodeAux = nodeAux->getRight();
        }
    }

    if (!trobat) {
        throw runtime_error("Director no trobat");
    }

    float average = suma / comptador;
    return average;
}

void MubiesflixBST::showAllPelis() const {
    // Cas base (arbre buit)
    if (root == nullptr) {
        throw runtime_error("Arbre buit");
    }

    // He posat el mateix numero que al PDF
    int k = 2;
    vector<NODEtree<int, Peli>*> llistaNode;
    NODEtree<int, Peli>* nodeAux = root;
    int comptador = 0;
    char input;

    while (!llistaNode.empty() || nodeAux != nullptr) {
        while (nodeAux != nullptr) {
            llistaNode.push_back(nodeAux);
            nodeAux = nodeAux->getLeft();
        }

        // Últim node
        nodeAux = llistaNode.back();
        // L'eliminem de la llista
        llistaNode.pop_back();

        // Imprimeix director i pel·lícules
        cout << "Director: " << nodeAux->getKey() << "\n===" << endl;
        vector<Peli>& pelis = nodeAux->getValue();
        for (size_t i = 0; i < pelis.size(); ++i) {
            cout << "Pel·lícula " << (i + 1) << ": ";
            pelis[i].printInfo();
            cout << endl;
        }
        cout << endl; 

        comptador = comptador + 1;

        // Demana continuar cada k directors
        if (comptador % k == 0) {
            cout << "Vols veure les següents " << k << " directors? (s/n): ";
            cin >> input;

            if (input == 'n') {
                return; // Finalitza si l'usuari respon 'n'
            }
        }

        nodeAux = nodeAux->getRight();
    }
}

void MubiesflixBST::findLargestDirectorId() const {
    if (root == nullptr) {
        throw runtime_error("Arbre buit");
    }

    NODEtree<int, Peli>* nodeAux = root;
    while (nodeAux->getRight() != nullptr) {
        nodeAux = nodeAux->getRight();
    }

    cout<< "La id més gran és:" << nodeAux->getKey() << endl; 
}

void MubiesflixBST::findSmallestNotTakenDirectorId() const {
    if (root == nullptr) {
        cout << "Arbre buit" << endl;
        return;
    }

    vector<int> llistaIdDirector;
    vector<NODEtree<int, Peli>*> llistaNode;
    NODEtree<int, Peli>* nodeAux = root;

    while (!llistaNode.empty() || nodeAux != nullptr) {
        while (nodeAux != nullptr) {
            llistaNode.push_back(nodeAux);
            nodeAux = nodeAux->getLeft();
        }

        nodeAux = llistaNode.back();
        llistaNode.pop_back();

        llistaIdDirector.push_back(nodeAux->getKey());

        nodeAux = nodeAux->getRight();
    }

    int idFalta = 0;
    for (int id : llistaIdDirector) {
        if (id > idFalta) {
            // Si es compleix sortim.
            break; 
        }
        idFalta = id + 1;
    }

    cout << "El ID del director més petit no assignat és: " << idFalta << endl;
}

void MubiesflixBST::addPeli() {
    // Demanar dades de la pel·lícula
    int peliId;
    string titol;
    int durada;
    float valoracio;

    cout << "Afegir Pel·lícula" << endl;

    cout << "ID de la pel·lícula: ";
    cin >> peliId;

    cout << "Títol: ";
    cin >> titol;

    cout << "Durada (minuts): ";
    cin >> durada;

    cout << "Valoració (0-10): ";
    cin >> valoracio;

    Peli novaPeli(peliId, titol, durada, valoracio);

    char opcio;
    cout << "Vols assignar manualment el ID director? (s/n): ";
    cin >> opcio;

    int directorId;
    if (opcio == 's') {
        cout << "Introdueix ID director: ";
        cin >> directorId;
    } else {
        // smallest not taken
        if(addition_strategy == SMALLEST_NOTTAKEN_ID) {
            vector<int> llistaId;
            vector<NODEtree<int, Peli>*> llistaNode;
            NODEtree<int, Peli>* nodeAux = root;

            while (!llistaNode.empty() || nodeAux != nullptr) {
                while (nodeAux != nullptr) {
                    llistaNode.push_back(nodeAux);
                    nodeAux = nodeAux->getLeft();
                }

                nodeAux = llistaNode.back();
                llistaNode.pop_back();
                llistaId.push_back(nodeAux->getKey());
                nodeAux = nodeAux->getRight();
            }
            
            directorId = 0;
            for (int id : llistaId) {
                if (id > directorId) break;
                directorId = id + 1;
            }
        } else {
            // after largest id
            if (root == nullptr) {
                directorId = 0;
            } else {
                NODEtree<int, Peli>* node = root;
                while (node->getRight()) node = node->getRight();
                directorId = node->getKey() + 1;
            }
        }
    }

    insert(directorId, novaPeli);
    cout << "Pel·lícula afegida" << endl;
}

MubiesflixBST::AdditionStrategy MubiesflixBST::intToStrategy(int valor) {
    if (valor == 1) {
        return AFTER_LARGEST_ID;
    } else if (valor == 2) {
        return SMALLEST_NOTTAKEN_ID;
    } else {
        throw invalid_argument("Valor d'estratègia no vàlid");
    }
}