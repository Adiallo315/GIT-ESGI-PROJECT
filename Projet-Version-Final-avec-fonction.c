#include <stdio.h>

#define MAX_ADDRESS_IP 80
#define LONGUEUR_ADDRESS_IP 32

void afficherMenu() {
    printf("\nMenu Principal:\n");
    printf("1: Ajouter une nouvelle adresse IP\n");
    printf("2: Afficher les adresses IP\n");
    printf("3: Filtrage par masque\n");
    printf("4: Supprimer\n");
    printf("5: Quitter\n");
}

int adresse_ip_valide(const char ip[]) {
    int points_ip = 0;
    int verif_points = 1;

    for (int i = 0; ip[i] != '\0'; i++) {
        if ((ip[i] < '0' || ip[i] > '9') && ip[i] != '.') {
            return 0;
        }

        if (ip[i] == '.') {
            if (verif_points) {
                return 0;
            }
            points_ip++;
            verif_points = 1;
        } else {
            verif_points = 0;
        }
    }

    if (points_ip != 3) {
        return 0;
    }

    int octet = 0;
    int points_ip_ = 0;

    for (int i = 0; ip[i] != '\0'; i++) {
        if (ip[i] == '.') {
            if (octet < 0 || octet > 255) {
                return 0;
            }
            octet = 0;
            points_ip_++;
        } else {
            octet = octet * 10 + (ip[i] - '0');
        }
    }

    if (octet < 0 || octet > 255 || points_ip_ != 3) {
        return 0;
    }

    return 1;
}

void copierChaine(char destination[], const char source[]) {
    int i;
    for (i = 0; source[i] != '\0'; i++) {
        destination[i] = source[i];
    }
    destination[i] = '\0';
}



int ajouterAdresseIP(int id[], char stock_adress[][LONGUEUR_ADDRESS_IP], char masque[][LONGUEUR_ADDRESS_IP], int nombreAddresseIp) {
    if (nombreAddresseIp < MAX_ADDRESS_IP) {
        char nouvelleAdresseIP[LONGUEUR_ADDRESS_IP];
        char nouveauMasque[LONGUEUR_ADDRESS_IP];

        printf("Entrez une adresse IP (format 192.168.1.0) : ");
        scanf("%s", nouvelleAdresseIP);

        
        if (!adresse_ip_valide(nouvelleAdresseIP)) {
            printf("Adresse IP invalide. Veuillez entrer une adresse IP valide.\n");
            
            return nombreAddresseIp;
        }

        printf("Entrez un masque (format 255.255.0.0) : ");
        scanf("%s", nouveauMasque);

        if (!adresse_ip_valide(nouveauMasque)) {
            printf("Masque IP invalide. Veuillez entrer un masque IP valide.\n");
            return nombreAddresseIp;
        }

        id[nombreAddresseIp] = nombreAddresseIp + 1;
        copierChaine(stock_adress[nombreAddresseIp], nouvelleAdresseIP);
        copierChaine(masque[nombreAddresseIp], nouveauMasque);


        nombreAddresseIp++;

        FILE* fichier = fopen("adresses.csv", "a");
        if (fichier != NULL) {
            fprintf(fichier, "%d %s %s\n", id[nombreAddresseIp - 1], stock_adress[nombreAddresseIp - 1], masque[nombreAddresseIp - 1]);
            fclose(fichier);
        }

       
        return nombreAddresseIp;
    } else {
        printf("Le catalogue est plein. Impossible d'ajouter une nouvelle adresse IP avec masque.\n");
        
        return nombreAddresseIp;
    }
}


void afficherAdressesIP(int nombreAddresseIp, int id[], char stock_adress[][LONGUEUR_ADDRESS_IP], char masque[][LONGUEUR_ADDRESS_IP]) {
    printf("\nAdresses IP enregistrées :\n");
    for (int i = 0; i < nombreAddresseIp; i++) {
        printf("ID: %d, Adresse IP: %s, Masque: %s\n", id[i], stock_adress[i], masque[i]);
    }
}


int supprimerAdresseIP(int nombreAddresseIp, int id[], char stock_adress[][LONGUEUR_ADDRESS_IP], char masque[][LONGUEUR_ADDRESS_IP]) {
    int idASupprimer;
    printf("Entrez l'ID de l'adresse IP à supprimer : ");
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
            for (int j = 0; j < LONGUEUR_ADDRESS_IP; j++) {
                stock_adress[i][j] = stock_adress[i + 1][j];
                masque[i][j] = masque[i + 1][j];
            }
        }

        printf("L'adresse IP avec l'ID %d a été supprimée.\n", idASupprimer);
        return nombreAddresseIp - 1;
    } else {
        printf("Aucune adresse IP trouvée avec l'ID %d.\n", idASupprimer);
        return nombreAddresseIp;
    }
}



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

int main() {
    int id[MAX_ADDRESS_IP];
    char stock_adress[MAX_ADDRESS_IP][LONGUEUR_ADDRESS_IP];
    char masque[MAX_ADDRESS_IP][LONGUEUR_ADDRESS_IP];

    int nombreAddresseIp = 0;
    int choix;

    FILE *fichier = fopen("adresses.csv", "r");
    if (fichier != NULL) {
        while (nombreAddresseIp < MAX_ADDRESS_IP && fscanf(fichier, "%d %s %s", &id[nombreAddresseIp], stock_adress[nombreAddresseIp], masque[nombreAddresseIp]) == 3) {
            nombreAddresseIp++;
        }
        fclose(fichier);
    } else {
        printf("Fichier d'adresses introuvable. Un nouveau fichier a été créé.\n");
    }

    do {
        afficherMenu();
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
              nombreAddresseIp = ajouterAdresseIP(id, stock_adress, masque, nombreAddresseIp);

                break;

            case 2:
                afficherAdressesIP(nombreAddresseIp, id, stock_adress, masque);
                break;

            case 3:
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
            


            case 4:
               nombreAddresseIp = supprimerAdresseIP(nombreAddresseIp, id, stock_adress, masque);

                break;

            case 5:
                printf("Bye ! \n");
                break;

            default:
                printf("Option is not valid\n");
        }

    } while (choix != 5);

    return 0;
}
