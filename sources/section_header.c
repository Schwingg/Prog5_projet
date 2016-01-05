#define SEC_HEAD_IDX 0x1b0 // TODO : Get value from ELF header
#define SEC_SIZE 40 // TODO : Get value from ELF header
#define SEC_NAME_NO 12 // TODO : Get value from ELF header
#define SEC_NBR 15 // TODO : Get value from ELF header

#include <stdio.h>
#include <stdlib.h>

typedef struct
 {
	char* sh_name;
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

int main()
{
	FILE* fichier;
	fichier = fopen("example1.o","r");

	
	int pos = 0, i = 0;
	SEC_HEADER **sections = (SEC_HEADER **) malloc((sizeof (SEC_HEADER))*SEC_NBR);
  if (sections == NULL)
    return 1;

  for(i = 0; i < SEC_NBR; i++)
  {
		sections[i] = (SEC_HEADER*) malloc(sizeof(SEC_HEADER));
		if (sections[i] == NULL)
			return 1;
	}
	
  fseek(fichier, (SEC_NAME_NO*SEC_SIZE)+SEC_HEAD_IDX+17, SEEK_SET); // 5 * 4 - 3 bytes
  fread(&pos, sizeof(int), 1, fichier);

  fseek(fichier, SEC_HEAD_IDX, SEEK_SET);  

	int idxName = 0;
	for(i = 0; i < SEC_NBR; i++)
	{
		idxName = 0;
		//sections[i]->sh_name = (char*) malloc
		fread(&idxName,sizeof(int),1,fichier);
		if(idxName == 0)
		{
			if(i == 0)
				sections[i]->sh_name = "";
			//else
				//return NULL;				
		}
		else
		{
			fseek(fichier,pos+idxName,SEEK_SET);
			char c;
			int j = 0;
			do
			{
				fread(&c,sizeof(char),1,fichier);
				if(c)
					sections[i]->sh_name[j] = c;
				else
					sections[i]->sh_name[j] = '\0';
				j++;
			}while(c != 0);
			fseek(fichier,SEC_HEAD_IDX+(40*i)+4, SEEK_SET);
		}

		fread(&sections[i]->sh_type, sizeof(int), 1, fichier);
		fread(&sections[i]->sh_flags, sizeof(int), 1, fichier);
		fread(&sections[i]->sh_addr, sizeof(int), 1, fichier);
		fread(&sections[i]->sh_offset, sizeof(int), 1, fichier);
		fread(&sections[i]->sh_size, sizeof(int), 1, fichier);
		fread(&sections[i]->sh_link, sizeof(int), 1, fichier);
		fread(&sections[i]->sh_info, sizeof(int), 1, fichier);
		fread(&sections[i]->sh_addralign, sizeof(int), 1, fichier);
		fread(&sections[i]->sh_entsize, sizeof(int), 1, fichier);
	}

	return 0;
}
