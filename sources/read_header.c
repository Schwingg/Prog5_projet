#include "bfile.h"
#include "stdio.h"

BFILE* bfichier;

void read_header(BFILE* bfichier) {
    int i, x;
    int test = 0;

    for (i = 0; i < 32; i++) {
        x = bitread(bfichier);
    } //Skip the magic numbers (4 bytes)

    //Read the bits indicating the addressing size
    for (i = 0; i < 8; i++) {
        x = bitread(bfichier);
        test = test | (x << (7 - i));
    }
    switch (test) {
        case 0x0:
            printf("aucun bit???????????\n");
            break;
        case 0x1:
            printf("32 bits\n");
            break;
        case 0x2:
            printf("64 bits\n");
            break;
    }
    test = 0;
    //Little or Big Endian reading and test
    for (i = 0; i < 8; i++) {
        x = bitread(bfichier);
        test = test | (x << (7 - i));
    }

    switch (test) {
        case 0x0:
            printf("aucun ??????????????\n");
            break;
        case 0x1:
            printf("Little Endian\n");
            break;
        case 0x2:
            printf("Big Endian\n");
            break;
    }
    test = 0;

    for (i = 0; i < 8; i++) { //We read 1 byte
        x = bitread(bfichier); //We read bit after bit
        test = test | (x << (7 - i)); //We concatenate the bits to get an integer
    }
    if (test == 1) {
        printf("Original version of ELF\n");
    } else {
        printf("Not original version of ELF\n");
    }
    test = 0;

	// OS Type
    for (i = 0; i < 8; i++) {
        x = bitread(bfichier);
        test = test | (x << (7 - i));
    }
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
    test = 0;

	//Application Binary Interface Version
    for (i = 0; i < 8; i++) {
        x = bitread(bfichier);
        test = test | (x << (7 - i));
    }
    printf("ABI Version : %d\n", test);
    test = 0;

    for (i = 0; i < 56; i++) { //Jump 7 bytes
        x = bitread(bfichier);
    }

	//Type of ELF file
    for (i = 0; i < 16; i++) { //Read 2 bytes
        x = bitread(bfichier);
        test = test | (x << (15 - i));
    }

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
    test = 0;

	//Target architecture
    for (i = 0; i < 16; i++) {
        x = bitread(bfichier);
        test = test | (x << (15 - i));
    }
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
    test = 0;

	//Version
    for (i = 0; i < 32; i++) { //Read 4 octets
        x = bitread(bfichier);
        test = test | (x << (31 - i));
    }
    if (test == 1) printf("Original version of ELF\n");
    else printf("Not original version of ELF\n");
    test = 0;

	//Memory address of the entry point
    for (i = 0; i < 32; i++) {
        x = bitread(bfichier);
        test = test | (x << (31 - i));
    }
    printf("Memory address of the entry point : 0x%04X\n", test);
    test = 0;

	//
    for (i = 0; i < 32; i++) {
        x = bitread(bfichier);
        test = test | (x << (31 - i));
    }
    printf("Start of the program header table : %d\n", test);
    test = 0;

    for (i = 0; i < 32; i++) {
        x = bitread(bfichier);
        test = test | (x << (31 - i));
    }
    printf("Start of the section header table : %d\n", test);
    test = 0;

    for (i = 0; i < 32; i++) {
        x = bitread(bfichier);
        test = test | (x << (31 - i));
    }
    printf("Flags : 0x%04X\n", test);
    test = 0;

    for (i = 0; i < 16; i++) {
        x = bitread(bfichier);
        test = test | (x << (15 - i));
    }
    printf("Size of the header : %d\n", test);
    test = 0;

    for (i = 0; i < 16; i++) {
        x = bitread(bfichier);
        test = test | (x << (15 - i));
    }
    printf("Size of a program header table entry : %d\n", test);
    test = 0;

    for (i = 0; i < 16; i++) {
        x = bitread(bfichier);
        test = test | (x << (15 - i));
    }
    printf("Number of entries in the program header table : %d\n", test);
    test = 0;

    for (i = 0; i < 16; i++) {
        x = bitread(bfichier);
        test = test | (x << (15 - i));
    }
    printf("Size of a section header table entry : %d\n", test);
    test = 0;

    for (i = 0; i < 16; i++) {
        x = bitread(bfichier);
        test = test | (x << (15 - i));
    }
    printf("Number of entries in the section header table : %d\n", test);
    test = 0;

    for (i = 0; i < 16; i++) {
        x = bitread(bfichier);
        test = test | (x << (15 - i));
    }
    printf("Index of the section header table entry : %d\n", test);
}
