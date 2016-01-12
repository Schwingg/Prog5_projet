// ! Attention ! Usage de "htobe32" pour les architectures 64 bits
// en little endian, non testé pour la carte ARM en big endian 

#include <stdio.h>
#include <stdlib.h>
#include "projet.h"

SEC_HEADER **section_header(FILE* fichier, HEADER* hed) {
    unsigned int pos = 0;
    int i = 0;

    //Allocation of the sections header
    SEC_HEADER **sections = (SEC_HEADER **) malloc(hed->e_shnum * (sizeof (SEC_HEADER)));
    if (sections == NULL)
        return NULL;
    for (i = 0; i < hed->e_shnum; i++) {
        sections[i] = (SEC_HEADER*) malloc(sizeof (SEC_HEADER));
        if (sections[i] == NULL)
            return NULL;
    }
    //end of allocation of sections

    fseek(fichier, (hed->e_shstrndx * hed->e_shentsize) + hed->e_shoff + 16, SEEK_SET); // 5 * 4 - 3 bytes
    fread(&pos, sizeof (int), 1, fichier);
    pos = htobe32(pos);

    //Display the Names table position
    printf("Position de la table des noms : 0x%04X\n", pos);
    fseek(fichier, hed->e_shoff, SEEK_SET);

    int idxName = 0;

    //for each section
    for (i = 0; i < hed->e_shnum; i++) {
        idxName = 0;
        //store the name in sh_name
        sections[i]->sh_name = (char*) malloc(sizeof (char)*256);

        fread(&idxName, sizeof (int), 1, fichier);
        idxName = htobe32(idxName);
        if (idxName == 0) {
            if (i == 0)
                sections[i]->sh_name = "";
        } else {
            fseek(fichier, pos + idxName, SEEK_SET);
            char c = 2;
            int j = 0;
            while (c != 0) {
                c = fgetc(fichier);
                if (c)
                    sections[i]->sh_name[j] = c;
                else
                    sections[i]->sh_name[j] = '\0';
                j++;
            }
            fseek(fichier, hed->e_shoff + (40 * i) + 4, SEEK_SET);
        }

        //Store the rest of the information for this section
        fread(&sections[i]->sh_type, sizeof (int), 1, fichier);
        fread(&sections[i]->sh_flags, sizeof (int), 1, fichier);
        fread(&sections[i]->sh_addr, sizeof (int), 1, fichier);
        fread(&sections[i]->sh_offset, sizeof (int), 1, fichier);
        fread(&sections[i]->sh_size, sizeof (int), 1, fichier);
        fread(&sections[i]->sh_link, sizeof (int), 1, fichier);
        fread(&sections[i]->sh_info, sizeof (int), 1, fichier);
        fread(&sections[i]->sh_addralign, sizeof (int), 1, fichier);
        fread(&sections[i]->sh_entsize, sizeof (int), 1, fichier);
    }

    return sections;
}
