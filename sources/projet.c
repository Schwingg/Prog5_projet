#include "bfile.h"
#include "stdio.h"
#include "read_header.h"

FILE *fichier = NULL;
BFILE* bfichier;

void ferme(int error) {
    fclose(fichier);
    bstop(bfichier);
}

int main(int argc, char *argv[]) {

    if (argc == 2) {
        if ((fichier = fopen(argv[1], "r"))) {
            /* On ouvre le fichier dont le chemin est accessible via argv[1] */
        } else {
            printf("impossible de lire le fichier\n");
            return 1;
        }
        bfichier = bstart(fichier, "r");
        if (read_header(bfichier)) {
            ferme(0);
            return 0;
        } else {
            return 1;
        }
    } else {
        printf("Vous devez passer un fichier en parametre\n");
        printf("%s nom-du-fichier\n", argv[0]);
        return 1;
    }
}



