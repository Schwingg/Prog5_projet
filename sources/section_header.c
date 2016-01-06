// ! Attention ! Usage de "htobe32" pour les architectures 64 bits
// en little endian, non testé pour la carte ARM en big endian 

#include <stdio.h>
#include <stdlib.h>
#include "read_header.h"
#include "section_header.h"

SEC_HEADER **section_header(FILE* fichier, HEADER* hed) {
    //(unsigned int)hed->e_shoff;
    //(unsigned int)hed->e_shentsize;
    //(unsigned int)hed->e_shstrndx;
    //(unsigned int)hed->e_shnum;
    unsigned int pos = 0;
    int i = 0;
    
    //Allocation of the sections header
    SEC_HEADER **sections = (SEC_HEADER **) malloc((unsigned int)hed->e_shnum * (sizeof (SEC_HEADER)));
    if (sections == NULL)
        return NULL;

    //Allocation of the sections's header parts
    for (i = 0; i < (unsigned int)hed->e_shnum; i++) {
        sections[i] = (SEC_HEADER*) malloc(sizeof (SEC_HEADER));
        if (sections[i] == NULL)
            return NULL;
    }

    fseek(fichier, ((unsigned int)hed->e_shstrndx * (unsigned int)hed->e_shentsize) + (unsigned int)hed->e_shoff + 16, SEEK_SET); // 5 * 4 - 3 bytes
    fread(&pos, sizeof (int), 1, fichier);
    pos = htobe32(pos);

    //Display the Names table position
    printf("Position de la table des noms : %x\n", pos);
    fseek(fichier, (unsigned int)hed->e_shoff, SEEK_SET);

    int idxName = 0;

    //for each section
    for (i = 0; i < (unsigned int)hed->e_shnum; i++) {
        idxName = 0;
        //store the name in sh_name
        sections[i]->sh_name = (char*) malloc(sizeof (char)*256);

        fread(&idxName, sizeof (int), 1, fichier);
        idxName = htobe32(idxName); // FIXME : check for ARM
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
            fseek(fichier, (unsigned int)hed->e_shoff + (40 * i) + 4, SEEK_SET);
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

    // Display the informations
    for (i = 0; i < (unsigned int)hed->e_shnum; i++) {
        printf("Type : %s\n", sections[i]->sh_name);
        printf("Flags : 0x%x\n", htobe32(sections[i]->sh_flags));
        printf("Adress : 0x%x\n", htobe32(sections[i]->sh_addr));
        printf("Offset : 0x%x\n", htobe32(sections[i]->sh_offset));
        printf("Size : 0x%x\n", htobe32(sections[i]->sh_size));
        printf("Link : 0x%x\n", htobe32(sections[i]->sh_link));
        printf("Info : 0x%x\n", htobe32(sections[i]->sh_info));
        printf("AddrAlign : 0x%x\n", htobe32(sections[i]->sh_addralign));
        printf("EntSize : 0x%x\n", htobe32(sections[i]->sh_entsize));
        printf("------------------\n");
    }


    return sections;
}
