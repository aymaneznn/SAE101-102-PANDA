using namespace std;
#include<iostream>

const int TAILLE_MAX = 100;

// Definition des bambou
struct Bambou {
    int croissance;
    int taille;
};

// Création d'un bambou
void CreateBambou(Bambou& bambou, int taille) {
    bambou.croissance = taille;
    bambou.taille = taille;
}

// Initialisation de bambouraie
void InitBamboueraie(Bambou bambouraie[], int taille, int tab[]) {
    for (int i = 0; i < taille; i++) {
        CreateBambou(bambouraie[i], tab[i]);
    }
}

// Statistique de la taille moyenne de la bambouseraie
float TailleMoy(Bambou tab[], int taille) {
    float total = 0;
    for (int i = 0; i < taille; i++) {
        total += tab[i].taille;
    }
    return total/taille;
}

// Statistique de la taille minimum de la bambouseraie
int TailleMin(Bambou tab[], int taille) {
    int min = tab[0].taille;
    for (int i = 0; i < taille; i++) {
        if (tab[i].taille < min) {
            min = tab[i].taille;
        }
    }
    return min;
}

void main() {
    Bambou bambousaie[TAILLE_MAX];
    int taille = 10;
    InitBamboueraie(bambousaie, taille, {})
}