#include <stdio.h>
#include <stdlib.h>
#include "projet.h"


//Displays each section's content in hex format

int read_section(FILE* fichier, SEC_HEADER **sections, HEADER *hed) {
    int i, j, k = 0;
    unsigned int hex = 0x0;
    for (i = 0; i < hed->e_shnum; i++) {//for each section
        printf("Section %s\n", sections[i]->sh_name);
        fseek(fichier, htobe32(sections[i]->sh_offset), SEEK_SET);
        printf("addr |                data");
        printf("\n------------------------------------------");
        for (j = htobe32(sections[i]->sh_offset); j < htobe32(sections[i]->sh_offset) + htobe32(sections[i]->sh_size); j = j + 4) {
            //Return to line
            if (k %4  == 0) {
                printf("\n%04x | ", j);
            }
            k++;
            fread(&hex, 4, 1, fichier);
            hex = htobe32(hex);
            printf("%08x ", hex);
            hex = 0;
        }
        k = 0;
        printf("\n------------------------------------------\n");
        printf("addr |      data");
        printf("\n\n");
    }
    return 0;
}
