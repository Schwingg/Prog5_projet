#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet.h"

#define nbSecs 15 

void num_section(SEC_HEADER ** sections, SEC_HEADER ** rel_sections, int nb_rel_secs, FILE * fichier)
{
  //int i = 0, /*j = 0*/ nbentrees = 1;
	FILE* fres = fopen("test.o", "w");
	//REL ** rel_entrees;
	//int addr = 0;
	//int addend = 0;
	//SEC_HEADER* cible;

	//for(i = 0; i < nb_rel_secs; i++) // Each section
	  //{
	  //rel_entrees = get_rel_entries(rel_sections[i],&nbentrees);
		//cible = sections[htobe32(rel_sections[i]->sh_info)]; // get the target section (via sh_info)
		//addr = htobe32(cible->sh_offset);
		
		/*for(j = 0; j < nbentrees; j++) // Each entry
		{
		  addend += addr + htobe32(rel_entrees[j]->r_offset); // TODO : Check for the RELA case
		}
		printf("Nom : %s Adresse initiale : 0x%x Adresse decalee debut : 0x%x Adresse decalee fin : 0x%x\n",cible->sh_name, htobe32(cible->sh_offset), addend, addend + htobe32(cible->sh_size));

		addend = 0;
		addr = 0;
		if(rel_sections[i]->r_info >> 8 != 0) // != SHN_UNDEF
		{
			fseek(fichier,addend,SEEK_SET);
			fwrite(cible,sizeof(cible),1,fres);
		}*/
		fseek(fichier,0,SEEK_SET);
		/*char * contents = (char*) malloc(sizeof(char)*0x500-1);
		fread(&contents,0x500-1,1,fichier);
		fwrite(contents,0x500-1,1,fres);*/

		char oct = 0; int j = 0;

		for(j = 0; j < 0x30; j++) // until the e_shnum
		{
		  fread(&oct,1,1,fichier);	  
		  fwrite(&oct,1,1,fres);
		  oct = 0;
		}
		
		short nb = 0;
		fread(&nb,sizeof(short),1,fichier); // Change the section number
		nb = htobe16(nb) - nb_rel_secs;
		//printf("%d\n",htobe16(nb));
		nb = htobe16(nb);
		fwrite(&nb,sizeof(short),1,fres);
		nb = 0;
		
		fread(&nb,sizeof(short),1,fichier); // Change the section name position
		nb = htobe16(nb) - nb_rel_secs;
		//printf("%d\n",nb);
		nb = htobe16(nb);
		fwrite(&nb,sizeof(short),1,fres);

		j += 4;
		
		while(j < 0x1b0){ // Read until section header
		  fread(&oct,1,1,fichier);
		  fwrite(&oct,1,1,fres);
		  oct = 0;
		  j++;
		}

		int k = 0, l = 0, word = 0;
		
		for(k = 0; k < nbSecs; k++) // Read section table
		{
		  if(strstr(sections[k]->sh_name,".rel.") != NULL)
		    fseek(fichier,40,SEEK_CUR);
		  else if(strcmp(sections[k]->sh_name,".symtab") == 0){
		    for(l = 0; l < 16; l++){
		      fread(&oct,1,1,fichier);
		      fwrite(&oct,1,1,fres);
		      oct = 0;
		    }
		    
		    fread(&word,sizeof(int),1,fichier); // Read link part
		    word = htobe32(word) - (nb_rel_secs*40);
		    word = htobe32(word);
		    //printf("%d\n",word);
		    fwrite(&word,sizeof(int),1,fres);
		    word = 0;

		    for(l = 0; l < 4; l++){
		      fread(&oct,1,1,fichier);
		      fwrite(&oct,1,1,fres);
		      oct = 0;
		    }
		    
		    fread(&word,sizeof(int),1,fichier); // Read link part
		    word = htobe32(word) - nb_rel_secs;
		    word = htobe32(word);
		    //printf("%d\n",word);
		    fwrite(&word,sizeof(int),1,fres);
		    word = 0;
		    /*fread(&word,sizeof(int),1,fichier);
		    word = htobe32(word) - nb_rel_secs;
		    //printf("%x\n",word);
		    word = htobe32(word);
		    fwrite(&word,sizeof(int),1,fres);*/
		    for(l = 0; l < 12; l++){
		      fread(&oct,1,1,fichier);
		      fwrite(&oct,1,1,fres);
		      oct = 0;
		    }
		  }
		  else if(strcmp(sections[k]->sh_name,".strtab") == 0){
		    for(l = 0; l < 16; l++){
		      fread(&oct,1,1,fichier);
		      fwrite(&oct,1,1,fres);
		      oct = 0;
		    }
		    fread(&word,sizeof(int),1,fichier);
		    word = htobe32(word) - (nb_rel_secs*40);
		    word = htobe32(word);
		    fwrite(&word,sizeof(int),1,fres);
		    word = 0;
		    for(l = 0; l < 20; l++){
		      fread(&oct,1,1,fichier);
		      fwrite(&oct,1,1,fres);
		      oct = 0;
		    }
		  }else{
		    for(l = 0; l < 40; l++){
		      fread(&oct,1,1,fichier);
		      fwrite(&oct,1,1,fres);
		      oct = 0;
		    }
		  }
		}
		
		j += nbSecs*40;

		while(j < 0x500){
		  fread(&oct,1,1,fichier);
		  fwrite(&oct,1,1,fres);
		  oct = 0;
		  j++;
		}
		
		fclose(fres);
		//}
}
