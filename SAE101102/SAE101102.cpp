#include <iostream>
using namespace std;



// Taille maximale de la bambouseraie
const int TAILLE_MAX = 100;

// Definition des bambou

struct Bambou {
    int croissance;
    int taille;
};



// Fonction qui chrecher la bambou le plus grand

int VerifMax(Bambou bambou, int TailleChoisie) {
    

        int TailleMax = 0;
        int indiceBambou;

        for (int i = 0; i < TailleChoisie; i++) {
            if (bambou.taille > TailleMax) {
                TailleMax = bambou.taille;
                indiceBambou = i;
            }
        }

        return indiceBambou;
}

// Fonction qui enleve le bambou  Reduce - Max()

void ReduceMax(Bambou bambou, int tab[], int TailleChoisie) {
    int taille;
    int indice = VerifMax(bambou, TailleChoisie);
    tab[indice] = bambou.croissance;
}


// Fonction qui permet d'effacer le bambou le plus grand en laissant sa taille = croissance

void CutBambou(Bambou bambou) {

    bambou.taille = bambou.croissance;

}

// Fonction 

int main(){
    Bambou bambouseraie[TAILLE_MAX];
}