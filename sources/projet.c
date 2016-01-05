

FILE* fichier;
BFILE* bfichier;

int main(int argc, char *argv[]) {

    FILE *fichier = NULL;

    char caractere;

    if (argc > 1) {

        fichier = fopen(argv[1], "r"); /* On ouvre le fichier dont le chemin est accessible via argv[1] */

    }

}
