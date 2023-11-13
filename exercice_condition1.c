#include <stdio.h>

int main() {
    int age;

    printf("Entrez votre age : ");
    scanf("%d", &age);

    if (age >= 18) {
        printf("Vous êtes majeur.\n");
    } else {
        printf("Vous êtes mineur.\n");
    }

    return 0;
}
