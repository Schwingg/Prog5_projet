#include "bfile.h"
#include <stdio.h>

FILE* fichier;
BFILE* bfichier;

int data[18] = {0x4,0x5,0x6,0x7,0x8,0x10,0x12,0x14,0x18,0,0,0,0,0,0,0,0,0};

int main(){
	fichier = fopen("matrice.o","r");
	bfichier = bstart(fichier, "r");
	int i = 0;
	int bit;
	char * test;
	
	for(i = 0; i < 8; i++)
	{
		bit = bitread(bfichier);
		test[i] = (char) bit;
	}

	printf("%s", test);
}
