#include <stdio.h>

int main() {
    int note;

    printf("Entrez votre note : ");
    scanf("%d", &note);

    if (note >= 90) {
        printf("Excellent!\n");
    } else if (note >= 70) {
        printf("Bien fait!\n");
    } else if (note >= 50) {
        printf("Passable.\n");
    } else {
        printf("Échec.\n");
    }

    return 0;
}
