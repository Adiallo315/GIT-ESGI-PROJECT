#include <stdio.h>

void convertisseurBinaire(int n) {
    for (int k = 7; k >= 0; k--) {
        printf("%d", (n >> k) & 1);
    }
    printf(".");
}

int memeReseauBinaire(int ip1[4], int ip2[4], int masque[4]) {
    for (int i = 0; i < 4; i++) {
        if ((ip1[i] & masque[i]) != (ip2[i] & masque[i])) {
            return 0;
        }
    }
    return 1;
}


#define MAX_ADDRESS_IP 80
#define LONGUEUR_ADDRESS_IP 32

int main() {
    int id[MAX_ADDRESS_IP];
    char stock_adress[MAX_ADDRESS_IP][LONGUEUR_ADDRESS_IP];
    char masque[MAX_ADDRESS_IP][LONGUEUR_ADDRESS_IP];

    int nombreAddresseIp = 0;
      int choix;

    FILE* fp = fopen("adresses.csv", "r");
    if (fp != NULL) {
        while (nombreAddresseIp < MAX_ADDRESS_IP && fscanf(fp, "%d,%16[^,],%16s", &id[nombreAddresseIp], stock_adress[nombreAddresseIp], masque[nombreAddresseIp]) == 3) {
            nombreAddresseIp++;
        }
        fclose(fp);
    } else {
        printf("Fichier d'adresses introuvable. Un nouveau fichier a été créé.\n");
    }

    do {
        printf("\nMenu Principal:\n");
        printf("1: Ajouter une nouvelle adresse IP\n");
        printf("2: Afficher les adresses IP\n");
        printf("3: Filtrage par masque\n");
        printf("4: Supprimer\n");
        printf("5: Quitter\n");

        printf("Choisissez une option : ");
      
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


            case 3: {
                char adresseIPFiltrage[16];
                char masqueFiltrage[16];

                int adresseIPTableau[4] = {0};
                int indexIP = 0;
                int accumuleNumbreIP = 0;

                int masqueTableau[4] = {0};
                int indexMasque = 0;
                int accumuleNumbreMasque = 0;

                printf("Entrez l'adresse IP  : ");
                scanf("%s", adresseIPFiltrage);

                int i = 0;
                while (adresseIPFiltrage[i] != '\0') {
                    if (adresseIPFiltrage[i] == '.') {
                        adresseIPTableau[indexIP++] = accumuleNumbreIP;
                        accumuleNumbreIP = 0;
                    } else {
                        accumuleNumbreIP = accumuleNumbreIP * 10 + (adresseIPFiltrage[i] - '0');
                    }
                    i++;
                }
                adresseIPTableau[indexIP] = accumuleNumbreIP;

                printf("Adresse IP stockee : %d.%d.%d.%d\n", adresseIPTableau[0], adresseIPTableau[1], adresseIPTableau[2], adresseIPTableau[3]);

                printf("Entrez le masque  : ");
                scanf("%s", masqueFiltrage);

                int y = 0;
                while (masqueFiltrage[y] != '\0') {
                    if (masqueFiltrage[y] == '.') {
                        masqueTableau[indexMasque++] = accumuleNumbreMasque;
                        accumuleNumbreMasque = 0;
                    } else {
                        accumuleNumbreMasque = accumuleNumbreMasque * 10 + (masqueFiltrage[y] - '0');
                    }
                    y++;
                }
                masqueTableau[indexMasque] = accumuleNumbreMasque;

                printf("Masque stocke : %d.%d.%d.%d\n", masqueTableau[0], masqueTableau[1], masqueTableau[2], masqueTableau[3]);

                printf("Adresse IP en binaire : ");
                for (int j = 0; j < 4; j++) {
                    convertisseurBinaire(adresseIPTableau[j]);
                }
                printf("\n");

                printf("Masque IP en binaire : ");
                for (int j = 0; j < 4; j++) {
                    convertisseurBinaire(masqueTableau[j]);
                }
                printf("\n");

                printf("Résultat de l'ET logique : ");
                for (int j = 0; j < 4; j++) {
                    convertisseurBinaire(adresseIPTableau[j] & masqueTableau[j]);
                }
                printf("\n");

                int estDansLeMemeReseau = 0;
                for (int i = 0; i < nombreAddresseIp; i++) {
                    int reseau[4], masqueReseau[4];
                    sscanf(stock_adress[i], "%d.%d.%d.%d/%d.%d.%d.%d", &reseau[0], &reseau[1], &reseau[2], &reseau[3], &masqueReseau[0], &masqueReseau[1], &masqueReseau[2], &masqueReseau[3]);

                    int memeReseau = 1;
                    for (int j = 0; j < 4; j++) {
                        if ((adresseIPTableau[j] & masqueReseau[j]) != (reseau[j] & masqueReseau[j])) {
                            memeReseau = 0;
                            break;
                        }
                    }

                    if (memeReseau) {
                        printf("L'adresse IP appartient au même réseau que l'adresse stockée : %s\n", stock_adress[i]);
                        estDansLeMemeReseau = 1;
                        break;  
                    }
                }

                if (estDansLeMemeReseau) {
                    printf("L'adresse IP appartient à un réseau connu.\n");
                } else {
                    printf("L'adresse IP n'appartient à aucun réseau connu.\n");
                }
                break;
            }


            case 4:
                int idASupprimer;
                printf("Entrez l'ID de l'adresse IP a supprimer : ");
                scanf("%d", &idASupprimer);

                int indexASupprimer = -1;

                    
                for (int i = 0; i < nombreAddresseIp; i++) {
                    if (id[i] == idASupprimer) {
                    indexASupprimer = i;
                    break;
                    }
                }

                if (indexASupprimer != -1) {
                    for (int i = indexASupprimer; i < nombreAddresseIp - 1; i++) {
                        id[i] = id[i + 1];
                        for (int j = 0; j < 32; j++) {
                            stock_adress[i][j] = stock_adress[i + 1][j];
                            masque[i][j] = masque[i + 1][j];
                            }
                        }

                    nombreAddresseIp--;

                    printf("L'adresse IP avec l'ID %d a ete supprime.\n", idASupprimer);
                    } else {
                            printf("Aucune adresse IP trouvee avec l'ID %d.\n", idASupprimer);
                            }
                    break;



            case 5: 
                printf("Bye ! \n");
                    break;
                    
                default:
                    printf("Option is not valide");
                }

    }while (choix != 5);
        return 0;
}