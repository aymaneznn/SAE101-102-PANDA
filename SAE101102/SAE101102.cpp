#include <iostream>
using namespace std;

// Taille maximale de la bambouseraie
const int TAILLE_MAX = 100;

// Definition des bambou
struct Bambou {
    int croissance;
    int taille;
};

//Création d'un bambou
void CreateBambou(Bambou bambou, int taille) {
    bambou.croissance = taille;
    bambou.taille = taille;
}

//Création d'un bambou
void GrowBambou(Bambou bambou) {
    bambou.taille += bambou.croissance;
}

int VerifMax(Bambou Bambou, int TailleChoisie) {
        
        int TailleMax = 0;
        int indiceBambou;

        for (int i = 0 ; i < TailleChoisie; i++) {
            if (Bambou.taille > TailleMax) {
                TailleMax = Bambou.taille;
                indiceBambou = i;
            }
        }
        return indiceBambou;
}

int main(){
    Bambou bambouseraie[TAILLE_MAX];
}