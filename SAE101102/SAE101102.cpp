#include <iostream>
using namespace std;

// Taille maximale de la bambouseraie
const int TAILLE_MAX = 100;

// Definition des bambou
struct Bambou {
    int croissance;
    int taille;
};

void VerifMax(Bambou Bambou, int TailleChoisie) {

    int TailleMax = 0;
    int indiceBambou;

    for (int i = 0; i < TailleChoisie; i++) {
        if (Bambou.taille > TailleMax) {
            TailleMax = Bambou.taille;
            indiceBambou = i;
        }
    }
}

int main() {
    Bambou bambouseraie[TAILLE_MAX];
}