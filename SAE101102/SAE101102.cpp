using namespace std;
#include<SDL.h> 
#include<SDL_ttf.h> 
#include<iostream>
#include "config_sdl.h"
#include <fstream>
#include <sstream>
#include "SDL_image.h"

SDL_Renderer* rendu;
TTF_Font* font;
const int TAILLE_MAX = 100;

const int seuil = 15;
// Definition des bambou
struct Bambou {
    int croissance;
    int taille;
};

Bambou bambouseraie[TAILLE_MAX];

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

// Statistique de la taille moyenne de la bambouseraie
float TailleMoy(Bambou tab[], int taille) {
    float total = 0;
    for (int i = 0; i < taille; i++) {
        total += tab[i].taille;
    }
    return total / taille;
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

// (rand() % 9) + 1)

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

    for (int i = 0; i < TailleChoisie; i++) {
        if (Bambou[i].taille > TailleMax) {
            TailleMax = Bambou[i].taille;
            indiceBambou = i;
        }
    }
    return indiceBambou;
}

// Coupe le bambou le plus grand
int ReduceMax(Bambou bambou[], int TailleChoisie) {
    int indice = VerifMax(bambou, TailleChoisie);
    bambou[indice].taille = bambou[indice].croissance;
    return indice;
}

// Fonction Reduce-Fastest(x)
int ReduceFaster(int seuil, Bambou tab[], int TailleChoisie) {
    int maxCroissance = 0;
    int indice = 0;
    for (int j = 0; j < TailleChoisie; j++) {
        if (tab[j].taille > seuil) {
            if (tab[j].croissance > maxCroissance) {
                maxCroissance = tab[j].croissance;
                indice = j;
            }
        }
    }
    return indice;
}

// Croissance simultané de la bambouraie
void GrowAll(Bambou bambouraie[], int taille) {
    for (int i = 0; i < taille; i++) {
        GrowBambou(bambouraie[i]);
    }
}

// --------------------------------------------------Fonctions SDL----------------------------------------------------------- //

// Fond
void fond(SDL_Renderer* rendu) {
    char name[] = "fond_pixel.bmp";
    char name2[] = "herbe.bmp";

    SDL_Surface* image = SDL_LoadBMP(name);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);

    SDL_Rect dstrect = { 0,0,1100,700 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);

    SDL_Surface* image2 = SDL_LoadBMP(name2);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image2);

    SDL_Rect dstrect2 = { 0,600,1080,100 };
    SDL_RenderCopy(rendu, texture2, NULL, &dstrect2);
    SDL_RenderPresent(rendu);

}

// Bambou
void afficheBambou(SDL_Renderer* rendu, int positionX, int positionY, int nbBambou) {
    char name[] = "bambouv2.bmp";
    for (int i = 0; i < nbBambou; i++) {

        SDL_Surface* image = SDL_LoadBMP(name);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);

        SDL_Rect dstrect = { positionX,positionY,100,150 };
        SDL_RenderCopy(rendu, texture, NULL, &dstrect);
        SDL_RenderPresent(rendu);
        positionY -= 35;
        //SDL_Rect bambou;
        //bambou.x = positionX;
        //bambou.y = positionY;
        //bambou.w = 10;
        //bambou.h = 30;
        //SDL_SetRenderDrawColor(rendu, 173, 255, 47, 255);	//pinceau vert
        //SDL_RenderFillRect(rendu, &bambou);
        //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
        //SDL_RenderDrawRect(rendu, &bambou);



        //SDL_Rect haut;
        //haut.x = positionX - 2;
        //haut.y = positionY + 31;
        //haut.w = 15;
        //haut.h = 5;
        //SDL_SetRenderDrawColor(rendu, 173, 255, 47, 255);	//pinceau vert
        //SDL_RenderFillRect(rendu, &haut);
        //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
        //SDL_RenderDrawRect(rendu, &haut);



        //SDL_Rect bas;
        //bas.x = positionX - 2;
        //bas.y = positionY;
        //bas.w = 15;
        //bas.h = 5;
        //SDL_SetRenderDrawColor(rendu, 173, 255, 47, 255);	//pinceau vert
        //SDL_RenderFillRect(rendu, &bas);
        //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
        //SDL_RenderDrawRect(rendu, &bas);
        //positionY -= 28;
        //SDL_RenderPresent(rendu);//on rafraichit
    }
}

// Robot Panda
void afficheRobot(SDL_Renderer* rendu, int positionX, int positionY) {

    char name[] = "panda.bmp";

    SDL_Surface* image = SDL_LoadBMP(name);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);

    SDL_Rect dstrect = { positionX,positionY,100,100 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);
    //SDL_Rect RobotPanda;
    //RobotPanda.x = positionX;
    //RobotPanda.y = positionY;
    //RobotPanda.w = 30;
    //RobotPanda.h = 30;
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &RobotPanda);
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &RobotPanda);
    //SDL_RenderPresent(rendu);//on rafraichit

    ////pieds
    //SDL_Rect pied_gauche;
    //pied_gauche.x = positionX;
    //pied_gauche.y = positionY + 30;
    //pied_gauche.w = 10;
    //pied_gauche.h = 10;
    //SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &pied_gauche);
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &pied_gauche);
    //SDL_RenderPresent(rendu);//on rafraichit

    //SDL_Rect pied_droite;
    //pied_droite.x = positionX + 20;
    //pied_droite.y = positionY + 30;
    //pied_droite.w = 10;
    //pied_droite.h = 10;
    //SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &pied_droite);
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &pied_droite);
    //SDL_RenderPresent(rendu);//on rafraichit

    ////bras
    //SDL_Rect bras_gauche;
    //bras_gauche.x = positionX - 10;
    //bras_gauche.y = positionY;
    //bras_gauche.w = 10;
    //bras_gauche.h = 10;
    //SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &bras_gauche);
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &bras_gauche);
    //SDL_RenderPresent(rendu);//on rafraichit

    ////bras
    //SDL_Rect outil;
    //outil.x = positionX - 70;
    //outil.y = positionY + 5;
    //outil.w = 80;
    //outil.h = 2;
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &outil);
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &outil);
    //SDL_RenderPresent(rendu);//on rafraichit

    //SDL_Rect bras_droite;
    //bras_droite.x = positionX + 30;
    //bras_droite.y = positionY;
    //bras_droite.w = 10;
    //bras_droite.h = 10;
    //SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &bras_droite);
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &bras_droite);
    //SDL_RenderPresent(rendu);//on rafraichit

    ////tête
    //SDL_Rect tete;
    //tete.x = positionX + 5;
    //tete.y = positionY - 10;
    //tete.w = 20;
    //tete.h = 20;
    //SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &tete);
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &tete);
    //SDL_RenderPresent(rendu);//on rafraichit

    //SDL_Rect oeil_gauche;
    //oeil_gauche.x = positionX + 8;
    //oeil_gauche.y = positionY - 5;
    //oeil_gauche.w = 5;
    //oeil_gauche.h = 5;
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &oeil_gauche);
    //SDL_SetRenderDrawColor(rendu, 254, 254, 254, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &oeil_gauche);
    //SDL_RenderPresent(rendu);//on rafraichit

    //SDL_Rect oeil_droit;
    //oeil_droit.x = positionX + 15;
    //oeil_droit.y = positionY - 5;
    //oeil_droit.w = 5;
    //oeil_droit.h = 5;
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &oeil_droit);
    //SDL_SetRenderDrawColor(rendu, 254, 254, 254, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &oeil_droit);
    //SDL_RenderPresent(rendu);//on rafraichit

    //SDL_Rect oreille_droit;
    //oreille_droit.x = positionX + 16;
    //oreille_droit.y = positionY - 20;
    //oreille_droit.w = 10;
    //oreille_droit.h = 10;
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &oreille_droit);
    //SDL_SetRenderDrawColor(rendu, 254, 254, 254, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &oreille_droit);
    //SDL_RenderPresent(rendu);//on rafraichit

    //SDL_Rect oreille_gauche;
    //oreille_gauche.x = positionX + 2;
    //oreille_gauche.y = positionY - 20;
    //oreille_gauche.w = 10;
    //oreille_gauche.h = 10;
    //SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &oreille_gauche);
    //SDL_SetRenderDrawColor(rendu, 254, 254, 254, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &oreille_gauche);
    //SDL_RenderPresent(rendu);//on rafraichit
}


int interval = 500;
Uint32 event1(Uint32 interval, void* param) {
    
    // variables
    int number = 0;
    int parametres[6] = { 1,2,3,4,5,6 };
    int xx = 0;
    int yy = 0;
    // creation des bambous 
    InitBamboueraie(bambouseraie, 6, parametres);

    // boucle infinie
    bool boucle = true;
    for (int i = 0; boucle; i++) {

        // affichage des bambous 
        afficheBambou(rendu, 150, 510, bambouseraie[0].taille);
        afficheBambou(rendu, 250, 510, bambouseraie[1].taille);
        afficheBambou(rendu, 350, 510, bambouseraie[2].taille);
        afficheBambou(rendu, 450, 510, bambouseraie[3].taille);
        afficheBambou(rendu, 550, 510, bambouseraie[4].taille);
        afficheBambou(rendu, 550, 510, bambouseraie[0].taille);

        

        // test dans la console
        for (int i = 0; i < 5; i++) {
            cout << "Bambou " << i + 1 << " : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
        }
        cout << endl;

        // croissance des bambous
        for (int i = 0; i < 5; i++) {
            GrowBambou(bambouseraie[i]);
        }

        int indice_a_couper = ReduceMax(bambouseraie, 5);
        bambouseraie[indice_a_couper].taille = bambouseraie[indice_a_couper].croissance;

        SDL_Delay(900);

        // mis à jour de l'ecran avec les bonne tailles des bambous en affichant le fond de la fenetre 
        fond(rendu);

        //system("pause");

        // les endroits ou le Robot spawn
        if (indice_a_couper == 0) {
            afficheRobot(rendu, 200, 570);
        }
        else if (indice_a_couper == 1) {
            afficheRobot(rendu, 300, 570);
        }
        else if (indice_a_couper == 2) {
            afficheRobot(rendu, 400, 570);
        }
        else if (indice_a_couper == 3) {
            afficheRobot(rendu, 500, 570);
        }
        else if (indice_a_couper == 4) {
            afficheRobot(rendu, 600, 570);
        }
        number++;
        string tmp = to_string(number);
        char text[200] = "Jour : ";
        char const* num_char = tmp.c_str();
        strcat_s(text, 200, num_char);
        SDL_Color blanc = { 255,255,255 }; //on définit une couleur de texte
        SDL_Rect positionTexte; //rectangle définissant le positionnement du texte, et sa taille

        //on place le texte au point (100,100)
        positionTexte.x = 850;
        positionTexte.y = 0;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        SDL_Texture* texture = loadText(rendu, text, blanc, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //si on veut modifier le cadre du texte
        positionTexte.w *= 3;
        positionTexte.h *= 3;
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);

        char solei[] = "soleiv2.bmp";

        SDL_Surface* image5 = SDL_LoadBMP(solei);
        SDL_Texture* texture5 = SDL_CreateTextureFromSurface(rendu, image5);

        SDL_Rect dstrect5 = { xx,yy,300,300 };
        SDL_RenderCopy(rendu, texture5, NULL, &dstrect5);
        SDL_RenderPresent(rendu);
        if (xx == 1000) {
            xx = 0 ;
        }
        xx += 50;
    }

    SDL_RenderPresent(rendu);//on rafraichit

    return interval;
}


Uint32 event2(Uint32 interval, void* param) {

    // variables
    int number = 0;
    int parametres[6] = { 1,2,3,4,5,6 };

    // creation des bambous 
    InitBamboueraie(bambouseraie, 6, parametres);

    // boucle infinie
    bool boucle = true;
    for (int i = 0; boucle; i++) {

        // affichage des bambous 
        afficheBambou(rendu, 150, 570, bambouseraie[0].taille);
        afficheBambou(rendu, 250, 570, bambouseraie[1].taille);
        afficheBambou(rendu, 350, 570, bambouseraie[2].taille);
        afficheBambou(rendu, 450, 570, bambouseraie[3].taille);
        afficheBambou(rendu, 550, 570, bambouseraie[4].taille);
        afficheBambou(rendu, 550, 570, bambouseraie[0].taille);



        // test dans la console
        for (int i = 0; i < 5; i++) {
            cout << "Bambou " << i + 1 << " : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
        }
        cout << endl;

        // croissance des bambous
        for (int i = 0; i < 5; i++) {
            GrowBambou(bambouseraie[i]);
        }

        int indice_a_couper = ReduceFaster(seuil,bambouseraie,5);
        bambouseraie[indice_a_couper].taille = bambouseraie[indice_a_couper].croissance;

        SDL_Delay(300);

        // mis à jour de l'ecran avec les bonne tailles des bambous en affichant le fond de la fenetre 
        fond(rendu);

        //system("pause");

        // les endroits ou le Robot spawn
        if (indice_a_couper == 0) {
            afficheRobot(rendu, 200, 570);
        }
        else if (indice_a_couper == 1) {
            afficheRobot(rendu, 300, 570);
        }
        else if (indice_a_couper == 2) {
            afficheRobot(rendu, 400, 570);
        }
        else if (indice_a_couper == 3) {
            afficheRobot(rendu, 500, 570);
        }
        else if (indice_a_couper == 4) {
            afficheRobot(rendu, 600, 570);
        }

        number++;
        string tmp = to_string(number);
        char text[200] = "Jour : ";
        char const* num_char = tmp.c_str();
        strcat_s(text, 200, num_char);
        SDL_Color blanc = { 255,255,255 }; //on définit une couleur de texte
        SDL_Rect positionTexte; //rectangle définissant le positionnement du texte, et sa taille

        //on place le texte au point (100,100)
        positionTexte.x = 850;
        positionTexte.y = 0;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        SDL_Texture* texture = loadText(rendu, text, blanc, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //si on veut modifier le cadre du texte
        positionTexte.w *= 3;
        positionTexte.h *= 3;
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);

    }

    SDL_RenderPresent(rendu);//on rafraichit

    return interval;
}




// ----------------------------------------------Fin fonctions SDL----------------------------------------------------------- //



int main(int argn, char* argv[]) {

    // SDL (interface graphique)

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Echec à l’ouverture";
        return 1;
    }
    //on ouvre la police de caractères
    TTF_Init();
    font = TTF_OpenFont("C:\\Windows\\Fonts\\calibri.ttf", 15);

    SDL_TimerID timer;

    //on crée la fenêtre
    SDL_Window* win = SDL_CreateWindow("PandaRobot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN);

    if (win == NULL)
        cout << "erreur ouverture fenetre";

    rendu = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    //fin parametres fenetres 

    char name[] = "ROBOT_PANDA.bmp";

    SDL_Surface* image = SDL_LoadBMP(name);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);

    SDL_Rect dstrect = { 0,0,1100,700 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);


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
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_a) { //touche a
                timer = SDL_AddTimer(interval, event1, NULL);
            }
            
            if (event.key.keysym.sym == SDLK_b) { //touche b
                timer = SDL_AddTimer(interval, event2, NULL);
            }
            break;
            SDL_RemoveTimer(timer);
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

    return 0;
}