
#include "projet.h"


//Displays each section's content in hex format

int read_section(FILE* fichier, SEC_HEADER **sections, HEADER *hed) {
    int i, j, k = 0;
    unsigned int hex = 0x0;
    for (i = 0; i < hed->e_shnum; i++) {//for each section
        fseek(fichier, htobe32(sections[i]->sh_offset), SEEK_SET);
        for (j = htobe32(sections[i]->sh_offset); j < htobe32(sections[i]->sh_offset) + htobe32(sections[i]->sh_size); j = j + 4) {
            if (k %4  == 0) {
            }
            k++;
            fread(&hex, 4, 1, fichier);
            hex = htobe32(hex);
            hex = 0;
        }
        k = 0;
    }
    return 0;
}
