#include <stdio.h>
#include <stdlib.h>
#include "read_header.h"
#include "section_header.h"
#include "read_section.h"


// FIXME : Bourrage du dernier octet observé

int read_section(FILE* fichier, SEC_HEADER **sections, HEADER *hed) {
    int i, j, k = 0;
    unsigned int hex = 0x0;
    for (i = 0; i < hed->e_shnum; i++) {
        printf("Section %s\n", sections[i]->sh_name);
        fseek(fichier, htobe32(sections[i]->sh_offset), SEEK_SET);
        ;
        for (j = htobe32(sections[i]->sh_offset); j < htobe32(sections[i]->sh_offset) + htobe32(sections[i]->sh_size); j = j + 4) {
            k++;
            fread(&hex, 4, 1, fichier);
            hex = htobe32(hex);
            printf("%08x ", hex);
            hex = 0;
            if (k % 4 == 0) {
                printf("\n");
            }
        }
        k = 0;
        printf("\n\n");
    }
    return 0;
}
