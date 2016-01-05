#define SEC_HEAD_IDX 0x1b0 // TODO : Get value from ELF header
#define SEC_SIZE 40 // TODO : Get value from ELF header
#define SEC_NAME_NO 12 // TODO : Get value from ELF header
#define SEC_NBR 15 // TODO : Get value from ELF header

#include <stdio.h>
#include <stdlib.h>

typedef struct
 {
	int sh_name;
  int sh_type;
  int sh_flags;
  int sh_addr;
  int sh_offset;
  int sh_size;
  int sh_link;
  int sh_info;
  int sh_addralign;
  int sh_entsize;
} SEC_HEADER;

SEC_HEADER section_header(FILE* fichier)
{
	int octet = 0, i = 0;
	SEC_HEADER *sections;
  sections = (SEC_HEADER *) malloc(sizeof (SEC_HEADER)*SEC_NBR);
  if (sections == NULL)
    return NULL;
	
  fseek(fichier, SEC_HEAD_IDX, SEEK_SET);

	int idxName = 0;
	for(i = 0; i < SEC_NBR; i++)
	{
		idxName = 0;
		fread(&idxName,sizeof(int),1,fichier);
		if(idxName)
	}
}
