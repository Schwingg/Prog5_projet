#define DEBUT 0x948 // TODO : Get value from ELF header
#include "bfile.h"
#include <stdio.h>

FILE* fichier;
BFILE* bfichier;

int main(){
	fichier = fopen("matrice.o","r");
	bfichier = bstart(fichier, "r");
	int i = 0;

	while(i < DEBUT){ bitread(bfichier); i++;}

	for(i = DEBUT; i < 0x9A8; i++)
	{
		if(i%8 == 0)
			printf(" ");

		printf("%d",bitread(bfichier));
	}
	
}
