#include<iostream>
using namespace std;

const int TAILLE_MAX = 100;

// Statistiques 

// Statistiques tailles max

int StatTaillleMax(Bambou tab[], int TailleChoisie) {
    int maximum = 0;
    for (int i = 0; i < TailleChoisie; i++) {
        if (tab[i].taille > maximum) {
            maximum = tab[i].taille;
        }
    }
    return maximum;
}

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

void InitBamboueraie(Bambou bambouraie[], int taille) {
    for (int i = 0; i < taille; i++){
        CreateBambou(bambouraie[i], (rand() % 9) + 1);
    }
}
// Croissance d'un bambou
void GrowBambou(Bambou& bambou) {
    bambou.taille += bambou.croissance;
}
 
// Coupe d'un bambou
void CutBambou(Bambou& bambou) {
    bambou.taille = bambou.croissance;
}

// Reperage du bambou le plus grand
int VerifMax(Bambou Bambou[], int TailleChoisie) {
        int TailleMax = 0;
        int indiceBambou = 0;

        for (int i = 0 ; i < TailleChoisie; i++) {
            if (Bambou[i].taille > TailleMax) {
                TailleMax = Bambou[i].taille;
                indiceBambou = i;
            }
        }
        return indiceBambou;
}

// Coupe le bambou le plus grand
void ReduceMax(Bambou bambou[], int TailleChoisie) {
    int taille;
    int indice = VerifMax(bambou, TailleChoisie);
    bambou[indice].taille = bambou[indice].croissance;
}

// Fonction Reduce-Fastest(x)
void ReduceFaster(int seuil, Bambou tab[], int TailleChoisie) {
    int maxCroissance = 0;
    for (int j = 0; j < TailleChoisie; j++) {
        if (tab[j].taille > seuil) {
            if (tab[j].croissance > maxCroissance) {
                maxCroissance = tab[j].croissance;
            }
        }
    }
    CutBambou(tab[maxCroissance]);
}

// Croissance simultané de la bambouraie
void GrowAll(Bambou bambouraie[], int taille) {
    for (int i = 0; i < taille; i++) {
        GrowBambou(bambouraie[i]);
    }
}

int main(){
    Bambou bambouseraie[TAILLE_MAX];
    InitBamboueraie(bambouseraie, 5);

    cout << "Bambou 0 : " << bambouseraie[0].taille << "  " << bambouseraie[0].croissance << endl;
    cout << "Bambou 1 : " << bambouseraie[1].taille << "  " << bambouseraie[1].croissance << endl;
    GrowBambou(bambouseraie[0]);
    cout << "Bambou 0 : " << bambouseraie[0].taille << "  " << bambouseraie[0].croissance << endl;
    cout << "Bambou 1 : " << bambouseraie[1].taille << "  " << bambouseraie[1].croissance << endl;
    CutBambou(bambouseraie[0]);
    cout << "Bambou 0 : " << bambouseraie[0].taille << "  " << bambouseraie[0].croissance << endl;
    cout << "Bambou 1 : " << bambouseraie[1].taille << "  " << bambouseraie[1].croissance << endl;

    cout << VerifMax(bambouseraie, 5);
    ReduceMax(bambouseraie, 5);
    ReduceFaster(6, bambouseraie, 5);
    GrowAll(bambouseraie, 5);
}
