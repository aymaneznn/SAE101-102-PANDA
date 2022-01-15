using namespace std;
#include<SDL.h> 
#include<SDL_ttf.h> 
#include<iostream>
#include "config_sdl.h"
#include <fstream>

const int TAILLE_MAX = 100;
const int y_premier_bambou = 570;

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



// (rand() % 9) + 1)


// Création d'un bambou
void CreateBambou(Bambou& bambou, int taille) {
    bambou.croissance = taille;
    bambou.taille = taille;
}

void InitBamboueraie(Bambou bambouraie[], int taille) {
    int tab[5] = { 2,4,3,1,5 };
    for (int i = 0; i < taille; i++){
        CreateBambou(bambouraie[i], tab[i]);
    }
}

// Croissance d'un bambou
int GrowBambou(Bambou& bambou) {
    bambou.taille += bambou.croissance;
    return bambou.taille;
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
int ReduceMax(Bambou bambou[], int TailleChoisie) {
    int taille;
    int indice = VerifMax(bambou, TailleChoisie);
    bambou[indice].taille = bambou[indice].croissance;
    return indice;
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

// --------------------------------------------------Fonctions SDL----------------------------------------------------------- //

// Bambou
void afficheBambou(SDL_Renderer* rendu, int positionX, int positionY, int nbBambou) {
    
    for (int i = 0; i < nbBambou; i++){
        SDL_Rect bambou;
        bambou.x = positionX;
        bambou.y = positionY;
        bambou.w = 10;
        bambou.h = 30;
        SDL_SetRenderDrawColor(rendu, 173, 255, 47, 255);	//pinceau vert
        SDL_RenderFillRect(rendu, &bambou);
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
        SDL_RenderDrawRect(rendu, &bambou);
        positionY -= 31;
        SDL_RenderPresent(rendu);//on rafraichit
    } 
}

// ----------------------------------------------Fin fonctions SDL----------------------------------------------------------- //



int main(int argn, char* argv[]) {


    Bambou bambouseraie[TAILLE_MAX];

    // tests

    /*cout << " Debut " << endl << endl;
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
    ReduceFaster(6, bambouseraie, 5);*/
    
    // SDL (interface graphique)





    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Echec à l’ouverture";
        return 1;
    }
    //on ouvre la police de caractères
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\calibri.ttf", 25);

    //on crée la fenêtre
    SDL_Window* win = SDL_CreateWindow("PandaRobot",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1080,
        720,
        SDL_WINDOW_SHOWN
    );




    if (win == NULL)
        cout << "erreur ouverture fenetre";

    SDL_Renderer* rendu = SDL_CreateRenderer(
        win,
        -1,
        SDL_RENDERER_ACCELERATED);


    //fin parametres fenetres 

    // debut des dessin sur l'ecran

    //Fond 1 bleu
    SDL_Rect rect1;

    rect1.x = 0;
    rect1.y = 0;
    rect1.w = 1080;
    rect1.h = 720;
    SDL_SetRenderDrawColor(rendu, 176, 224, 230, 255);	//pinceau bleu
    SDL_RenderFillRect(rendu, &rect1);

    // Fond 2
    SDL_Rect rect2;

    rect1.x = 0;
    rect1.y = 520;
    rect1.w = 1080;
    rect1.h = 200;
    SDL_SetRenderDrawColor(rendu, 0, 250, 154, 255);	//pinceau vert
    SDL_RenderFillRect(rendu, &rect1);

    // ligne pour le sol des bambou

    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderDrawLine(rendu, 0, 600, 1080, 600);


    //////


    int a = 2, b = 4, c = 3, d = 1, e = 5;

    // creation des bambous 
    CreateBambou(bambouseraie[0], a);
    CreateBambou(bambouseraie[1], b);
    CreateBambou(bambouseraie[2], c);
    CreateBambou(bambouseraie[3], d);
    CreateBambou(bambouseraie[4], e);

    for (int i = 0; i < 1000; i++) {
        // affichage des bambous 
        afficheBambou(rendu, 150, 570, bambouseraie[0].taille);
        afficheBambou(rendu, 250, 570, bambouseraie[1].taille);
        afficheBambou(rendu, 350, 570, bambouseraie[2].taille);
        afficheBambou(rendu, 450, 570, bambouseraie[3].taille);
        afficheBambou(rendu, 550, 570, bambouseraie[4].taille);
        afficheBambou(rendu, 550, 570, bambouseraie[0].taille);

        // test dans la console
        for (int i = 0; i < 5; i++) {
            cout << " avant : " << bambouseraie[i].taille << endl;
        }
        cout << endl;

        // croissance des bambous
        GrowBambou(bambouseraie[0]);
        GrowBambou(bambouseraie[1]);
        GrowBambou(bambouseraie[2]);
        GrowBambou(bambouseraie[3]);
        GrowBambou(bambouseraie[4]);

        int indice_a_couper = ReduceMax(bambouseraie, 5);
        bambouseraie[indice_a_couper].taille = bambouseraie[indice_a_couper].croissance;
        
        // test dans la console
        for (int i = 0; i < 5; i++) {
            cout << " apres : " << bambouseraie[i].taille << endl;
        }
        cout << endl;
        

        // remet ajour l'ecran avec les bonne tailles des bambous en affichant le fond de la fenetre 
        SDL_Rect rect1;

        rect1.x = 0;
        rect1.y = 0;
        rect1.w = 1080;
        rect1.h = 720;
        SDL_SetRenderDrawColor(rendu, 176, 224, 230, 255);	//pinceau bleu
        SDL_RenderFillRect(rendu, &rect1);

        // Fond 2
        SDL_Rect rect2;

        rect1.x = 0;
        rect1.y = 520;
        rect1.w = 1080;
        rect1.h = 200;
        SDL_SetRenderDrawColor(rendu, 0, 250, 154, 255);	//pinceau vert
        SDL_RenderFillRect(rendu, &rect1);

        // ligne pour le sol des bambou

        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderDrawLine(rendu, 0, 600, 1080, 600);
        system("pause");
    }
    
    

    //////

 
    SDL_RenderPresent(rendu);//on rafraichit

        /*************BOUCLE D'evenements**************/

    bool continuer = true;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:

            continuer = false;
            break;
        }
    }
    //destruction du renderer à la fin
    SDL_DestroyRenderer(rendu);
    //destruction à la fin
    SDL_DestroyWindow(win);

    TTF_CloseFont(font);
    TTF_Quit();


    //fermeture
    SDL_Quit();

    // -------------------------------------------------------------------------------------------------------------------------//


    return 0;
}