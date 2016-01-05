#include "stdio.h"
#include "read_header.h"
#include "projet.h"
#include "stdlib.h"

void ferme() {
    fclose(fichier);
}

int main(int argc, char *argv[]) {
    HEADER *hed;
    hed = (HEADER *) malloc(sizeof (HEADER));
    if (hed == NULL)
        return 1;
    if (argc == 2) {
        if ((fichier = fopen(argv[1], "r"))) {
            /* Open the file passed in argv[1] */
        } else {
            printf("impossible de lire le fichier\n");
            return 1;
        }
        hed = read_header(fichier); // No error during header reading
        if (hed->ELF == 1) {
            ferme();
            return 0;
        } else {// Header reading returned an error
            ferme();
            return 1;
        }
    } else {// argv[1] is empty
        printf("Vous devez passer un fichier en parametre\n");
        printf("%s nom-du-fichier\n", argv[0]);
        return 1;
    }
}



