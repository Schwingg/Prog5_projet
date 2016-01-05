

int main (int argc, char *argv[])

{

    FILE *fichier = NULL;

    char caractere;

    if (argc > 1)

    {

        fichier = fopen (argv[1], "r"); /* On ouvre le fichier dont le chemin est accessible via argv[1] */

    }


    if (fichier != NULL)

    {

        do

        {

            caractere = fgetc (fichier);

            printf("%c", caractere);

        } while (caractere != EOF);

    }

    else exit(EXIT_FAILURE);


    getchar();


    return EXIT_SUCCESS;

}
