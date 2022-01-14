#include<iostream>
using namespace std;

const int TAILLE_MAX = 100;

// Definition des bambou
struct Bambou {
    int croissance;
    int taille;
};

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




//// Statistiques de la taille maximal 
//int StatTaillleMax(Bambou tab[], int TailleChoisie) {
//    int maximum = 0;
//    for (int i = 0; i < TailleChoisie; i++) {
//        if (tab[i].taille > maximum) {
//            maximum = tab[i].taille;
//
//        }
//    }
//    return maximum;
//}

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

    // tests

    cout << " Debut " << endl << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Bambou " << i + 1 << " : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
    }
    cout << endl;
    GrowAll(bambouseraie, 5);
    for (int i = 0; i < 5; i++) {
        cout << "Bambou " << i + 1 << " : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
    }
    cout << endl;
    cout << "Premiere decoupe"<<endl;
    ReduceMax(bambouseraie, 5);
    GrowAll(bambouseraie, 5);
    for (int i = 0; i < 5; i++) {
        cout << "Bambou " << i + 1 << " : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
    }
    cout << endl;
    cout << "deuxieme decoupe" << endl;
    ReduceMax(bambouseraie, 5);
    GrowAll(bambouseraie, 5);
    for (int i = 0; i < 5; i++) {
        cout << "Bambou " << i + 1 << " : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
    }
    cout << endl;
    cout << "troisieme decoupe"<<endl;
    ReduceMax(bambouseraie, 5);
    GrowAll(bambouseraie, 5);
    for (int i = 0; i < 5; i++) {
        cout << "Bambou " << i + 1 <<" : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
    }
    cout << endl;

    cout << "fini" << endl;
    cout << " Le bambou le plus grand est le bambou numero : " << VerifMax(bambouseraie, 5) + 1 << " avec une taille de : "<< bambouseraie[VerifMax(bambouseraie, 5)].taille << endl;
    ReduceMax(bambouseraie, 5);
    ReduceFaster(6, bambouseraie, 5);
    
}