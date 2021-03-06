
#include "projet.h"


/*Paramètres: - symb_tab - .symtab section structure
 							- str_tab - .strtab section structure
 */							
SYMB_HEADER **symbole_header(FILE* fichier, SEC_HEADER* symb_tab, SEC_HEADER* str_tab){
	unsigned long SYMB_HEAD_IDX = htobe32(symb_tab->sh_offset);
    unsigned long SYMB_SIZE = htobe32(symb_tab->sh_size);
    unsigned long STR_HEAD_IDX = htobe32(str_tab->sh_offset);
    int i = 0;
    int idxName;
    int LONGUEUR_SYMB = 16;// 16 = size of a line in the symbols tab (bytes)
    nbr_symb = SYMB_SIZE / LONGUEUR_SYMB;
    
    //Allocation
    SYMB_HEADER ** symbole = (SYMB_HEADER **) malloc(nbr_symb * (sizeof (SYMB_HEADER)));
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
   return symbole;
   }
