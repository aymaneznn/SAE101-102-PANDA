


// Fonction Reduce-Fastest(x)

void ReduceFaster(Bambou bambou, int seuil, Bambou tab[], int TailleChoisie) {
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

