#include "bfile.h"
#include "stdio.h"

FILE* fichier;
BFILE* bfichier;

int main(int argc, char *argv[]) {
    FILE *fichier = NULL;
    if (argc > 1) {
        fichier = fopen(argv[1], "r");
        /* On ouvre le fichier dont le chemin est accessible via argv[1] */
        return;
    } else {
        return 1;
    }
}
