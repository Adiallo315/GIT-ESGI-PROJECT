#include <stdio.h>

void convertisseurBinaire(int n) {
    for (int k = 7; k >= 0; k--) {
        printf("%d", (n >> k) & 1);
    }
    printf(".");
}


#define MAX_ADDRESS_IP 80
#define LONGUEUR_ADDRESS_IP 32

int main() {
    int id[MAX_ADDRESS_IP];
    char stock_adress[MAX_ADDRESS_IP][LONGUEUR_ADDRESS_IP];
    char masque[MAX_ADDRESS_IP][LONGUEUR_ADDRESS_IP];

    int nombreAddresseIp = 0;

    FILE* fp = fopen("adresses.csv", "r");
    if (fp != NULL) {
        while (nombreAddresseIp < MAX_ADDRESS_IP && fscanf(fp, "%d,%16[^,],%16s", &id[nombreAddresseIp], stock_adress[nombreAddresseIp], masque[nombreAddresseIp]) == 3) {
            nombreAddresseIp++;
        }
        fclose(fp);
    } else {
        printf("Fichier d'adresses introuvable. Un nouveau fichier a été créé.\n");
    }

    while (1) {
        printf("\nMenu Principal:\n");
        printf("1: Ajouter une nouvelle adresse IP\n");
        printf("2: Afficher les adresses IP\n");
        printf("3: Filtrage par masque\n");
        printf("3: Supprimer\n");
        printf("5: Quitter\n");

        printf("Choisissez une option : ");
        int choix;
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                if (nombreAddresseIp < MAX_ADDRESS_IP) {
                    printf("Entrez une adresse IP (format 192.168.1.0) : ");
                    scanf("%s", stock_adress[nombreAddresseIp]);

                    printf("Entrez un masque (format 255.255.0.0) : ");
                    scanf("%s", masque[nombreAddresseIp]);

                    id[nombreAddresseIp] = nombreAddresseIp + 1;
                    nombreAddresseIp++;
                } else {
                    printf("Le catalogue est plein. Impossible d'ajouter une nouvelle adresse IP.\n");
                }
                break;

            case 2:
                printf("\nAdresses IP enregistrées :\n");
                for (int i = 0; i < nombreAddresseIp; i++) {
                    printf("ID: %d, Adresse IP: %s, Masque: %s\n", id[i], stock_adress[i], masque[i]);
                }
                break;

            case 3: 


            case 5:
                fp = fopen("adresses.csv", "w");
                if (fp != NULL) {
                    for (int i = 0; i < nombreAddresseIp; i++) {
                        fprintf(fp, "%d,%s,%s\n", id[i], stock_adress[i], masque[i]);
                    }
                    fclose(fp);
                }
                printf("Au revoir !\n");
                return 0;

           

            default:
                printf("Option non valide\n");
                break;
        }
    }

    return 0;
}
