#include <stdio.h>
#include <stdlib.h>
#include "read_header.h"
#include "section_header.h"
#include "symbolheader.h"


/*Paramètres: - symb_tab - structure de la section de la table de symbole(.symtab)
 							- str_tab - structure de la section de .strtab
 */							
SYMB_HEADER **symbole_header(FILE* fichier, SEC_HEADER* symb_tab, SEC_HEADER* str_tab){
		unsigned long SYMB_HEAD_IDX = htobe32(symb_tab->sh_offset);
    unsigned long SYMB_SIZE = htobe32(symb_tab->sh_size);
    unsigned long STR_HEAD_IDX = htobe32(str_tab->sh_offset);
    //unsigned long STR_SIZE = str_tab->sh_size;
    int i = 0;
    int idxName;
    int LONGUEUR_SYMB = 16;// 16 = taille en octet d'une ligne de la table de symbole
    int nbr_symb = SYMB_SIZE / LONGUEUR_SYMB;
    
    //Allocation
    SYMB_HEADER **symbole = (SYMB_HEADER **) malloc(nbr_symb * (sizeof (SYMB_HEADER)));
    if (symbole == NULL)
        return NULL;
    for (i = 0; i < nbr_symb; i++) {
        symbole[i] = (SYMB_HEADER*) malloc(sizeof (SYMB_HEADER));
        if (symbole[i] == NULL)
            return NULL;
    }
    fseek(fichier,SYMB_HEAD_IDX,SEEK_SET);
   //for each symbol
    for (i = 0; i < nbr_symb; i++) {
        idxName = 0;
        //store the name in st_name
        symbole[i]->st_name = (char*) malloc(sizeof (char)*256);
				
        fread(&idxName, sizeof (int), 1, fichier);
        idxName = htobe32(idxName);
        if (idxName == 0) {
                symbole[i]->st_name = "";
        } else {
        		
            fseek(fichier, STR_HEAD_IDX + idxName, SEEK_SET);
            char c = 2;
            int j = 0;
            while (c != 0) {
                c = fgetc(fichier);           
                if (c)
                    symbole[i]->st_name[j] = c;
                else
                    symbole[i]->st_name[j] = '\0';
                j++;
            }
            fseek(fichier,SYMB_HEAD_IDX + (LONGUEUR_SYMB * i) + 4, SEEK_SET);
        }
        
        //Store the rest of the information for this section
        fread(&symbole[i]->st_value, sizeof (int), 1, fichier);
        fread(&symbole[i]->st_size, sizeof (int), 1, fichier);
        fread(&symbole[i]->st_info, sizeof (char), 1, fichier);
        fread(&symbole[i]->st_other, sizeof (char), 1, fichier);
        fread(&symbole[i]->st_shndx, sizeof (short), 1, fichier);
        symbole[i]->st_shndx = htobe16(symbole[i]->st_shndx);
				symbole[i]->st_value = htobe32(symbole[i]->st_value);
				
    }
    
    for (i=0;i < nbr_symb ;i++){
    	printf("Name :		%s\n", symbole[i]->st_name);
    	printf("Value :		%x\n", symbole[i]->st_value);
    	printf("Size :		%d\n", symbole[i]->st_size);
      
      switch(symbole[i]->st_info >>4){
      		case(0):
      			printf("LOCAL\n");
      			break;
      			case(1):
      			printf("GLOBAL\n");
      			break;
      			case(2):
      			printf("WEAK\n");
      			break;
      			case(13):
      			printf("LOPROC\n");
      			break;
      			case(15):
      			printf("HIPROC\n");
      			break;
      			}
      			
     switch(symbole[i]->st_info & 0xf){
      		case(0):
      			printf("NOTYPE\n");
      			break;
      			case(1):
      			printf("OBJECT\n");
      			break;
      			case(2):
      			printf("FUNC\n");
      			break;
      			case(3):
      			printf("SECTION\n");
      			break;
      			case(4):
      			printf("FILE\n");
      			break;
      			case(13):
      			printf("LOPROC\n");
      			break;
      			case(15):
      			printf("HIPROC\n");
      			break;
      			}

    	printf("Other :		DEFAULT\n");// valeur inutilisé : st_other
    	printf("Ndx :		%d\n", symbole[i]->st_shndx);
    	printf("---------------------\n\n");
    	}
   return symbole;
   }
