#include "bfile.h"
#include "stdio.h"

BFILE* bfichier;

void jump(int octet){
	int i;
	for (i=0; i<(8*octet); i++){
		bitread(bfichier);
	}
}

int read(int octet, int endian){
	int i,j,test=0;
	if (endian == 0){
		for (i=0; i<(8*octet); i++){
			test = test | (bitread(bfichier) << ((8*octet)-1-i));
		}
	}
	else{
		for (i=0; i<octet; i++){
			for (j=0; j<8; j++){
				test = test | bitread(bfichier) << ((8*i)+7-j);
			}
		}
	}
	return test;
}


int read_header(BFILE* bfichier) {
    int i, nbbit, endian=0;
    int test;

    jump(1);

    char elf[3] = {'E', 'L', 'F'};
    for (i = 0; i < 3; i++) {
        test = read(1,endian);
        if (test != elf[i]) {
            printf("Ce nest pas un fichier ELF\n");
            return 1;
        }
    }

    //Read the bits indicating the addressing size
    test = read(1,endian);
    switch (test) {
        case 0x0:
            printf("aucun bit???????????\n");
            break;
        case 0x1:
            printf("32 bits\n");
            nbbit = 32;
            break;
        case 0x2:
            printf("64 bits\n");
            nbbit = 64;
            break;
    }
    //Little or Big Endian reading and test
    test = read(1,endian);
    switch (test) {
        case 0x0:
            printf("aucun ??????????????\n");
            break;
        case 0x1:
            printf("Little Endian\n");
            endian = 1;
            break;
        case 0x2:
            printf("Big Endian\n");
            endian = 0;
            break;
    }

    test = read(1,endian);
    if (test == 1) {
        printf("Original version of ELF\n");
    } else {
        printf("Not original version of ELF\n");
    }

    // OS Type
    test = read(1,endian);
    switch (test) {
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

    //Application Binary Interface Version
    test = read(1,endian);
    printf("ABI Version : %d\n", test);

    jump(7);

    //Type of ELF file
	test = read(2,endian);
    switch (test) {
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

    //Target architecture
    test = read(2,endian);
    switch (test) {
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

    //Version
    test = read(4,endian);
    if (test == 1) printf("Original version of ELF\n");
    else printf("Not original version of ELF\n");

    //Memory address of the entry point
	if (nbbit == 32) test = read(4,endian);
	else test = read(8,endian);
    printf("Memory address of the entry point : 0x%04X\n", test);

    //offset header
	if (nbbit == 32) test = read(4,endian);
	else test = read(8,endian);
    printf("Start of the program header table : %d\n", test);

    //offset  section table
	if (nbbit == 32) test = read(4,endian);
	else test = read(8,endian);
    printf("Start of the section header table : %d\n", test);

    test = read(4,endian);
    printf("Flags : 0x%04X\n", test);

    test = read(2,endian);
    printf("Size of the header : %u\n", test);

    test = read(2,endian);
    printf("Size of a program header table entry : %d\n", test);

    test = read(2,endian);
    printf("Number of entries in the program header table : %d\n", test);

    test = read(2,endian);
    printf("Size of a section header table entry : %d\n", test);

    test = read(2,endian);
    printf("Number of entries in the section header table : %d\n", test);

    test = read(2,endian);
    printf("Index of the section header table entry : %d\n", test);

	return 0;
}
