

// Definition des bambou
struct Bambou {
    int croissance;
    int taille;
};

// Création d'un bambou
void CreateBambou(Bambou bambou, int taille) {
    bambou.croissance = taille;
    bambou.taille = taille;
}

// Croissance d'un bambou
void GrowBambou(Bambou bambou) {
    bambou.taille += bambou.croissance;
}
 
// Coupe d'un bambou
void CutBambou(Bambou bambou) {
    bambou.taille = bambou.croissance;
}

// Reperage du bambou le plus grand
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

// Coupe le bambou le plus grand
void ReduceMax(Bambou bambou, int tab[], int TailleChoisie) {
    int taille;
    int indice = VerifMax(bambou, TailleChoisie);
    tab[indice] = bambou.croissance;
}

// Fonction Reduce-Fastest(x)


int ReduceFaster(Bambou bambou, int seuil, Bambou tab[], int TailleChoisie) {
    int maxCroissance = 0;
    if (bambou.taille = seuil) {
        for (int i = 0; i < TailleChoisie, i++) {
            if (tab[i].croissance > maxCroissance) {
                maxCroissance = tab[i].croissance;
            }
        }

    }
    return maxCroissance;
}

// Croissance simultané de la bambouraie
void GrowAll(Bambou bambouraie[], int taille) {
    for (int i = 0; i < taille; i++) {
        GrowBambou(bambouraie[i]);
    }
}

int main(){
    Bambou bambouseraie[TAILLE_MAX];

}