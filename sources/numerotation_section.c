#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet.h"

void num_section(SEC_HEADER ** sections, int nbSecs, int nb_rel_secs, FILE * fichier)
{
  FILE* fres = fopen("test.o", "w");

  fseek(fichier,0,SEEK_SET);

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
