
#include "projet.h"

int * get_index(SYMB_HEADER ** symb, SEC_HEADER ** sections, int nbSecs, int nb_rel_sec)
{
  int i = 0, nbInx = 0, j = 0, tmp = 0;
  int tab_rel[nb_rel_sec];
  

  for(i = 0; i < nbSecs; i++)
  {
    if(strcmp(sections[i]->sh_name, ".symtab") == 0)
    {
      nbInx = htobe32(sections[i]->sh_size) / htobe32(sections[i]->sh_entsize);
    }
    else if(strstr(sections[i]->sh_name, ".rel.") != NULL)
    {
      tab_rel[j] = i;
      j++;
    }
  }

  int * tab_index = (int*) malloc(sizeof(int)*nbInx);

  for (i = 0; i < nbInx; i++)
  {
    tab_index[i] = symb[i]->st_shndx;
    tmp = tab_index[i];
    for (j = 0; j < nb_rel_sec; j++)
    {
      if(tab_rel[j] < tmp)
	tab_index[i]--;
    }
  }
  
  //index = tab_index;
  return tab_index;
}

void num_section(HEADER * hdr, SEC_HEADER ** sections, int nb_rel_secs, SYMB_HEADER ** symb, FILE * fichier)
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
  nb = 0;
  
  j += 4;
		
  while(j < hdr->e_shoff){ // Read until section header
    fread(&oct,1,1,fichier);
    fwrite(&oct,1,1,fres);
    oct = 0;
    j++;
  }

  int k = 0, l = 0, word = 0, addrRel = 0x7FFFFFFF, symbTab = 0;
		
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
      symbTab = htobe32(word);
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

  while(j < symbTab)
  {
    fread(&oct,1,1,fichier);
    fwrite(&oct,1,1,fres);
    oct = 0;
    j++;
  }
  
  int taille = 0;
  int idxSymb = 0;
  int *index = get_index(symb,sections,nbSecs,nb_rel_secs);

  for(l = 0; l < nbSecs; l++)
  {
    if(strcmp(sections[l]->sh_name, ".symtab") == 0)
    {
      taille = htobe32(sections[l]->sh_size) / htobe32(sections[l]->sh_entsize);
      idxSymb = l;
      break;
    }    
  }

  for(k = 0; k < taille; k++)
  {
    for(l = 0; l < 4; l++)
    {
      fread(&oct,1,1,fichier);
      fwrite(&oct,1,1,fres);
      oct = 0;
    }
    fread(&word,sizeof(int),1,fichier);
    word = htobe32(word)+htobe32(sections[symb[k]->st_shndx]->sh_offset);
    word = htobe32(word);
    fwrite(&word,sizeof(int),1,fres);
    word = 0;
    for(l = 0; l < 6; l++)
    {
      fread(&oct,1,1,fichier);
      fwrite(&oct,1,1,fres);
      oct = 0;
    }
    fseek(fichier,2,SEEK_CUR);
    nb = htobe16(index[k]);
    fwrite(&nb,sizeof(short),1,fres);
    nb = 0;
  }
  j+=htobe32(sections[idxSymb]->sh_size);
  while(j < addrRel){
    fread(&oct,1,1,fichier);
    fwrite(&oct,1,1,fres);
    oct = 0;
    j++;
  }
  free(index);
  fclose(fres);
  //}
}
