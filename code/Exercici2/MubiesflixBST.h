class MubiesflixBST {
    protected:
        BSTtree<int, Peli>;
    public: 
        enum AdditionStrategy { AFTER_LARGEST_ID, SMALLEST_NOTTAKEN_ID }; 
        MubiesflixBST(AdditionStrategy addition_strategy); 
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
    private: 
        AdditionStrategy addition_strategy; 
        /* Metodes auxiliars, definiu-los aquí sota */ 
};