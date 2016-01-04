#include "bfile.h"
#include <stdio.h>

FILE* fichier;
BFILE* bfichier;

int main(){
	fichier = fopen("matrice.o","r");
	bfichier = bstart(fichier,"r");

	int i,x;
	int test=0;

	for (i=0; i<48; i++){x = bitread(bfichier);} //We jump the magic numbers and the octets for 32/64 bits and the endian (6 octets)

	printf("32 bits\n"); //We only work with the ELF32 format
	printf("Big Endian\n"); // We only work in Big Endian

	for (i=0; i<8; i++){ //We read 1 octet
		x = bitread(bfichier); //We read byte after byte
		test = test | (x << (7-i)); //We concatenate the bytes to get an integer
	}
	if (test == 1) printf("Original version of ELF\n");
	else printf("Not original version of ELF\n");
	test = 0;

	for (i=0; i<8; i++){
		x = bitread(bfichier);
		test = test | (x << (7-i));
	}
	switch (test){
	case 0x0:
		printf("System V\n");
		break;
	case 0x1:
		printf("HP-UX\n");
		break;
	case 0x2:
		printf("NetBSD\n");
		break;
	case 0x3:
		printf("Linux\n");
		break;
	case 0x6:
		printf("Solaris\n");
		break;
	case 0x7:
		printf("AIX\n");
		break;
	case 0x8:
		printf("IRIX\n");
		break;
	case 0x9:
		printf("FreeBSD\n");
		break;
	case 0xC:
		printf("OpenBSD\n");
		break;
	case 0xD:
		printf("OpenVMS\n");
		break;
	}
	test = 0;

	for (i=0; i<8; i++){
		x = bitread(bfichier);
		test = test | (x << (7-i));
	}
	printf("ABI Version : %d\n",test);
	test = 0;

	for (i=0; i<56; i++){ //We jump 7 octets
		x = bitread(bfichier);
	}

	for (i=0; i<16; i++){ //We read 2 octets
		x = bitread(bfichier);
		test = test | (x << (15-i));
	}
	switch (test){
	case 0x1:
		printf("Relocatable\n");
		break;
	case 0x2:
		printf("Executable\n");
		break;
	case 0x3:
		printf("Shared\n");
		break;
	case 0x4:
		printf("Core\n");
		break;
	}
	test = 0;

	for (i=0; i<16; i++){
		x = bitread(bfichier);
		test = test | (x << (15-i));
	}
	switch (test){
	case 0x00:
		printf("No specific instruction set\n");
		break;
	case 0x02:
		printf("SPARC\n");
		break;
	case 0x03:
		printf("x86\n");
		break;
	case 0x08:
		printf("MIPS\n");
		break;
	case 0x14:
		printf("PowerPC\n");
		break;
	case 0x28:
		printf("ARM\n");
		break;
	case 0x2A:
		printf("SuperH\n");
		break;
	case 0x32:
		printf("IA-64\n");
		break;
	case 0x3E:
		printf("x86-64\n");
		break;
	case 0xB7:
		printf("AArch64\n");
		break;
	}
	test = 0;

	for (i=0; i<32; i++){ //We read 4 octets
		x = bitread(bfichier);
		test = test | (x << (31-i));
	}
	if (test == 1) printf("Original version of ELF");
	else printf("Not original version of ELF");
	test = 0;

	for (i=0; i<32; i++){
		x = bitread(bfichier);
		test = test | (x << (31-i));
	}
	printf("Memory adress of the entry point : 0x%04X", test);
	test = 0;

	for (i=0; i<32; i++){
		x = bitread(bfichier);
		test = test | (x << (31-i));
	}
	printf("Start of the program header table : %d", test);
	test = 0;

	for (i=0; i<32; i++){
		x = bitread(bfichier);
		test = test | (x << (31-i));
	}
	printf("Start of the section header table : %d", test);
	test = 0;

	for (i=0; i<32; i++){
		x = bitread(bfichier);
		test = test | (x << (31-i));
	}
	printf("Flags : 0x%04X", test);
	test = 0;

	for (i=0; i<16; i++){
		x = bitread(bfichier);
		test = test | (x << (15-i));
	}
	printf("Size of the header : %d", test);
	test = 0;

	for (i=0; i<16; i++){
		x = bitread(bfichier);
		test = test | (x << (15-i));
	}
	printf("Size of a program header table entry : %d", test);
	test = 0;

	for (i=0; i<16; i++){
		x = bitread(bfichier);
		test = test | (x << (15-i));
	}
	printf("Number of entries in the program header table : %d", test);
	test = 0;

	for (i=0; i<16; i++){
		x = bitread(bfichier);
		test = test | (x << (15-i));
	}
	printf("Size of a section header table entry : %d", test);
	test = 0;

	for (i=0; i<16; i++){
		x = bitread(bfichier);
		test = test | (x << (15-i));
	}
	printf("Number of entries in the section header table : %d", test);
	test = 0;

	for (i=0; i<16; i++){
		x = bitread(bfichier);
		test = test | (x << (15-i));
	}
	printf("Index of the section header table entry : %d", test);

	return 0;
}
