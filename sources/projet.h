
FILE *fichier = NULL;

HEADER *hed;

SEC_HEADER **sections;

/*
 Contains the project's main function, with file passed as a parameter
 */
int main(int argc, char *argv[]);


/*
 Allows to quit the program, specifying if a problem occurs
 */
void ferme();

/*
 Frees the structures used
 */
void desalloc();
