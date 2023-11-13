#include <stdio.h>
#include <string.h>



 const int MAX_TACHES = 100;
int main() {
   
    char taches[MAX_TACHES][100]; 
    int compteurDeTaches = 0;
    
    int choix;
    int pos;
    do {
        printf("Menu :\n");
        printf("1: Ajouter une tâche\n");
        printf("2: Supprimer une tâche\n");
        printf("3: Mettre à jour une tâche\n");
        printf("4: Afficher les tâches\n");
        printf("0: Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                if (compteurDeTaches < MAX_TACHES) {
                    printf("Entrez la description de la tâche : ");
                    scanf(" %[^\n]", taches[compteurDeTaches]);
                    compteurDeTaches++;
                } else {
                    printf("Le tableau de tâches est plein. Impossible d'ajouter une nouvelle tâche.\n");
                }
                break;
            case 2:
            
                     for (int i = 0; i < compteurDeTaches; i++) {
                    printf("%d: %s\n", i + 1, taches[i]);
                    }
                    printf("Quelles taches vous voulais supprimer ? :");
                    scanf("%d", &pos);

                    if(pos > compteurDeTaches){
                        printf("suppression impossible.\n");
                    }
                    else{
                       for (int i = pos; i < compteurDeTaches - 1; i++) {
                       taches[i] == taches[i - 1];
                    }
                    compteurDeTaches--;
                    }
                    for (int i = 0; i < compteurDeTaches; i++) {
                    printf("%d: %s\n", i + 1, taches[i]);
                    }
                    
               
                break;
            case 3:

                break;
            case 4:
                printf("Tâches :\n");
                for (int i = 0; i < compteurDeTaches; i++) {
                    printf("%d: %s\n", i + 1, taches[i]);
                }
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option non valide. Veuillez choisir une option valide.\n");
        }
    } while (choix != 0);

    return 0;
}