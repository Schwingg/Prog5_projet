#include "arm_simulator_interface.h"
#include "projet.h"

// TODO : use example in ARM_runner_example.c

void simuler(SEC_HEADER ** sections, int nbSecs, FILE * fichier)
{
  int address = 0x58;
  int i = 0, j = 0, k = 0, word = 0;
  int * contenu;

  arm_simulator_data_t simulator;

  simulator = arm_connect("127.0.0.1","..."); // Change the service arg value

  arm_write_register(simulator,15,address);

  for(i = 0; i < nbSecs; i++)
  {
    if(strcmp(sections[i]->sh_name, ".text") == 0)
    {
      if(htobe32(sections[i]->sh_size)/4 > 0)
      {
	contenu = (int*) malloc(sizeof(int)*htobe32(sections[i]->sh_size)/4);
	k = 0;
	fseek(fichier,sections[i]->sh_offset,SEEK_SET);
	for(j = 0; j < htobe32(sections[i]->sh_size)/4; j++)
	{
	  fread(&word,sizeof(int),1,fichier);
	  contenu[k] = word; // htobe32 is useless because written in ARM memory
	  k++;	  
	}
	arm_write_memory(simulator,address,contenu,htobe32(sections[i]->sh_size));
	free(contenu);
      }
    }
  }
  arm_run(simulator);
}

  void implantation(SEC_HEADER ** sections, int nbSecs,  SYMB_HEADER ** symtab, FILE *fichier)
  {
    int nb_rel_secs = 0, i = 0, nb_entries = 0, j = 0, pos = 0, word = 0;
    char oct = 0;
    REL ** rel_entries;
    FILE * fres = fopen("test2.o","w");
    SEC_HEADER ** rel_sections = get_rel_sections(sections, nbSecs, &nb_rel_secs);

    for(i = 0; i < nb_rel_secs; i++) // Each REL section
    {
      rel_entries = NULL; // TODO : optimize memory management 
      rel_entries = get_rel_entries(rel_sections[i], &nb_entries);
    

      while(pos < htobe32(sections[htobe32(rel_sections[i]->sh_info)]->sh_offset))
      {
	oct = 0;
	fread(&oct,1,1,fichier);
	fwrite(&oct,1,1,fres);
	pos++;
      }

      int s = 0, a = 0, t = 0, p = 0;
      unsigned char rel_type;
    
      for(j = 0; j < nb_entries; j++) // Each entry
      {
	while(pos < htobe32(sections[htobe32(rel_sections[i]->sh_info)]->sh_offset) + htobe32(rel_entries[j]->r_offset))
	{
	  oct = 0;
	  fread(&oct,1,1,fichier);
	  fwrite(&oct,1,1,fres);
	  pos++;
	}
	word = 0;
	fread(&word,sizeof(int),1,fichier);
	s = htobe32(symtab[htobe32(rel_entries[j]->r_info) >> 8]->st_value);
	a = word;
	t = (symtab[htobe32(rel_entries[j]->r_info) >> 8]->st_info & 0xf) == 2;
	//printf("%x\n", symtab[htobe32(rel_entries[j]->r_info) >> 8]->st_value);
	p = pos;
	rel_type = (unsigned char) htobe32(rel_entries[j]->r_info);

	if(rel_type == 2) // TODO : Check architecture ARM/PC
	  word = (a + s) | t; // (S + A) | T
	else if(rel_type == 5 || rel_type == 8)
	  word = a + s; // S + A
	else if(rel_type == 28 || rel_type == 29)
	{
	  word = ((a + s) | t) - p; // ((S + A) | T) - P
	  word = word & 0x03FFFFFE;
	}
	else
	  printf("Type non reconnu !\n");


	word = htobe32(word);
	fwrite(&word,sizeof(int),1,fres);
	pos += 4;
      } 
    }

    while(!feof(fichier))
    {
      oct = 0;
      fread(&oct,1,1,fichier);
      fwrite(&oct,1,1,fres);
      pos++;
    }
    fclose(fres);
  }

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

    nb = htobe16(nb);
    fwrite(&nb,sizeof(short),1,fres);
    nb = 0;
		
    fread(&nb,sizeof(short),1,fichier); // Change the section name position
    nb = htobe16(nb) - nb_rel_secs;

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
      symb[k]->st_value = word;
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
    fres = fopen("test.o","r");
    implantation(sections, nbSecs, symb, fres);
    fclose(fres);
  }


