#define "bfile.h"
#define <stdio.h>

file* fichier;
bfile* bfichier;

int main{
	fichier = fopen("matrice.o","r");
	bfichier = bstart(fichier,"r");
	int i,x;
	int bits=0;
	for (i=0; i<32; i++){x = bitread(bfichier);}
	for (i=0; i<8; i++){
		x = bitread(bfichier);
		bits = bits | (x << (8-i));
	}
	return 0;
}
