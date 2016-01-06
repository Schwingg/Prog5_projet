#define SEC 1 // need a section to get info (number or name)
#define SEC_OFF 0x44 // Offset of section SEC
#define SEC_SIZE 0x16 // Size of section SEC

#include <stdio.h>
#include <stdlib.h>
#include "read_header.h"
#include "section_header.h"
#include "read_section.h"


// FIXME : Bourrage du dernier octet observé

int read_section(FILE* fichier, SEC_HEADER **sections, HEADER *hed) {
    int i, j;
    unsigned int hex = 0x0;
    for (i = 0; i < hed->e_shnum; i++) {
        printf("Section %s\n", sections[i]->sh_name);
        fseek(fichier, htobe32(sections[i]->sh_offset), SEEK_SET);;
        for (j = htobe32(sections[i]->sh_offset); j < htobe32(sections[i]->sh_offset) + htobe32(sections[i]->sh_size); j = j + 4) {
            fread(&hex, 4, 1, fichier);
            hex = htobe32(hex);
            printf("%08x ", hex);
            hex = 0;
        }
        printf("\n");
    }

    //    fseek(fichier, SEC_OFF, SEEK_SET);
    //
    //    for (i = SEC_OFF; i < SEC_OFF + SEC_SIZE; i = i + 4) {
    //        fread(&hex, 4, 1, fichier);
    //        hex = htobe32(hex);
    //        printf("%x ", hex);
    //        //printf("%x ", i);
    //        hex = 0;
    //    }
    //    printf("\n");
    return 0;
}
