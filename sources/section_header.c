#define SEC_HEAD_IDX 0x1b0 // TODO : Get value from ELF header           e_shoff
#define SEC_SIZE 40 // TODO : Get value from ELF header              e_shentsize
#define SEC_NAME_NO 12 // TODO : Get value from ELF header            e_shstrndx
#define SEC_NBR 15 // TODO : Get value from ELF header                   e_shnum

// ! Attention ! Usage de "htobe32" pour les architectures 64 bits
// en little endian, non testé pour la carte ARM en big endian 

#include <stdio.h>
#include <stdlib.h>
#include "read_header.h"
#include "section_header.h"

SEC_HEADER *section_header(FILE* fichier, HEADER* hed) {

    //FILE* fichier;
    fichier = fopen("example1.o", "r");


    int pos = 0, i = 0;
    SEC_HEADER **sections = (SEC_HEADER **) malloc(SEC_NBR * (sizeof (SEC_HEADER)));
    if (sections == NULL)
        return NULL;

    for (i = 0; i < SEC_NBR; i++) {
        sections[i] = (SEC_HEADER*) malloc(sizeof (SEC_HEADER));
        if (sections[i] == NULL)
            return NULL;
    }

    fseek(fichier, (SEC_NAME_NO * SEC_SIZE) + SEC_HEAD_IDX + 17, SEEK_SET); // 5 * 4 - 3 bytes
    fread(&pos, sizeof (int), 1, fichier);
    pos = htobe32(pos);
    pos = 0x130; // FIXME : à rendre dynamique

    printf("Position de la table des noms : %x\n", pos);
    fseek(fichier, SEC_HEAD_IDX, SEEK_SET);

    int idxName = 0;

    for (i = 0; i < SEC_NBR; i++) {
        idxName = 0;

        sections[i]->sh_name = (char*) malloc(sizeof (char)*256);

        fread(&idxName, sizeof (int), 1, fichier);
        idxName = htobe32(idxName); // FIXME : check for ARM
        //printf("Section courante : %x\n",idxName);
        if (idxName == 0) {
            if (i == 0)
                sections[i]->sh_name = "";
            //else
            //return NULL;				
        } else {
            fseek(fichier, pos + idxName, SEEK_SET);
            char c = 2;
            int j = 0;
            while (c != 0) {
                c = fgetc(fichier);
                if (c)
                    sections[i]->sh_name[j] = c;
                    //return 1;
                else
                    sections[i]->sh_name[j] = '\0';
                //printf("\nFin de ligne !");
                j++;
            }
            fseek(fichier, SEC_HEAD_IDX + (40 * i) + 4, SEEK_SET);
        }

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

    for (i = 0; i < SEC_NBR; i++) {
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


    return 0;
}
