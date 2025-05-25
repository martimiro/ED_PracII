#include "Peli.h"
#include "HashMap.h"
#include "LinkedHashEntry.h"

class MubiesflixHash: public HashMap<int,Peli> {
    public:
    MubiesflixHash(string file_path);
    virtual ~MubiesflixHash() {};
    int totalCelles();
    int totalCol();
    int maxCol();
    int factorCarrega(); //percentatge d’espai ocupat al hash
    void addPeli(int director_id, Peli peli);
    vector<Peli> getPeliculasDirector(int director_id);
    private:
    void loadFromFile(string file_path);
    void _insereixPelicula(int director_id, int peli_id, string titol, int durada, float
    valoracio);
    };