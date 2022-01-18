#include <iostream>
using namespace std;
int main(){
    int  max = 0, smax = 0;
    int tab[] = { 1,2,3,4,100,1000,2000,600,800 };

    for (int i = 0; i < 9; i++) {

        if (max < tab[i]){
            max = tab[i];
        }
        /*if (smax < tab[i] && max != tab[i]){
            smax = tab[i];
        }*/
    }
    for (int i = 0; i < 9; i++) {

        if (smax < tab[i] && max != tab[i]) {
            smax = tab[i];
        }
    }

    cout << "Max : " << max << endl;
    cout << "Deuxieme max : " << smax << endl;
    return 0;

}