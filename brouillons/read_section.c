#define SEC 1 // need a section to get info (number or name)
#define SEC_OFF 0x44 // Offset of section SEC
#define SEC_SIZE 0x16 // Size of section SEC
#include <stdio.h>
#include <stdlib.h>

// FIXME : Bourrage du dernier octet observé

int main()
{
	FILE* fichier = fopen("example1.o","r");
	if(fichier == NULL)
		return 1;
	int i = 0;
	unsigned long hex = 0x0;
	
	fseek(fichier, SEC_OFF, SEEK_SET);
	
	for(i = SEC_OFF; i < SEC_OFF + SEC_SIZE; i = i + 4)
	{
		fread(&hex,4,1,fichier);
		hex = htobe32(hex);
		printf("%x ",hex);
		//printf("%x ", i);
		hex = 0;
	}
	printf("\n");
	fclose(fichier);

	return 0;
}
