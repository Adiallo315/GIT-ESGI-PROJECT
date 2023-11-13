#include <stdio.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    char adresseIP[16];
    char masque[16];
    int choix;
    sqlite3 *db;
    char *sql = "CREATE TABLE IF NOT EXISTS Catalogue ("
                "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                "AdresseIP TEXT NOT NULL,"
                "Masque TEXT NOT NULL);";
    int rc = sqlite3_open("address.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        return 0;
    }

    rc = sqlite3_exec(db, sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "La table n'a pas pu être creer : %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stdout, "Table cree\n");
    }   
   
    do {
        printf("1: Add a new IP addres : \n"); 
        printf("2: List IP addresses \n");
        printf("3:  Search similar by mask \n"); 
        printf("4 :Delete an Ip \n"); 
        printf("5: quit \n"); 
        printf("Choose an option : "); 
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Entrez l'adresse IP : ");
            scanf("%s", adresseIP);

            printf("Entrez le masque : ");
            scanf("%s", masque);

            char insert_sql[100];
            sprintf(insert_sql, "INSERT INTO Catalogue (AdresseIP, Masque) VALUES ('%s', '%s');", adresseIP, masque);

            rc = sqlite3_e  xec(db, insert_sql, 0, 0, 0);

            if (rc != SQLITE_OK) {
            fprintf(stderr, "L'insertion ne s'effectue pas : %s\n", sqlite3_errmsg(db));
            } else {
                fprintf(stdout, "Insertion reussie\n");
                 }
            break;

        case 2:
            char *sqlSelect = "SELECT * FROM Catalogue;";  
            rc = sqlite3_exec(db, sqlSelect, callback, 0, 0);

            if (rc != SQLITE_OK) {
                fprintf(stderr, "Requete ne fonctionne pas : %s\n", sqlite3_errmsg(db));
            }
        
   

            break;

        case 3:
            printf("Pas d'implementation encore");
            char adresseIPFiltrage;
            char masqueFiltrage;
            
            int tableauEntierAdresseIP[];
            int indexIP = 0;



            printf("Entrez l'adresse IP : ");
            scanf("%s", adresseIPFiltrage);

            printf("Entrez le masque : ");
            scanf("%s", masqueFiltrage);

             int i = 0;
            while (adresseIPFiltrage[i] != '\0') {
                if (adresseIPFiltrage[i] == '.') {
                    adresseIPTableau[indexIP++] = adresseIPFiltrage[i - 1] - 48;
                }
                i++;
         }
             adresseIPTableau[indexIP] = adresseIPFiltrage[i - 1] - 48;
            printf("Adresse IP stockée : %d.%d.%d.%d\n", adresseIPTableau[0], adresseIPTableau[1], adresseIPTableau[2], adresseIPTableau[3]);




            break;


        case 4:
                int idSuppression;
                char sqlSuppression[100];
                printf("Entrez l'id a suprimer : ");
                scanf("%d", &idSuppression);
                sprintf(sqlSuppression, "DELETE FROM Catalogue WHERE ID = %d;", idSuppression);

                 rc = sqlite3_exec(db, sqlSuppression, 0, 0, 0);

                 if (rc != SQLITE_OK) {
                fprintf(stderr, "La suppression n'a pas pu etre effectuer  : %s\n", sqlite3_errmsg(db));
                return rc;
                } else {
                fprintf(stdout, "Suppression reussie\n");
                return SQLITE_OK;
                }
            break;

        case 5: 
            printf("Bye ! \n");
            break;
        
        default:
            printf("Option is not valide");
        }

    }while (choix != 5);

    sqlite3_close(db);
    return 0;
}


  