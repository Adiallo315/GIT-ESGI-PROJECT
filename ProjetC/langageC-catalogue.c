#include <stdio.h>
#include <stdlib.h>
#include <string.h>


  FILE *addressIP = NULL;

/*int IsValidIp(char* szIP)
{
 int isValid;
int i;
int byte;
int iIpLen;
char dotCount;
    isValid = 1;
    iIpLen = strlen(szIP);
    dotCount = 0;
    // Si on nous donne une chaine de caractère vide ou bien que la chaine dépasse les 15 caractères ce n'est pas une bonne IP
    if(iIpLen == 0 || iIpLen > 15)
        {
            isValid = 0;
        }
        else
        {
        // On récupère le premier octet 
        byte = atoi(szIP);

        // S'il est plus grand que 255 alors ce n'est pas une IP valide 
        if(byte > 255)
        {
            isValid = 0;
        }

        // on parcours la chaine 
        for(i = 0; i < iIpLen && isValid == 1; i++)
        {
        // on check si on nous donne bien seulement des chiffres ou le point 
        if(!(szIP[i] >= '0' && szIP[i] <= '9') && szIP[i] != '.')
        {
            isValid = 0;
        }

    // on compte le nb de point 
    if(szIP[i] == '.')
    {
        dotCount ++;
    // puis on check si l'octet que l'on récupère est valide 
    byte = atoi(&szIP[i+1]);
    if(byte > 255)
        {
    isValid = 0;
    }
}
}
// s'il n'y a pas trois points dans l'ip alors ce n'est pas une ip valide 
 if(dotCount != 3)
 {
 isValid = 0;
 }

 }

    printf("isValid : %d",isValid);
 return isValid;
}*/

int main() {
   
       
    char choix;
    
    do {
        printf("Menu :\n");
        printf("a - Add a new IP address\n");
        printf("l - List IP addresses\n");
        printf("s - Search similar\n");
        printf("d - Delete an IP\n");
        printf("q - Quit\n");
        printf("Choisissez une option : ");
        scanf("%s", &choix);

        switch (choix) {
            case 'a':
                 addressIP = fopen("adressesIP.csv","a");
                        if (addressIP!=NULL){
        
                            //char* ip="";
                            //int adresse;
                            //int i;
                            //int erreur;
                            unsigned int ip1, ip2, ip3, ip4;
                            printf("ecrivez une adresse ip: ");
                            //scanf("%s",ip);
                             //printf("%s",ip);
                             /*for (i = 0; erreur == 0 && i < strlrn(ip); i++)
                             {
                             if (ip[i] == '0' )
                                {
                                    printf("Adresse IP invalide\n ");
                                    fclose(addressIP);
                                }
                                else if (ip[])
                                {
                                    
                                }
                             
                              */
                              
                                //adresse = IsValidIp(ip);

                               // printf("%d",adresse);
                                
 
                                if( scanf("%u.%u.%u.%u" , &ip1 , &ip2, &ip3, &ip4) != 4 ||
                                ip1>255 || ip2>255 || ip3>255 || ip4>255 )
                                printf("Saisie erronée\n");
                                
                                printf("%u.%u.%u.%u", ip1 , ip2, ip3, ip4);
                                //{
                                //printf("Saisie erronée\n");
                                //}
                                //else if (ip1,ip2,ip3,ip4 == '..','..','..','..' )
                                //{
                                  //  printf("Saisie erronée\n");
                                //}
                                

                                //else 
                               // {
                               // fprintf(addressIP,"%c",adresse);
                                //}
                            // }
                             fclose(addressIP);
                             

                         }
                        else{
                             printf("--error--");
                            exit(1);
                        }
                break;    
            case 'l':
             
                break;
            case 's':

                break;
            case 'd':
               
                break;
            case 'q':
                printf("Au revoir !\n");
                
                break;
            default:
                printf("Option non valide. Veuillez choisir une option valide.\n");
        }
    } while (choix != 'q');

    return 0;
}