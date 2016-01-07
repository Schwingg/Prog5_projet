#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "section_header.h"
#include "rel.h"

REL** get_rel_sections(FILE* fichier, SEC_HEADER** sections, int nbSecs)
{
	int i = 0, j = 0;
	
	for(i = 0; i < nbSecs; i++)
	{
		if(strstr(sections[i]->sh_name,".rel.") != NULL)
		{
			REL **rel_sections = (REL **) malloc(sections[i]->sh_offset/8 * (sizeof (REL))); // 2 words (8 bytes)
			if (rel_sections == NULL)
        return NULL;
        
			for(j = 0; j < htobe32(sections[i]->sh_size); j += 8)
			{
				rel_sections[j] = (REL*) malloc(sizeof (REL));
				if (rel_sections[j] == NULL)
					return NULL;
			
				fseek(fichier,htobe32(sections[i]->sh_offset)+j,SEEK_SET);
				fread(&rel_sections[j]->r_offset,sizeof(int),1,fichier);
				fread(&rel_sections[j]->r_info,sizeof(int),1,fichier);

				printf("%x %x ", htobe32(rel_sections[j]->r_offset), htobe32(rel_sections[j]->r_info));
				printf("| Symb : %x Type : %x | ", htobe32(rel_sections[j]->r_info) >> 8, (unsigned char)htobe32(rel_sections[j]->r_info));
			}
			printf("\n");
		}
		else if(strstr(sections[i]->sh_name,".rela.") != NULL)
		{
			RELA **rela_sections = (RELA **) malloc(sections[i]->sh_offset/12 * (sizeof (RELA))); // 3 words (12 bytes)
			if (rela_sections == NULL)
        return NULL;
        
			for(j = 0; j < htobe32(sections[i]->sh_size); j += 12)
			{
				rela_sections[j] = (RELA*) malloc(sizeof (RELA));
				if (rela_sections[j] == NULL)
					return NULL;
			
				fseek(fichier,htobe32(sections[i]->sh_offset)+j,SEEK_SET);
				fread(&rela_sections[j]->r_offset,sizeof(int),1,fichier);
				fread(&rela_sections[j]->r_info,sizeof(int),1,fichier);

				printf("%x %x %x", htobe32(rela_sections[j]->r_offset), htobe32(rela_sections[j]->r_info),htobe32(rela_sections[j]->r_addend));
				printf("| Symb : %x Type : %x | ", htobe32(rela_sections[j]->r_info) >> 8, (unsigned char)htobe32(rela_sections[j]->r_info));
			}
			printf("\n");
		}
	}
	return NULL;
}
