#include "bfile.h"
#include "stdio.h"
#include "read_header.h"

int main(int argc, char *argv[]) {
    FILE *fichier = NULL;
    BFILE* bfichier;
    if (argc > 1) {
        fichier = fopen(argv[1], "r");
        /* On ouvre le fichier dont le chemin est accessible via argv[1] */
        bfichier = bstart(fichier, "r");
        if (read_header(bfichier)) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}



