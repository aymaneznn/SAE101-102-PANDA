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
    }
    
}

// ----------------------------------------------Fin fonctions SDL----------------------------------------------------------- //



int main(int argn, char* argv[]) {
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
        SDL_WINDOWPOS_CENTERED,     //pos. X: autre option: SDL_WINDOWPOS_UNDEFINED
        SDL_WINDOWPOS_CENTERED,     //pos. Y: autre option: SDL_WINDOWPOS_UNDEFINED 
        1080, 			//largeur en pixels			
        720, 			//hauteur en pixels
        SDL_WINDOW_SHOWN //d’autres options (plein ecran, resizable, sans bordure...)
    );
    if (win == NULL)
        cout << "erreur ouverture fenetre";
    //Création d’un dessin associé à la fenêtre (1 seul renderer par fenetre)
    SDL_Renderer* rendu = SDL_CreateRenderer(
        win,  //nom de la fenêtre
        -1, //par défaut
        SDL_RENDERER_ACCELERATED); //utilisation du GPU, valeur recommandée


    //fin parametres fenetres 

    // debut des dessin sur l'ecran

    //Fond 1 bleu
    SDL_Rect rect1; //on définit le rectangle à tracer
                   //SDL_Rect est un type struct	
    rect1.x = 0;  //coin en haut à gauche
    rect1.y = 0;  //coin en haut à gauche
    rect1.w = 1080;		//largeur
    rect1.h = 720;		//hauteur
    SDL_SetRenderDrawColor(rendu, 176, 224, 230,255);	//pinceau bleu
    SDL_RenderFillRect(rendu, &rect1); //on trace un rectangle plein

    // Fond 2
    SDL_Rect rect2; //on définit le rectangle à tracer
                   //SDL_Rect est un type struct	
    rect1.x = 0;  //coin en haut à gauche
    rect1.y = 520;  //coin en haut à gauche
    rect1.w = 1080;		//largeur
    rect1.h = 200;		//hauteur
    SDL_SetRenderDrawColor(rendu, 0, 250, 154, 255);	//pinceau vert
    SDL_RenderFillRect(rendu, &rect1); //on trace un rectangle plein

    //////

    afficheBambou(rendu, 50, 570, 5);

    //////
    
    // ligne pour le sol des bambou

    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderDrawLine(rendu, 0,600 ,1080 , 600);

    SDL_RenderPresent(rendu);//on rafraichit
		/*************BOUCLE D'evenements**************/

	bool continuer = true;   //booléen fin de programme
	SDL_Event event;//gestion des évènements souris/clavier, 
					//SDL_Event est de type struct
    while (continuer)
    {
        SDL_WaitEvent(&event);//attente d’un évènement
        switch (event.type) //test du type d’évènement
        {
        case SDL_QUIT: //clic sur la croix de fermeture
                       //on peut enlever SDL_Delay
            continuer = false;
            break;
        }
    }
	//destruction du renderer à la fin
	SDL_DestroyRenderer(rendu);
	//destruction à la fin
	SDL_DestroyWindow(win);   //equivalent du delete

	TTF_CloseFont(font); //on ferme la font
	TTF_Quit(); //on quitte la TTF


	//fermeture
	SDL_Quit();

    return 0;
}