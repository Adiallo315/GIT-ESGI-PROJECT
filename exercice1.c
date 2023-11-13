#include <stdio.h>

int main(){
    int saisi_1 = 0;

    printf("Entrez un nombre :  ");
    scanf("%d \n", &saisi_1);

    printf("-------------------");

    int saisie_2= 0;
    printf("Entrez un nombre :  ");
    scanf("%d", &saisie_2);

    int resultat = 0;


    resultat = saisi_1 * saisie_2;

    printf("Le resultt de %d * %d = %d", saisi_1, saisie_2, resultat);
}