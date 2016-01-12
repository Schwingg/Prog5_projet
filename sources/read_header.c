
#include "projet.h"

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
    fseek(fichier, 1, SEEK_CUR);

    char elf[3] = {'E', 'L', 'F'};
    for (i = 0; i < 3; i++) {
        test = read(1, endian);
        if (test != elf[i]) {
            hed->ELF = 0;
            return hed;
        }
    }
    hed->ELF = 1;

    //Read the bits indicating the addressing size
    test = read(1, endian);
    switch (test) {
        case 0x0:
            break;
        case 0x1:
            nbbit = 32;
            break;
        case 0x2:
            nbbit = 64;
            break;
    }
    hed->EI_CLASS = nbbit;
    //Little or Big Endian reading and test
    test = read(1, endian);
    switch (test) {
        case 0x0:
            break;
        case 0x1:
            endian = 1;
            break;
        case 0x2:
            endian = 0;
            break;
    }
    hed->EI_DATA = endian;
    test = read(1, endian);
    hed->version=test;
    test = 0;

    // OS Type
    test = read(1, endian);
    hed->os_type = test;
    

    //Application Binary Interface Version
    test = read(1, endian);
    hed->abi_ver = test;

    fseek(fichier, 7, SEEK_CUR);

    //Type of ELF file
    test = read(2, endian);
    hed->elf_ftype = test;

    //Target architecture
    test = read(2, endian);
    hed->hw_target = test;

    //Version
    test = read(4, endian);
    hed->elf_ver=test;

    //Memory address of the entry point
    test = (read((nbbit / 8), endian));
    hed->e_entry = test;

    //offset header
    test = (read((nbbit / 8), endian));
    hed->e_phoff = test;

    //offset  section table
    test = (read((nbbit / 8), endian));
    hed->e_shoff = test;

    //flags
    test = read(4, endian);
    hed->flags=test;

    //header size
    test = read(2, endian);
    hed->e_ehsize = test;

    //size of the program header section
    test = read(2, endian);
    hed->e_phentsize = test;

    //number of entries in the program header section
    test = read(2, endian);
    hed->e_phnum = test;

    // size of a section
    test = read(2, endian);
    hed->e_shentsize = test;

    //number of entries in the section header table
    test = read(2, endian);
    hed->e_shnum = test;

    //index of the section header table entry
    test = read(2, endian);
    hed->e_shstrndx = test;

    return hed;
}
