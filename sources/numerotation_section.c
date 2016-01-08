#include <stdio.h>
#include <stdlib.h>
#include "projet.h"

void num_section(SEC_HEADER ** sections, SEC_HEADER ** rel_sections, int nb_rel_secs, FILE * fichier)
{
	int i = 0, j = 0, nbentrees = 1;
	//FILE* fres = fopen("example1.o", "w");
	REL ** rel_entrees;
	int addr = 0;
	int addend = 0;
	SEC_HEADER* cible;

	for(i = 0; i < nb_rel_secs; i++) // Each section
	{
		rel_entrees = get_rel_entries(rel_sections[i],&nbentrees);
		cible = sections[htobe32(rel_sections[i]->sh_info)]; // get the target section (via sh_info)
		addr = htobe32(cible->sh_offset);
		
		for(j = 0; j < nbentrees; j++) // Each entry
		{
		  addend += addr + htobe32(rel_entrees[j]->r_offset); // TODO : Check for the RELA case
		}
		printf("Nom : %s Adresse initiale : 0x%x Adresse decalee debut : 0x%x Adresse decalee fin : 0x%x\n",cible->sh_name, htobe32(cible->sh_offset), addend, addend + htobe32(cible->sh_size));

		addend = 0;
		addr = 0;
		/*if(rel_sections[i]->r_info >> 8 != 0) // != SHN_UNDEF
		{
			fseek(fichier,addend,SEEK_SET);
			fwrite(cible,sizeof(cible),1,fres);
		}*/
	}
}
