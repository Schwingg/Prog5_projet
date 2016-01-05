#include "stdio.h"
#include "read_header.h"

FILE *fichier = NULL;

void ferme() {
    fclose(fichier);
}

int main(int argc, char *argv[]) {

    if (argc == 2) {
        if ((fichier = fopen(argv[1], "r"))) {
            /* On ouvre le fichier dont le chemin est accessible via argv[1] */
        } else {
            printf("impossible de lire le fichier\n");
            return 1;
        }
        if (read_header(fichier)) {
            ferme();
            return 0;
        } else {
            ferme();
            return 1;
        }
    } else {
        printf("Vous devez passer un fichier en parametre\n");
        printf("%s nom-du-fichier\n", argv[0]);
        return 1;
    }
}



