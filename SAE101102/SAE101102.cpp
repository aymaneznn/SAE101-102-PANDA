using namespace std;
#include<SDL.h> 
#include<SDL_ttf.h> 
#include<iostream>
#include "config_sdl.h"
#include <fstream>
#include <sstream>
#include "SDL_image.h"
#include<ctime>


SDL_Renderer* rendu;
TTF_Font* font;
SDL_TimerID timer;
const int TAILLE_MAX = 100;
const int seuil = 10;
int parametres[8] = { 0 };
int manuell;

int max1 = 0;
int max2 = 0;
const int taille = 8;
int indice_batterie = 0;

// Definition des bambou
struct Bambou {
    int croissance;
    int taille;
};

Bambou bambouseraie[TAILLE_MAX];

// Statistiques 

// Statistique de la taille maximum de la bambouseraie
int TaillleMax(Bambou tab[], int TailleChoisie) {
    int maximum = 0;
    for (int i = 0; i < TailleChoisie; i++) {
        if (tab[i].taille > maximum) {
            maximum = tab[i].taille;
        }
    }
    return maximum;
}

// Statistique de la taille moyenne de la bambouseraie

int TailleMoy(Bambou tab[], int taille) {
    int total = 0;
    int nb = 0;
    for (int i = 0; i < taille; i++) {
        if (tab[i].taille != 0) {
            nb++;
        }
        total += tab[i].taille;
    }
    if (nb == 0) {
        nb = 1;
    }
    return total / nb;
}

// Statistique de la taille minimum de la bambouseraie
int TailleMin(Bambou tab[], int taille) {
    int min = TaillleMax(tab, 8);
    for (int i = 0; i < taille; i++) {
        if (tab[i].taille < min && tab[i].taille>0) {
            min = tab[i].taille;
        }
    }
    return min;
}

// Création d'un bambou
void CreateBambou(Bambou& bambou, int taille) {
    bambou.croissance = taille;
    bambou.taille = taille;
}

// Initialisation de bambouraie
void InitBamboueraie(Bambou bambouraie[], int taille, int tab[]) {
    srand(time(NULL));
    for (int i = 0; i < taille; i++) {
        CreateBambou(bambouraie[i], parametres[i]);
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

void VerifMax2BOT(Bambou bambouseraie[]) {
    int TailleMax1 = 0;
    int TailleMax2 = 0;
    for (int i = 0; i < taille; i++) {
        if (TailleMax1 < bambouseraie[i].taille) {
            TailleMax1 = bambouseraie[i].taille;
            max1 = i;
        }

    }
    for (int i = 0; i < taille; i++) {
        if (TailleMax2 < bambouseraie[i].taille && bambouseraie[i].taille != TailleMax1) {
            TailleMax2 = bambouseraie[i].taille;
            max2 = i;
        }
    }
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

void save() {
    ofstream sortie("save.txt", ios::trunc);
    for (int i = 0; i < taille; i++) {
        sortie << parametres[i] << " ";
    }
    sortie.close();
}

void load() {
    ifstream entre("save.txt", ios::in);
    for (int i = 0; i < taille; i++) {
        entre >> parametres[i];
        cout << parametres[i];
    }
    entre.close();
}

//--------------------------------------------------Fonctions SDL----------------------------------------------------------- //

// Fond
void fond(SDL_Renderer* rendu) {
    char name[] = "fond_pixelv2.bmp";
    //char name2[] = "herbev2.bmp";

    SDL_Surface* image = SDL_LoadBMP(name);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);

    SDL_Rect dstrect = { 0,0,1080,700 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture);

    /*SDL_Surface* image2 = SDL_LoadBMP(name2);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image2);

    SDL_Rect dstrect2 = { 0,600,1080,100 };
    SDL_RenderCopy(rendu, texture2, NULL, &dstrect2);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture2);*/
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

        if (positionY > 0) {
            positionY -= 40;
        }
        
        SDL_DestroyTexture(texture);
    }
}

// Robot Panda
void afficheRobot(SDL_Renderer* rendu, int positionX, int positionY) {
    char name[] = "pandav2.bmp";
    SDL_Surface* image = SDL_LoadBMP(name);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);
    SDL_Rect dstrect = { positionX,positionY,100,100 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture);
}

//exit
void exit() {
    char name[] = "exit.bmp";
    SDL_Surface* image = SDL_LoadBMP(name);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);
    SDL_Rect dstrect = { 950,650,100,50 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture);
}

void exit_menu() {
    char name[] = "exit.bmp";
    SDL_Surface* image = SDL_LoadBMP(name);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);
    SDL_Rect dstrect = { 1150,590,100,50 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture);
}

// menu
void menu() {
    char name[] = "menuv2.bmp";
    SDL_Surface* image = SDL_LoadBMP(name);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);
    SDL_Rect dstrect = { 0,0,1360,720 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture);
}

// Echange deux nombres dans un tableau
void exch(int tab[], int i, int j) {
    int temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
}

// Ajout dynamique dans un tableau de taille 18
void ajout(int tab[], int truc) {
    for (int i = 1; i < 19; i++) {
        exch(tab, i, i - 1);
    }
    tab[18] = truc;
}

//image batterie
void batterie(char nom[]) {
    SDL_Surface* image = SDL_LoadBMP(nom);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);
    SDL_Rect dstrect = { 900,10,200 ,100 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture);
}

// fond recharge
void fond_recharge() {
    SDL_Surface* image = SDL_LoadBMP("fond_recharge.bmp");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, image);
    SDL_Rect dstrect = { 0,0,1080 ,700 };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture);

    image = SDL_LoadBMP("eclair.bmp");
    SDL_Texture* eclair = SDL_CreateTextureFromSurface(rendu, image);
    dstrect = { 830,210,100,116 };
    SDL_RenderCopy(rendu, eclair, NULL, &dstrect);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(eclair);
}

bool repos = false;

// affiche le bon level batterie 
void batterie_lv1() {
    char lv1[] = "batterie_lv1.bmp";
    char lv2[] = "batterie_lv2.bmp";
    char lv3[] = "batterie_lv3.bmp";
    char names[] = "batterie_lv3.bmp";
    if (indice_batterie <= 5) {
        batterie(lv3);
    }
    if (indice_batterie >= 5 && indice_batterie < 10) {
        batterie(lv2);
    }
    if (indice_batterie >= 10) {
        batterie(lv1);
    }
    if (indice_batterie >= 15) {
        fond_recharge();
        repos = true;
        if (indice_batterie == 20) {
            indice_batterie = 0;
            repos = false;
            fond(rendu);
        }
        //batterie_lv1();
    }
    indice_batterie++;
    if(repos){
        SDL_Delay(800);
    }

}

int interval = 10;
Uint32 event1(Uint32 interval, void* param) {

    // definition des tableaux des stats
    int tabMax[19] = { 0 };
    int tabMoy[19] = { 0 };
    int tabMin[19] = { 0 };

    // variables
    int number = 0;
    int xx = 0;
    int yy = -80;
    int posx = 180;
    int h = 10;
    // creation des bambous 
    InitBamboueraie(bambouseraie, 8, parametres);

    // boucle infinie
    bool boucle = true;
    for (int i = 0; boucle; i++) {

        exit();
        batterie_lv1();
        if (repos == false) {

            // affichage des bambous 
            afficheBambou(rendu, 150, 510, bambouseraie[0].taille);
            afficheBambou(rendu, 250, 510, bambouseraie[1].taille);
            afficheBambou(rendu, 350, 510, bambouseraie[2].taille);
            afficheBambou(rendu, 450, 510, bambouseraie[3].taille);
            afficheBambou(rendu, 550, 510, bambouseraie[4].taille);
            afficheBambou(rendu, 650, 510, bambouseraie[5].taille);
            afficheBambou(rendu, 750, 510, bambouseraie[6].taille);
            afficheBambou(rendu, 850, 510, bambouseraie[7].taille);
        }

        // test dans la console
        for (int i = 0; i < 8; i++) {
            cout << "Bambou " << i + 1 << " : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
        }
        cout << endl;

        // croissance des bambous
        for (int i = 0; i < 8; i++) {
            GrowBambou(bambouseraie[i]);
        }

        // Mode repos du Panda
        if (repos == false) {
            int indice_a_couper = ReduceMax(bambouseraie, 8);
            bambouseraie[indice_a_couper].taille = bambouseraie[indice_a_couper].croissance;

            SDL_Delay(800);

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
            else if (indice_a_couper == 5) {
                afficheRobot(rendu, 700, 570);
            }
            else if (indice_a_couper == 6) {
                afficheRobot(rendu, 800, 570);
            }
            else if (indice_a_couper == 7) {
                afficheRobot(rendu, 900, 570);
            }

            // Le soleil se lève à tout jamais
            char soleil[] = "soleiv2.bmp";
            SDL_Surface* image5 = SDL_LoadBMP(soleil);
            SDL_Texture* texture5 = SDL_CreateTextureFromSurface(rendu, image5);
            SDL_Rect dstrect5 = { xx,yy,300,300 };
            SDL_RenderCopy(rendu, texture5, NULL, &dstrect5);
            SDL_RenderPresent(rendu);
            if (xx == 1000) {
                xx = 0;
            }
            xx += 50;
            SDL_DestroyTexture(texture5);
        }

        SDL_Rect Noir = { 1080,0,280,720 };
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderFillRect(rendu, &Noir);

        number++;
        string tmp = to_string(number);
        char text[200] = "Jours : ";
        char const* num_char = tmp.c_str();
        strcat_s(text, 200, num_char);
        SDL_Color blanc = { 255,255,255 }; //on définit une couleur de texte
        SDL_Rect positionTexte; //rectangle définissant le positionnement du texte, et sa taille

        //on place le texte au point (100,100)

        positionTexte.x = 1130;
        positionTexte.y = 25;

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

        //on détruit la texture
        SDL_DestroyTexture(texture);

        SDL_Color rouge = { 255,0,0 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 100;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Maximum", rouge, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        SDL_Rect graphMax;
        graphMax.x = 1130;
        graphMax.y = 125;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
        ajout(tabMax, TaillleMax(bambouseraie, 8));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 205 - (tabMax[i - 1] * 4), 1130 + (i * 10), 205 - (tabMax[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        SDL_Color vert = { 0,255,0 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 255;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Moyenne", vert, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 280;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
        ajout(tabMoy, TailleMoy(bambouseraie, 8));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 360 - (tabMoy[i - 1] * 4), 1130 + (i * 10), 360 - (tabMoy[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        SDL_Color bleu = { 100,100,255 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 410;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Minimum", bleu, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 435;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 100, 100, 255, 255);
        ajout(tabMin, TailleMin(bambouseraie, 8));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 515 - (tabMin[i - 1] * 4), 1130 + (i * 10), 515 - (tabMin[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        blanc = { 255,255,255 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 565;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Overview", blanc, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 590;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMax[i - 1] * 4), 1130 + (i * 10), 670 - (tabMax[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMoy[i - 1] * 4), 1130 + (i * 10), 670 - (tabMoy[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 100, 100, 255, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMin[i - 1] * 4), 1130 + (i * 10), 670 - (tabMin[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
        SDL_RenderDrawRect(rendu, &graphMax);

    }

    SDL_RenderPresent(rendu);//on rafraichit

    return interval;
}

Uint32 event2(Uint32 interval, void* param) {

    // definition des tableaux des stats
    int tabMax[19] = { 0 };
    int tabMoy[19] = { 0 };
    int tabMin[19] = { 0 };

    // variables
    int number = 0;
    int xx = 0;
    int yy = -80;

    // creation des bambous 
    InitBamboueraie(bambouseraie, 8, parametres);

    // boucle infinie
    bool boucle = true;
    for (int i = 0; boucle; i++) {

        exit();
        batterie_lv1();
        if (repos == false) {
            // affichage des bambous 
            afficheBambou(rendu, 150, 510, bambouseraie[0].taille);
            afficheBambou(rendu, 250, 510, bambouseraie[1].taille);
            afficheBambou(rendu, 350, 510, bambouseraie[2].taille);
            afficheBambou(rendu, 450, 510, bambouseraie[3].taille);
            afficheBambou(rendu, 550, 510, bambouseraie[4].taille);
            afficheBambou(rendu, 650, 510, bambouseraie[5].taille);
            afficheBambou(rendu, 750, 510, bambouseraie[6].taille);
            afficheBambou(rendu, 850, 510, bambouseraie[7].taille);
        }
        // test dans la console
        for (int i = 0; i < 8; i++) {
            cout << "Bambou " << i + 1 << " : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
        }
        cout << endl;

        // croissance des bambous
        for (int i = 0; i < 8; i++) {
            GrowBambou(bambouseraie[i]);
        }

        if (repos == false) {
            int indice_a_couper = ReduceFaster(seuil, bambouseraie, 8);
            bambouseraie[indice_a_couper].taille = bambouseraie[indice_a_couper].croissance;

            SDL_Delay(800);

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
            else if (indice_a_couper == 5) {
                afficheRobot(rendu, 700, 570);
            }
            else if (indice_a_couper == 6) {
                afficheRobot(rendu, 800, 570);
            }
            else if (indice_a_couper == 7) {
                afficheRobot(rendu, 900, 570);
            }

            // Le soleil se lève à tout jamais
            char soleil[] = "soleiv2.bmp";
            SDL_Surface* image5 = SDL_LoadBMP(soleil);
            SDL_Texture* texture5 = SDL_CreateTextureFromSurface(rendu, image5);
            SDL_Rect dstrect5 = { xx,yy,300,300 };
            SDL_RenderCopy(rendu, texture5, NULL, &dstrect5);
            SDL_RenderPresent(rendu);
            if (xx == 1000) {
                xx = 0;
            }
            xx += 50;
            SDL_DestroyTexture(texture5);
        }

        SDL_Rect Noir = { 1080,0,280,720 };
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderFillRect(rendu, &Noir);

        number++;
        string tmp = to_string(number);
        char text[200] = "Jours : ";
        char const* num_char = tmp.c_str();
        strcat_s(text, 200, num_char);
        SDL_Color blanc = { 255,255,255 }; //on définit une couleur de texte
        SDL_Rect positionTexte; //rectangle définissant le positionnement du texte, et sa taille

        //on place le texte au point (100,100)
        positionTexte.x = 850;
        positionTexte.y = 0;

        positionTexte.x = 1130;
        positionTexte.y = 25;

        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        SDL_Texture* texture = loadText(rendu, text, blanc, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //si on veut modifier le cadre du texte
        positionTexte.w *= 3;
        positionTexte.h *= 3;
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        exit();
        //on détruit la texture
        exit();
        SDL_DestroyTexture(texture);

        SDL_Color rouge = { 255,0,0 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 100;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Maximum", rouge, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        SDL_Rect graphMax;
        graphMax.x = 1130;
        graphMax.y = 125;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
        ajout(tabMax, TaillleMax(bambouseraie, 8));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 205 - (tabMax[i - 1] * 4), 1130 + (i * 10), 205 - (tabMax[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        SDL_Color vert = { 0,255,0 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 255;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Moyenne", vert, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 280;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
        ajout(tabMoy, TailleMoy(bambouseraie, 8));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 360 - (tabMoy[i - 1] * 4), 1130 + (i * 10), 360 - (tabMoy[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        SDL_Color bleu = { 100,100,255 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 410;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Minimum", bleu, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 435;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 100, 100, 255, 255);
        ajout(tabMin, TailleMin(bambouseraie, 8));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 515 - (tabMin[i - 1] * 4), 1130 + (i * 10), 515 - (tabMin[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        blanc = { 255,255,255 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 565;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Overview", blanc, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 590;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMax[i - 1] * 4), 1130 + (i * 10), 670 - (tabMax[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMoy[i - 1] * 4), 1130 + (i * 10), 670 - (tabMoy[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 100, 100, 255, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMin[i - 1] * 4), 1130 + (i * 10), 670 - (tabMin[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
        SDL_RenderDrawRect(rendu, &graphMax);

    }

    SDL_RenderPresent(rendu);//on rafraichit

    return interval;
}

Uint32 event3(Uint32 interval, void* param) {

    // definition des tableaux des stats
    int tabMax[19] = { 0 };
    int tabMoy[19] = { 0 };
    int tabMin[19] = { 0 };

    // variables
    int number = 0;
    int xx = 0;
    int yy = -80;
    // creation des bambous 
    InitBamboueraie(bambouseraie, 8, parametres);

    // boucle infinie
    bool boucle = true;
    for (int i = 0; boucle; i++) {

        exit();
        batterie_lv1();

        if (repos == false) {
            // affichage des bambous 
            afficheBambou(rendu, 150, 510, bambouseraie[0].taille);
            afficheBambou(rendu, 250, 510, bambouseraie[1].taille);
            afficheBambou(rendu, 350, 510, bambouseraie[2].taille);
            afficheBambou(rendu, 450, 510, bambouseraie[3].taille);
            afficheBambou(rendu, 550, 510, bambouseraie[4].taille);
            afficheBambou(rendu, 650, 510, bambouseraie[5].taille);
            afficheBambou(rendu, 750, 510, bambouseraie[6].taille);
            afficheBambou(rendu, 850, 510, bambouseraie[7].taille);
        }
        // test dans la console
        for (int i = 0; i < 8; i++) {
            cout << "Bambou " << i + 1 << " : " << bambouseraie[i].taille << " | il croie de : " << bambouseraie[i].croissance << endl;
        }
        cout << endl;

        VerifMax2BOT(bambouseraie);

        // croissance des bambous
        for (int i = 0; i < 8; i++) {
            GrowBambou(bambouseraie[i]);
        }

        if (repos == false) {
            int indice_a_couper1 = max1;
            cout << "max1 " << max1 << endl;
            cout << "max2 " << max2 << endl;
            int indice_a_couper2 = max2;
            bambouseraie[indice_a_couper1].taille = bambouseraie[indice_a_couper1].croissance;
            bambouseraie[indice_a_couper2].taille = bambouseraie[indice_a_couper2].croissance;

            SDL_Delay(800);

            // mis à jour de l'ecran avec les bonne tailles des bambous en affichant le fond de la fenetre 
            fond(rendu);

            //system("pause");

            // les endroits ou le Robot spawn

            if (indice_a_couper1 == 0) {
                afficheRobot(rendu, 200, 570);
            }
            else if (indice_a_couper1 == 1) {
                afficheRobot(rendu, 300, 570);
            }
            else if (indice_a_couper1 == 2) {
                afficheRobot(rendu, 400, 570);
            }
            else if (indice_a_couper1 == 3) {
                afficheRobot(rendu, 500, 570);
            }
            else if (indice_a_couper1 == 4) {
                afficheRobot(rendu, 600, 570);
            }
            else if (indice_a_couper1 == 5) {
                afficheRobot(rendu, 700, 570);
            }
            else if (indice_a_couper1 == 6) {
                afficheRobot(rendu, 800, 570);
            }
            else if (indice_a_couper1 == 7) {
                afficheRobot(rendu, 900, 570);
            }

            // les endroits ou le Robot spawn
            if (indice_a_couper2 == 0) {
                afficheRobot(rendu, 200, 570);
            }
            else if (indice_a_couper2 == 1) {
                afficheRobot(rendu, 300, 570);
            }
            else if (indice_a_couper2 == 2) {
                afficheRobot(rendu, 400, 570);
            }
            else if (indice_a_couper2 == 3) {
                afficheRobot(rendu, 500, 570);
            }
            else if (indice_a_couper2 == 4) {
                afficheRobot(rendu, 600, 570);
            }
            else if (indice_a_couper2 == 5) {
                afficheRobot(rendu, 700, 570);
            }
            else if (indice_a_couper2 == 6) {
                afficheRobot(rendu, 800, 570);
            }
            else if (indice_a_couper2 == 7) {
                afficheRobot(rendu, 900, 570);
            }

            // Le soleil se lève à tout jamais
            char soleil[] = "soleiv2.bmp";
            SDL_Surface* image5 = SDL_LoadBMP(soleil);
            SDL_Texture* texture5 = SDL_CreateTextureFromSurface(rendu, image5);
            SDL_Rect dstrect5 = { xx,yy,300,300 };
            SDL_RenderCopy(rendu, texture5, NULL, &dstrect5);
            SDL_RenderPresent(rendu);
            if (xx == 1000) {
                xx = 0;
            }
            xx += 50;
            SDL_DestroyTexture(texture5);
        }

        SDL_Rect Noir = { 1080,0,280,720 };
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderFillRect(rendu, &Noir);

        number++;
        string tmp = to_string(number);
        char text[200] = "Jours : ";
        char const* num_char = tmp.c_str();
        strcat_s(text, 200, num_char);
        SDL_Color blanc = { 255,255,255 }; //on définit une couleur de texte
        SDL_Rect positionTexte; //rectangle définissant le positionnement du texte, et sa taille

        //on place le texte au point (100,100)
        positionTexte.x = 850;
        positionTexte.y = 0;
        positionTexte.x = 1130;
        positionTexte.y = 25;

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

        //on détruit la texture
        SDL_DestroyTexture(texture);

        SDL_Color rouge = { 255,0,0 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 100;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Maximum", rouge, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        SDL_Rect graphMax;
        graphMax.x = 1130;
        graphMax.y = 125;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
        ajout(tabMax, TaillleMax(bambouseraie, 8));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 205 - (tabMax[i - 1] * 4), 1130 + (i * 10), 205 - (tabMax[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        SDL_Color vert = { 0,255,0 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 255;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Moyenne", vert, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 280;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
        ajout(tabMoy, TailleMoy(bambouseraie, 8));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 360 - (tabMoy[i - 1] * 4), 1130 + (i * 10), 360 - (tabMoy[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        SDL_Color bleu = { 100,100,255 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 410;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Minimum", bleu, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 435;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 100, 100, 255, 255);
        ajout(tabMin, TailleMin(bambouseraie, 8));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 515 - (tabMin[i - 1] * 4), 1130 + (i * 10), 515 - (tabMin[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        blanc = { 255,255,255 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 565;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Overview", blanc, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 590;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMax[i - 1] * 4), 1130 + (i * 10), 670 - (tabMax[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMoy[i - 1] * 4), 1130 + (i * 10), 670 - (tabMoy[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 100, 100, 255, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMin[i - 1] * 4), 1130 + (i * 10), 670 - (tabMin[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
        SDL_RenderDrawRect(rendu, &graphMax);

    }

    SDL_RenderPresent(rendu);//on rafraichit

    return interval;
}

Uint32 manual(Uint32 interval, void* param) {

    // definition des tableaux des stats
    int tabMax[19] = { 0 };
    int tabMoy[19] = { 0 };
    int tabMin[19] = { 0 };

    // variables
    int number = 0;
    int parametres[6] = { 1,2,3,4,5,6 };
    int xx = 0;
    int yy = -80;
    // creation des bambous 
    InitBamboueraie(bambouseraie, 6, parametres);

    fond(rendu);
    // boucle infinie
    bool boucle = true;
    for (int i = 0; boucle; i++) {
        batterie_lv1();
        
        if (repos == false) {
            // affichage des bambous 
            afficheBambou(rendu, 150, 570, bambouseraie[0].taille);
            afficheBambou(rendu, 250, 570, bambouseraie[1].taille);
            afficheBambou(rendu, 350, 570, bambouseraie[2].taille);
            afficheBambou(rendu, 450, 570, bambouseraie[3].taille);
            afficheBambou(rendu, 550, 570, bambouseraie[4].taille);
            afficheBambou(rendu, 550, 570, bambouseraie[4].taille);
            SDL_RenderPresent(rendu);
            SDL_Delay(800);

            //system("pause");

            if (manuell == 1) {
                CutBambou(bambouseraie[0]);
            }
            if (manuell == 2) {
                CutBambou(bambouseraie[1]);
            }
            if (manuell == 3) {
                CutBambou(bambouseraie[2]);
            }
            if (manuell == 4) {
                CutBambou(bambouseraie[3]);
            }
            if (manuell == 5) {
                CutBambou(bambouseraie[4]);
            }
        }

        // croissance des bambous
        for (int i = 0; i < 5; i++) {
            GrowBambou(bambouseraie[i]);
        }

        if (repos == false) {
            fond(rendu);

            // Le soleil se lève à tout jamais
            char soleil[] = "soleiv2.bmp";
            SDL_Surface* image5 = SDL_LoadBMP(soleil);
            SDL_Texture* texture5 = SDL_CreateTextureFromSurface(rendu, image5);
            SDL_Rect dstrect5 = { xx,yy,300,300 };
            SDL_RenderCopy(rendu, texture5, NULL, &dstrect5);
            SDL_RenderPresent(rendu);
            if (xx == 1000) {
                xx = 0;
            }
            xx += 50;
            SDL_DestroyTexture(texture5);
        }

        // Graphes
        SDL_Rect Noir = { 1080,0,280,720 };
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderFillRect(rendu, &Noir);

        //graphs
        number++;
        string tmp = to_string(number);
        char text[200] = "Jours : ";
        char const* num_char = tmp.c_str();
        strcat_s(text, 200, num_char);
        SDL_Color blanc = { 255,255,255 }; //on définit une couleur de texte
        SDL_Rect positionTexte; //rectangle définissant le positionnement du texte, et sa taille

        //on place le texte au point (100,100)
        positionTexte.x = 850;
        positionTexte.y = 0;
        positionTexte.x = 1130;
        positionTexte.y = 25;

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

        //on détruit la texture
        SDL_DestroyTexture(texture);

        SDL_Color rouge = { 255,0,0 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 100;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Maximum", rouge, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        SDL_Rect graphMax;
        graphMax.x = 1130;
        graphMax.y = 125;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
        ajout(tabMax, TaillleMax(bambouseraie, 5));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 205 - (tabMax[i - 1] * 4), 1130 + (i * 10), 205 - (tabMax[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        SDL_Color vert = { 0,255,0 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 255;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Moyenne", vert, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 280;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
        ajout(tabMoy, TailleMoy(bambouseraie, 5));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 360 - (tabMoy[i - 1] * 4), 1130 + (i * 10), 360 - (tabMoy[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        SDL_Color bleu = { 100,100,255 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 410;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Minimum", bleu, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 435;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 100, 100, 255, 255);
        ajout(tabMin, TailleMin(bambouseraie, 5));
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 515 - (tabMin[i - 1] * 4), 1130 + (i * 10), 515 - (tabMin[i] * 4));
        }
        SDL_RenderDrawRect(rendu, &graphMax);

        blanc = { 255,255,255 }; //on définit une couleur de texte
        positionTexte.x = 1130;
        positionTexte.y = 565;
        //on crée une texture à partir du texte, de sa couleur, et de la fonte
        texture = loadText(rendu, "Overview", blanc, font);
        //on maj le rectangle couvrant cette texture
        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
        //on copie la texture dans le rendu
        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on détruit la texture
        SDL_DestroyTexture(texture);
        graphMax.x = 1130;
        graphMax.y = 590;
        graphMax.w = 180;
        graphMax.h = 80;
        SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMax[i - 1] * 4), 1130 + (i * 10), 670 - (tabMax[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMoy[i - 1] * 4), 1130 + (i * 10), 670 - (tabMoy[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 100, 100, 255, 255);
        for (int i = 1; i < 19; i++) {
            SDL_RenderDrawLine(rendu, 1130 + ((i - 1) * 10), 670 - (tabMin[i - 1] * 4), 1130 + (i * 10), 670 - (tabMin[i] * 4));
        }
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
        SDL_RenderDrawRect(rendu, &graphMax);

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

    //on crée la fenêtre
    SDL_Window* win = SDL_CreateWindow("PandaRobot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1360, 720, SDL_WINDOW_SHOWN);

    if (win == NULL)
        cout << "erreur ouverture fenetre";

    rendu = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    //fin parametres fenetres 

    menu();

    SDL_Rect bb1;
    bb1.x = 612;
    bb1.y = 485;
    bb1.w = 62;
    bb1.h = 75;
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    //SDL_RenderDrawRect(rendu, &bb1);

    SDL_Rect bb2;
    bb2.x = 686;
    bb2.y = 485;
    bb2.w = 62;
    bb2.h = 75;
    //SDL_RenderDrawRect(rendu, &bb2);

    SDL_Rect bb3;
    bb3.x = 760;
    bb3.y = 485;
    bb3.w = 62;
    bb3.h = 75;
    //SDL_RenderDrawRect(rendu, &bb3);

    SDL_Rect bb4;
    bb4.x = 834;
    bb4.y = 485;
    bb4.w = 62;
    bb4.h = 75;
    //SDL_RenderDrawRect(rendu, &bb4);

    SDL_Rect bb5;
    bb5.x = 908;
    bb5.y = 485;
    bb5.w = 62;
    bb5.h = 75;
    //SDL_RenderDrawRect(rendu, &bb5);

    SDL_Rect bb6;
    bb6.x = 982;
    bb6.y = 485;
    bb6.w = 62;
    bb6.h = 75;
    //SDL_RenderDrawRect(rendu, &bb6);

    SDL_Rect bb7;
    bb7.x = 1056;
    bb7.y = 485;
    bb7.w = 62;
    bb7.h = 75;
    //SDL_RenderDrawRect(rendu, &bb7);

    SDL_Rect bb8;
    bb8.x = 1130;
    bb8.y = 485;
    bb8.w = 62;
    bb8.h = 75;
    //SDL_RenderDrawRect(rendu, &bb8);

    SDL_Rect ss;
    ss.x = 730;
    ss.y = 54;
    ss.w = 310;
    ss.h = 86;
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 0);

    SDL_Rect rect2;
    rect2.x = 884;
    rect2.y = 208;
    rect2.w = 260;
    rect2.h = 80;
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 0);

    SDL_Rect rect3;
    rect3.x = 624;
    rect3.y = 208;
    rect3.w = 260;
    rect3.h = 80;
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 0);

    SDL_Rect retour;
    retour.x = 1150;
    retour.y = 590;
    retour.w = 100;
    retour.h = 50;

    SDL_SetRenderDrawColor(rendu, 254, 254, 254, 255);

    SDL_Rect exit;
    exit.x = 950;
    exit.y = 650;
    exit.w = 100;
    exit.h = 50;
    SDL_SetRenderDrawColor(rendu, 254, 254, 254, 255);

    SDL_Rect manuel;
    manuel.x = 612;
    manuel.y = 346;
    manuel.w = 540;
    manuel.h = 100;
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 0);
    exit_menu();

    SDL_Rect bambou1;
    bambou1.x = 200;
    bambou1.y = 370;
    bambou1.w = 15;
    bambou1.h = 300;
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 0);	//pinceau vert
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir

    SDL_Rect bambou2;
    bambou2.x = 300;
    bambou2.y = 370;
    bambou2.w = 15;
    bambou2.h = 300;
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 0);	//pinceau vert
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 0); //pinceau noir


    SDL_Rect bambou3;
    bambou3.x = 400;
    bambou3.y = 370;
    bambou3.w = 15;
    bambou3.h = 300;
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);	//pinceau vert
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir;

    SDL_Rect bambou4;
    bambou4.x = 500;
    bambou4.y = 370;
    bambou4.w = 15;
    bambou4.h = 300;
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);	//pinceau vert
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir

    SDL_Rect bambou5;
    bambou5.x = 600;
    bambou5.y = 370;
    bambou5.w = 15;
    bambou5.h = 300;
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);	//pinceau vert
    //SDL_RenderFillRect(rendu, &bambou5);
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255); //pinceau noir
    //SDL_RenderDrawRect(rendu, &bambou5);

    SDL_Color blanc = { 0,0,0 }; //on définit une couleur de texte
    SDL_Rect positionTexte;
    SDL_Rect Save;
    Save.x = 620;
    Save.y = 585;
    Save.w = 200;
    Save.h = 50;
    SDL_RenderDrawRect(rendu, &Save);
    positionTexte.x = 660;
    positionTexte.y = 580;
    SDL_Texture* texture = loadText(rendu, "Save", blanc, font);
    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
    positionTexte.w *= 4;
    positionTexte.h *= 4;
    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(rendu);

    SDL_Rect Load;
    Load.x = 870;
    Load.y = 585;
    Load.w = 200;
    Load.h = 50;
    SDL_RenderDrawRect(rendu, &Load);
    positionTexte.x = 910;
    positionTexte.y = 580;
    texture = loadText(rendu, "Load", blanc, font);
    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
    positionTexte.w *= 4;
    positionTexte.h *= 4;
    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(rendu);

    /*************BOUCLE D'evenements**************/

    bool continuer = true;
    SDL_Event event;
    int champ = 0;
    blanc = { 0,0,0 };
    positionTexte;

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
                timer = SDL_AddTimer(interval, manual, NULL);
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) { //touche a
                continuer = false;
            }
            if (event.key.keysym.sym == SDLK_b) { //touche b
                timer = SDL_AddTimer(interval, event2, NULL);
            }

            if (champ != 0) {
                if (event.key.keysym.sym == SDLK_0) { //touche 0
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 0;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "0", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
                if (event.key.keysym.sym == SDLK_1) { //touche 1
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 1;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "1", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
                if (event.key.keysym.sym == SDLK_2) { //touche 2
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 2;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "2", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
                if (event.key.keysym.sym == SDLK_3) { //touche 3
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 3;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "3", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
                if (event.key.keysym.sym == SDLK_4) { //touche 4
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 4;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "4", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
                if (event.key.keysym.sym == SDLK_5) { //touche 5
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 5;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "5", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
                if (event.key.keysym.sym == SDLK_6) { //touche 6
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 6;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "6", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
                if (event.key.keysym.sym == SDLK_7) { //touche 7
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 7;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "7", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
                if (event.key.keysym.sym == SDLK_8) { //touche 8
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 8;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "8", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
                if (event.key.keysym.sym == SDLK_9) { //touche 9
                    SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                    SDL_Rect dstrect = { 607 + (74 * (champ - 1)),488,72,70 };
                    SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                    SDL_RenderPresent(rendu);
                    SDL_DestroyTexture(texture2);

                    parametres[champ - 1] = 9;
                    positionTexte.x = 625 + (74 * (champ - 1));
                    champ = 0;
                    positionTexte.y = 484;
                    SDL_Texture* texture = loadText(rendu, "9", blanc, font);
                    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                    positionTexte.w *= 5;
                    positionTexte.h *= 5;
                    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                    SDL_DestroyTexture(texture);
                    SDL_RenderPresent(rendu);
                }
            }
            break;
            SDL_RemoveTimer(timer);
        case SDL_MOUSEBUTTONUP://appui souris
            if (event.button.button == SDL_BUTTON_LEFT) {//si on clique bouton gauche
                if (event.button.x > rect2.x && event.button.x<rect2.x + rect2.w && event.button.y>rect2.y && event.button.y < rect2.y + rect2.h) { //dans 	le rectangle
                    cout << "faster" << endl;
                    fond(rendu);
                    timer = SDL_AddTimer(interval, event2, NULL);
                }
                if (event.button.x > ss.x && event.button.x<ss.x + ss.w && event.button.y>ss.y && event.button.y < ss.y + ss.h) { //dans 	le rectangle
                    cout << "manuel" << endl;
                    fond(rendu);
                    timer = SDL_AddTimer(interval, event3, NULL);
                }
                if (event.button.x > rect3.x && event.button.x<rect3.x + rect3.w && event.button.y>rect3.y && event.button.y < rect3.y + rect3.h) { //dans 	le rectangle
                    cout << "max" << endl;
                    fond(rendu);
                    timer = SDL_AddTimer(interval, event1, NULL);
                }
                if (event.button.x > manuel.x && event.button.x<manuel.x + manuel.w && event.button.y>manuel.y && event.button.y < manuel.y + manuel.h) { //dans 	le rectangle
                    cout << "Manuel" << endl;
                    fond(rendu);
                    timer = SDL_AddTimer(interval, manual, NULL);
                }
                if (event.button.x > retour.x && event.button.x<retour.x + retour.w && event.button.y>retour.y && event.button.y < retour.y + retour.h) { //dans 	le rectangle
                    cout << "retour" << endl;
                    continuer = false;
                    break;
                }
                if (event.button.x > bambou1.x && event.button.x<bambou1.x + bambou1.w && event.button.y>bambou1.y && event.button.y < bambou1.y + bambou1.h) { //dans 	le rectangle
                    cout << "bambou 1 " << endl;

                    manuell = 1;

                }
                if (event.button.x > bambou2.x && event.button.x<bambou2.x + bambou2.w && event.button.y>bambou2.y && event.button.y < bambou2.y + bambou2.h) { //dans 	le rectangle
                    cout << "bambou2" << endl;
                    manuell = 2;

                }
                if (event.button.x > bambou3.x && event.button.x<bambou3.x + bambou3.w && event.button.y>bambou3.y && event.button.y < bambou3.y + bambou3.h) { //dans 	le rectangle
                    cout << "bambou3" << endl;

                    manuell = 3;
                }
                if (event.button.x > bambou4.x && event.button.x<bambou4.x + bambou4.w && event.button.y>bambou4.y && event.button.y < bambou4.y + bambou4.h) { //dans 	le rectangle
                    cout << "bambou4" << endl;
                    fond(rendu);
                    manuell = 4;
                }
                if (event.button.x > bambou5.x && event.button.x<bambou5.x + bambou5.w && event.button.y>bambou5.y && event.button.y < bambou5.y + bambou5.h) { //dans 	le rectangle
                    cout << "bambou5" << endl;
                    fond(rendu);
                    manuell = 5;
                }
                if (event.button.x > retour.x && event.button.x<retour.x + retour.w && event.button.y>retour.y && event.button.y < retour.y + retour.h || event.button.x > exit.x && event.button.x<exit.x + exit.w && event.button.y>exit.y && event.button.y < exit.y + exit.h) {
                    cout << "retour" << endl;
                    continuer = false;
                    break;
                } //dans 	le rectangle
                if (event.button.x > bb1.x && event.button.x<bb1.x + bb1.w && event.button.y>bb1.y && event.button.y < bb1.y + bb1.h) { //dans 	le rectangle
                    cout << "bouton1" << endl;
                    /*SDL_SetRenderDrawColor(rendu, 0, 0, 0, 100);
                    SDL_RenderFillRect(rendu, &bb1);
                    SDL_RenderPresent(rendu);*/
                    champ = 1;
                    break;
                }
                if (event.button.x > bb2.x && event.button.x<bb2.x + bb2.w && event.button.y>bb2.y && event.button.y < bb2.y + bb2.h) { //dans 	le rectangle
                    cout << "bouton2" << endl;
                    /*SDL_SetRenderDrawColor(rendu, 0, 0, 0, 127);
                    SDL_RenderFillRect(rendu, &bb2);
                    SDL_RenderPresent(rendu);*/
                    champ = 2;
                    break;
                }
                if (event.button.x > bb3.x && event.button.x<bb3.x + bb3.w && event.button.y>bb3.y && event.button.y < bb3.y + bb3.h) { //dans 	le rectangle
                    cout << "bouton3" << endl;
                   /* SDL_SetRenderDrawColor(rendu, 0, 0, 0, 127);
                    SDL_RenderFillRect(rendu, &bb3);
                    SDL_RenderPresent(rendu);*/
                    champ = 3;
                    break;
                }
                if (event.button.x > bb4.x && event.button.x<bb4.x + bb4.w && event.button.y>bb4.y && event.button.y < bb4.y + bb4.h) { //dans 	le rectangle
                    cout << "bouton4" << endl;
                    /*SDL_SetRenderDrawColor(rendu, 0, 0, 0, 127);
                    SDL_RenderFillRect(rendu, &bb4);
                    SDL_RenderPresent(rendu);*/
                    champ = 4;
                    break;
                }
                if (event.button.x > bb5.x && event.button.x<bb5.x + bb5.w && event.button.y>bb5.y && event.button.y < bb5.y + bb5.h) { //dans 	le rectangle
                    cout << "bouton5" << endl;
                    /*SDL_SetRenderDrawColor(rendu, 0, 0, 0, 127);
                    SDL_RenderFillRect(rendu, &bb5);
                    SDL_RenderPresent(rendu);*/
                    champ = 5;
                    break;
                }
                if (event.button.x > bb6.x && event.button.x<bb6.x + bb6.w && event.button.y>bb6.y && event.button.y < bb6.y + bb6.h) { //dans 	le rectangle
                    cout << "bouton6" << endl;
                    /*SDL_SetRenderDrawColor(rendu, 0, 0, 0, 127);
                    SDL_RenderFillRect(rendu, &bb6);
                    SDL_RenderPresent(rendu);*/
                    champ = 6;
                    break;
                }
                if (event.button.x > bb7.x && event.button.x<bb7.x + bb7.w && event.button.y>bb7.y && event.button.y < bb7.y + bb7.h) { //dans 	le rectangle
                    cout << "bouton7" << endl;
                    /*SDL_SetRenderDrawColor(rendu, 0, 0, 0, 127);
                    SDL_RenderFillRect(rendu, &bb7);
                    SDL_RenderPresent(rendu);*/
                    champ = 7;
                    break;
                }
                if (event.button.x > bb8.x && event.button.x<bb8.x + bb8.w && event.button.y>bb8.y && event.button.y < bb8.y + bb8.h) { //dans 	le rectangle
                    cout << "bouton8" << endl;
                    /*SDL_SetRenderDrawColor(rendu, 0, 0, 0, 127);
                    SDL_RenderFillRect(rendu, &bb8);
                    SDL_RenderPresent(rendu);*/
                    champ = 8;
                    break;
                }
                if (event.button.x > Save.x && event.button.x<Save.x + Save.w && event.button.y>Save.y && event.button.y < Save.y + Save.h) { //dans 	le rectangle
                    cout << "sauvegarde" << endl;
                    save();
                    break;
                }
                if (event.button.x > Load.x && event.button.x<Load.x + Load.w && event.button.y>Load.y && event.button.y < Load.y + Load.h) { //dans 	le rectangle
                    cout << "charge" << endl;
                    load();
                    for (int i = 0; i < taille; i++) {
                        SDL_Surface* image = SDL_LoadBMP("Capture.bmp");
                        SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendu, image);
                        SDL_Rect dstrect = { 607 + (74 * i),488,72,70 };
                        SDL_RenderCopy(rendu, texture2, NULL, &dstrect);
                        SDL_RenderPresent(rendu);
                        SDL_DestroyTexture(texture2);

                        string tmp = to_string(parametres[i]);
                        char const* num_char = tmp.c_str();
                        positionTexte.x = 625 + (74 * i);
                        positionTexte.y = 484;
                        SDL_Texture* texture = loadText(rendu, num_char, blanc, font);
                        SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
                        positionTexte.w *= 5;
                        positionTexte.h *= 5;
                        SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
                        SDL_DestroyTexture(texture);
                        SDL_RenderPresent(rendu);
                    }
                }
            }
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

    return 0;
}
