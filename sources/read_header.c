#include "stdio.h"
#include "read_header.h"
#include "stdlib.h"

FILE *fichier;

// Skips octet bytes

void jump(int octet) {
    int temp = 0, i;
    for (i = 0; i < octet; i++) {
        fread(&temp, sizeof (char), 1, fichier);
    }
}

// Reads octet bytes, taking in account the Endianness

int read(int octet, int endian) {
    int i, estlu = 0, temp = 0;
    if (endian == 0) {
        for (i = 0; i < octet; i++) {
            fread(&temp, sizeof (char), 1, fichier);
            estlu = estlu | temp << 8 * (octet - 1 - i);

        }
    } else {
        for (i = 0; i < octet; i++) {
            fread(&temp, sizeof (char), 1, fichier);
            estlu = estlu | temp << 8 * i;
        }
    }
    return estlu;
}

// Reads the header of the file *fichier

HEADER *read_header(FILE *fichier) {
    int i, nbbit, endian = 0;
    int test;
    HEADER *hed;
    hed = (HEADER *) malloc(sizeof (HEADER));
    if (hed == NULL)
        return NULL;
    jump(1);

    char elf[3] = {'E', 'L', 'F'};
    for (i = 0; i < 3; i++) {
        test = read(1, endian);
        if (test != elf[i]) {
            printf("This is not an ELF file\n");
            hed->ELF = 0;
            return hed;
        }
    }
    hed->ELF = 1;
    printf("Class                                           ELF");

    //Read the bits indicating the addressing size
    test = read(1, endian);
    switch (test) {
        case 0x0:
            printf("/n No indication about address size?\n");
            break;
        case 0x1:
            printf("32/bits\n");
            nbbit = 32;
            break;
        case 0x2:
            printf("64/bits\n");
            nbbit = 64;
            break;
    }
    //Little or Big Endian reading and test
    printf("Data:                                           ");
    test = read(1, endian);
    switch (test) {
        case 0x0:
            printf("No indication about endianness\n");
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
    printf("Version:                                        ");
    test = read(1, endian);
    printf("%d\n", test);
    test = 0;

    // OS Type
    printf("OS type:                                        ");
    test = read(1, endian);
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
    test = read(1, endian);
    printf("ABI Version :                                   %d\n", test);

    jump(7);

    //Type of ELF file
    printf("Type:                                           ");
    test = read(2, endian);
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
    printf("Target architecture:                            ");
    test = read(2, endian);
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
    printf("Version:                                        ");
    test = read(4, endian);
    if (test == 1) printf("Original version of ELF\n");
    else printf("Not original version of ELF\n");

    //Memory address of the entry point
    test = (read((nbbit / 8), endian));
    printf("Memory address of the entry point :             0x%04X\n", test);

    //offset header
    test = (read((nbbit / 8), endian));
    printf("Start of the program header table :             %d\n", test);

    //offset  section table
    test = (read((nbbit / 8), endian));
    printf("Start of the section header table :             %d\n", test);

    //flags
    test = read(4, endian);
    printf("Flags :                                         0x%04X\n", test);

    //header size
    test = read(2, endian);
    printf("Size of the header :                            %d\n", test);

    //size of the program header section
    test = read(2, endian);
    printf("Size of a program header table entry :          %d\n", test);

    //number of entries in the program header section
    test = read(2, endian);
    printf("Number of entries in the program header table : %d\n", test);

    // size of a section
    test = read(2, endian);
    printf("Size of a section header table entry :          %d\n", test);

    //number of entries in the section header table
    test = read(2, endian);
    printf("Number of entries in the section header table : %d\n", test);

    //index of the section header table entry
    test = read(2, endian);
    printf("Index of the section header table entry :       %d\n", test);

    return hed;
}
