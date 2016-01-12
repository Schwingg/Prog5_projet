
#include "projet.h"

void num_section(HEADER * hdr, SEC_HEADER ** sections, int nb_rel_secs, FILE * fichier)
{
  FILE* fres = fopen("test.o", "w");
  int nbSecs = hdr->e_shnum;

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
		
  while(j < hdr->e_shoff){ // Read until section header
    fread(&oct,1,1,fichier);
    fwrite(&oct,1,1,fres);
    oct = 0;
    j++;
  }

  int k = 0, l = 0, word = 0, addrRel = 0x7FFFFFFF;
		
  for(k = 0; k < nbSecs; k++) // Read section table
  {
    if(strstr(sections[k]->sh_name,".rel.") != NULL)
    {
      fseek(fichier,hdr->e_shentsize/10*4,SEEK_CUR);
      fread(&word,sizeof(int),1,fichier);
      if(htobe32(word) < addrRel)
	addrRel = htobe32(word);
      fseek(fichier,hdr->e_shentsize/10*5,SEEK_CUR);
    }
    else if(strcmp(sections[k]->sh_name,".symtab") == 0){
      for(l = 0; l < hdr->e_shentsize/10*4; l++){
	fread(&oct,1,1,fichier);
	fwrite(&oct,1,1,fres);
	oct = 0;
      }
		    
      fread(&word,sizeof(int),1,fichier); // Read link part
      word = htobe32(word) - (nb_rel_secs*hdr->e_shentsize);
      word = htobe32(word);
      //printf("%d\n",word);
      fwrite(&word,sizeof(int),1,fres);
      word = 0;

      for(l = 0; l < hdr->e_shentsize/10; l++){
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
      for(l = 0; l < hdr->e_shentsize/10*3; l++){
	fread(&oct,1,1,fichier);
	fwrite(&oct,1,1,fres);
	oct = 0;
      }
    }
    else if(strcmp(sections[k]->sh_name,".strtab") == 0){
      for(l = 0; l < hdr->e_shentsize/10*4; l++){
	fread(&oct,1,1,fichier);
	fwrite(&oct,1,1,fres);
	oct = 0;
      }
      fread(&word,sizeof(int),1,fichier);
      word = htobe32(word) - (nb_rel_secs*hdr->e_shentsize);
      word = htobe32(word);
      fwrite(&word,sizeof(int),1,fres);
      word = 0;
      for(l = 0; l < hdr->e_shentsize/10*5; l++){
	fread(&oct,1,1,fichier);
	fwrite(&oct,1,1,fres);
	oct = 0;
      }
    }else{
      for(l = 0; l < hdr->e_shentsize; l++){
	fread(&oct,1,1,fichier);
	fwrite(&oct,1,1,fres);
	oct = 0;
      }
    }
  }
		
  j += nbSecs*hdr->e_shentsize;

  while(j < addrRel){
    fread(&oct,1,1,fichier);
    fwrite(&oct,1,1,fres);
    oct = 0;
    j++;
  }
		
  fclose(fres);
  //}
}
