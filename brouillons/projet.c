#include <stdio.h>
#include "read_header.h"
#include <stdlib.h>
#include "section_header.h"
#include "symbolheader.h"
#include "projet.h"
#include <string.h>


//Closes the file

void ferme() {
    fclose(fichier);
}

//frees the structures
void desalloc() {
    int i;
    for (i = 1; i < hed->e_shnum; i++) {
        free(sections[i]);
    }
    free(sections);
    free(symb);
    free(hed);
    
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        //allocation du header ELF
        hed = (HEADER *) malloc(sizeof (HEADER));
        if (hed == NULL)
            return 1;
        if ((fichier = fopen(argv[1], "r"))) {
            /* Open the file passed in argv[1] */
        } else {
            printf("impossible de lire le fichier\n");
            return 1;
        }
        hed = read_header(fichier); // No error during header reading
        if (hed->ELF == 1 && hed->EI_DATA == 0 && hed->EI_CLASS == 32) {
            ferme();
            //Starting the reading of the section header
            (fichier = fopen(argv[1], "r"));
            //allocation du header de section
            sections = (SEC_HEADER **) malloc(hed->e_shnum * (sizeof (SEC_HEADER)));
            if (sections == NULL)
                return 1;
            int i;
            for (i = 0; i < hed->e_shnum; i++) {
                sections[i] = (SEC_HEADER*) malloc(sizeof (SEC_HEADER));
                if (sections[i] == NULL)
                    return 1;
            }
            sections = section_header(fichier, hed);
                    
            int j,x;
            for(i = 0 ; i < hed->e_shnum;i++) {
            		if (strcmp(sections[i]->sh_name,".symtab")==0)
            				j = i;
            		if (strcmp(sections[i]->sh_name,".strtab")==0)
            				x = i;
            }
           
           	
          	symb = symbole_header(fichier,sections[j],sections[x]);
            
            ferme();
            desalloc();
            return 0;
        } else {// Header reading returned an error
            ferme();
            free(hed);
            return 1;
        }
    } else {// argv[1] is empty
        printf("Vous devez passer un fichier en parametre\n");
        printf("%s nom-du-fichier\n", argv[0]);
        return 1;
    }
}



