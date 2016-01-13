#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet.h"

SEC_HEADER ** get_rel_sections(SEC_HEADER ** sections, int nbSecs, int * nb_rel_sec)
{
	int i = 0, j = 0;
	rel_sections = (SEC_HEADER**) malloc(sizeof(SEC_HEADER)*nbSecs);
	
	for(i = 0; i < nbSecs; i++)
	{
		if(strstr(sections[i]->sh_name,".rel.") != NULL || strstr(sections[i]->sh_name,".rela.") != NULL)
		{
			rel_sections[j] = sections[i];
			j++;
		}
	}

	*nb_rel_sec = j;

	return rel_sections;
}

REL** get_rel_entries(SEC_HEADER * section, int* nb_entrees)
{
	int j = 0;
	nbr_rel = htobe32(section->sh_size)/htobe32(section->sh_entsize);
	rel_section = (REL **) malloc(htobe32(section->sh_offset)/htobe32(section->sh_entsize) * (sizeof (REL)));
	        
	for(j = 0; j < htobe32(section->sh_size)/htobe32(section->sh_entsize); j++)
	{
		rel_section[j] = (REL*) malloc(sizeof (REL));
		
		fseek(fichier,htobe32(section->sh_offset)+(j*8),SEEK_SET);
		fread(&rel_section[j]->r_offset,sizeof(int),1,fichier);
		fread(&rel_section[j]->r_info,sizeof(int),1,fichier);
		if(section->sh_type == 4)
		{
			rel_section[j]->rela = 1;
			fread(&rel_section[j]->r_addend,sizeof(int),1,fichier);
		}
	}

	*nb_entrees = j;
	return rel_section;
}
