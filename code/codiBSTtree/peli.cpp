#include "NODEtree.h"
#include "BSTtree.h"
#include "Peli.h"
#include "MubiesflixBST.h"

#include <iostream>
#include <string>

using namespace std;

void mostrarMenu() {
    cout << endl << "MENÚ MUBIESFLIX BST" << endl;
    cout << "1. Oferirà a l'usuari especificar la ruta del fitxer que es vulgui carregar a Mubiesflix. Us proporcionarem, mitjançant el Campus Virtual, diversos fitxers pelis-*.txt que haureu d'afegir al directori arrel del vostre projecte (allà on tingueu el main.cpp)." << endl;
    cout << "2. Mostrarà les pel·lícules d’un director concret." << endl;
    cout << "3. Mostrarà la valoració mitjana de les pel·lícules d’un director concret." << endl;
    cout << "4. Mostrarà tots els directors ordenats pel seu identificador i les seves pel·lícules." << endl;
    cout << "5. Mostrarà l’identificador més gran assignat als directors de Mubiesflix" << endl;
    cout << "6. Mostrarà l’identificador més petit no assignat a cap dels directors de Mubiesflix" << endl;
    cout << "7. Permetrà afegir una nova pel·lícula a un director. Per afegir-la a un director ja existent a Mubiesflix, s’haurà d’especificar l’identificador del director manualment. En cas de ser un nou director, es pot especificar manualment un nou identificador o trobar-ne un de manera automàtica seguint l’estratègia d’assignació pre-establerta." << endl;
    cout << "8. Establir una estratègia alternativa d’assignació automàtica d’identificadors de nous directors." << endl;
    cout << "9. Sortir" << endl;
    cout << "Selecciona una opció: ";
}

int main() {
    MubiesflixBST mubiesflix; // Use default initialization
    int opcio;
    string file_path;

    do {
        mostrarMenu();
        cin >> opcio;

        try {
            switch(opcio) {
                case 1: {
                    cout << "Introdueix el camí del fitxer (sense espais): ";
                    cin >> file_path;
                    mubiesflix.loadFromFile(file_path);
                    cout << "Fitxer carregat" << endl;
                    break;

                } case 2: {
                    int director_id;
                    cout << "Introdueix l'ID del director: ";
                    cin >> director_id;
                    mubiesflix.showPelisByDirector(director_id);
                    break;

                } case 3: {
                    int director_id;
                    cout << "Introdueix l'ID del director: ";
                    cin >> director_id;
                    float mitjana = mubiesflix.getAverageValoracioOfDirector(director_id);
                    cout << "Valoració mitjana: " << mitjana << endl;
                    break;

                } case 4: {
                    mubiesflix.showAllPelis();
                    break;
                } case 5: {
                    mubiesflix.findLargestDirectorId();
                    break;
                } case 6: {
                    mubiesflix.findSmallestNotTakenDirectorId();
                    break;
                } case 7: {
                    mubiesflix.addPeli();
                    break;
                } case 8: {
                    int estrat;
                    cout << "1. AFTER_LARGEST_ID" << endl;
                    cout << "2. SMALLEST_NOTTAKEN_ID" << endl;
                    cout << "Nova estratègia: ";

                    cin >> estrat;
                    mubiesflix.setStrategy(MubiesflixBST::intToStrategy(estrat));

                    cout << "Estratègia actualitzada" << endl;
                    break;
                } case 9: {
                    cout << "Adéu!" << endl;
                    break;
                } default: {
                    cout << "opcio incorrecta" << endl;
                    break;
                }
            }
        } 
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (opcio != 9);

    return 0;
}