#include <stdio.h>
#include "projet.h"
#include <string.h>
#include <stdlib.h>

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
    free(hed);
    free(symb);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        //allocation du header ELF à faire dans read_header.c
        if ((fichier = fopen(argv[1], "r"))) {
            // Open the file passed in argv[1] 
        } else {
            printf("impossible de lire le fichier\n");
            return 1;
        }
        
        //PART 1
        hed = read_header(fichier); // No error during header reading
        display_header(hed);
        if (hed->ELF == 1 && hed->EI_DATA == 0 && hed->EI_CLASS == 32) {
            ferme();
            
            //PART 2
            //Starting the reading of the section header
            fichier = fopen(argv[1], "r");
            //Section header allocation in section_header.c           
            sections = section_header(fichier, hed);
            display_sections_table(hed);
            ferme();
            
            //PART 3
            //Sections content reading
            fichier = fopen(argv[1], "r");
            if (read_section(fichier, sections, hed) == 1) {
                printf("Erreur lors de lallocation du pointeur");
                return 1;
            }
            
            //PART 4
            //Symbols reading
            int j, x, i;
            for (i = 0; i < hed->e_shnum; i++) {
                if (strcmp(sections[i]->sh_name, ".symtab") == 0) {
                    j = i;
                }
                if (strcmp(sections[i]->sh_name, ".strtab") == 0) {
                    x = i;
                }
            }
            symb = symbole_header(fichier, sections[j], sections[x]);
            display_symbols(sections[j], sections[x], symb);

			//PART 5
			//display_rel_sections(fichier, sections, hed->e_shnum);
			display_rel_a(sections, hed->e_shnum);
	    // Step 6 (not finished)
	    int a = 0;
	    // TODO : optimize the function call to get a
	    get_rel_sections(sections,hed->e_shnum,&a); // To get a (number of rel section)
	    num_section(hed,sections,a,fichier);

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
