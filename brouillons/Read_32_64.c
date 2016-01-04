#include "bfile.h"
#include <stdio.h>

FILE* fichier;
BFILE* bfichier;

int main(){
	fichier = fopen("matrice.o","r");
	bfichier = bstart(fichier,"r");
	int i,x;
	int bits=0;
	for (i=0; i<32; i++){x = bitread(bfichier);}
	for (i=0; i<8; i++){
		x = bitread(bfichier);
		printf("%d",x);
		bits = bits | (x << (7-i));
	}
	
	printf("%d",bits);
	
	return 0;
}
