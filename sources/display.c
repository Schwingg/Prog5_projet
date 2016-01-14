
#include "projet.h"


////////////////////HEADER///////////////////
//#Displays the header, using the HEADER structure#//
//#HEADER contains all the informations needed#//
//#command : -h#//
void display_header(HEADER *hed){
    if(hed->ELF == 0){
        printf("This is not an ELF file\n");
    }
    else{
        printf("Class                                           ELF");
    }

    if( hed->EI_CLASS == 32){
        printf("32/bits\n");
    }
    else if ( hed->EI_CLASS == 64){
        printf("64/bits\n");
    }
    else{
        printf("/n No indication about address size?\n");
    }

    printf("Data:                                           ");
    if( hed->EI_DATA == 1){
        printf("Little Endian\n");
    }
    else if ( hed->EI_DATA == 0){
        printf("Big Endian\n");
    }
    else{
        printf("No indication about endianness\n");
    }

    printf("Version:                                        ");
    printf("%d\n", hed->version);

    printf("OS type:                                        ");
    switch (hed->os_type) {
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
        
    printf("ABI Version :                                   %d\n", hed->abi_ver);

    printf("Type:                                           ");
    switch (hed->elf_ftype) {
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
        
    printf("Target architecture:                            ");
    switch (hed->hw_target) {
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
        
    printf("Version:                                        ");
    if (hed->elf_ver == 1) printf("Original version of ELF\n");
        else printf("Not original version of ELF\n");

    printf("Memory address of the entry point :             0x%04X\n", hed->e_entry);

    printf("Start of the program header table :             %d\n", hed->e_phoff);

    printf("Start of the section header table :             %d\n", hed->e_shoff);

    printf("Flags :                                         0x%04X\n", hed->flags);

    printf("Size of the header :                            %d\n", hed->e_ehsize);

    printf("Size of a program header table entry :          %d\n", hed->e_phentsize);

    printf("Number of entries in the program header table : %d\n", hed->e_phnum);

    printf("Size of a section header table entry :          %d\n", hed->e_shentsize);

    printf("Number of entries in the section header table : %d\n", hed->e_shnum);

    printf("Index of the section header table entry :       %d\n\n", hed->e_shstrndx);
}
/////////////////////////////////////////////

////////////////////SECTIONS_TABLE///////////
//#Displays the sections table, using the HEADER and SEC_HEADER structures#//
//#HEADER is used for the offset of the sections table and the number of sections#//
//#SEC_HEADER is used to retrieve the rest of the infos#//
//#command : -S#//
void display_sections_table(HEADER* hed,SEC_HEADER **sections){
        int i;
        printf("Position de la table des noms : 0x%04X\n", hed->pos);
        for (i = 0; i < hed->e_shnum; i++) {
        printf("[%d]\n", i);
        printf("Name :		%s\n", sections[i]->sh_name);
        printf("Type :		");
        switch (htobe32(sections[i]->sh_type)) {
            case 0:
                printf("NULL\n");
                break;
            case 1:
                printf("PROGBITS\n");
                break;
            case 2:
                printf("SYMTAB\n");
                break;
            case 3:
                printf("STRTAB\n");
                break;
            case 4:
                printf("RELA\n");
                break;
            case 5:
                printf("HASH\n");
                break;
            case 6:
                printf("DYNAMIC\n");
                break;
            case 7:
                printf("NOTE\n");
                break;
            case 8:
                printf("NOBITS\n");
                break;
            case 9:
                printf("REL\n");
                break;
            case 10:
                printf("SHLIB\n");
                break;
            case 11:
                printf("DYNSYM\n");
                break;
		}
		switch (sections[i]->sh_type) {
            case 0x70000000:
                printf("LOPROC\n");
                break;
            case 0x7fffffff:
                printf("HIPROC\n");
                break;
            case 0x80000000:
                printf("LOUSER\n");
                break;
            case 0xffffffff:
                printf("HIUSER\n");
                break;
        }
        printf("Adress :	0x%08X\n", htobe32(sections[i]->sh_addr));
        printf("Offset :	0x%06X\n", htobe32(sections[i]->sh_offset));
        printf("Size :		0x%06X\n", htobe32(sections[i]->sh_size));
        printf("EntSize :	0x%02X\n", htobe32(sections[i]->sh_entsize));
        printf("Flags :		");
        switch (htobe32(sections[i]->sh_flags)) {
            case 0:
                printf("\n");
                break;
            case 1:
                printf("W\n");
                break;
            case 2:
                printf("A\n");
                break;
            case 3:
                printf("WA\n");
                break;
            case 4:
                printf("X\n");
                break;
            case 5:
                printf("XW\n");
                break;
            case 6:
                printf("XA\n");
                break;
            case 7:
                printf("XWA\n");
                break;
        }
        printf("Link :		%d\n", htobe32(sections[i]->sh_link));
        printf("Info :		%d\n", htobe32(sections[i]->sh_info));
        printf("AddrAlign :	%d\n", htobe32(sections[i]->sh_addralign));
        printf("------------------\n");
    }
}
/////////////////////////////////////////////

////////////////////SECTIONS/////////////////
//#Displays the selected section, using the HEADER, SEC_HEADER structures and the FILE#//
//#name is the name of the selected section#//
//#hed is used as a limit#//
//#sections contains the name and offset of a section#//
//#fichier is used to read the infos about the section#//
//#command : -x#//
void display_sections_name(char* name,HEADER* hed,SEC_HEADER **sections,FILE* fichier){
    int found = 0;
    int i=0;
    int j,k=0;
    unsigned int hex = 0x0;
    while (found != 1 && i<hed->e_shnum){
        if (strcmp(name,sections[i]->sh_name) == 0){
            found = 1;
        }
        else{
            i++;
        }
    }
    if (found){
        fseek(fichier, htobe32(sections[i]->sh_offset), SEEK_SET);
        printf("Section %s\n", sections[i]->sh_name);
        printf("addr |                data");
        printf("\n------------------------------------------");
        for (j = htobe32(sections[i]->sh_offset); j < htobe32(sections[i]->sh_offset) + htobe32(sections[i]->sh_size); j = j + 4) {
                //Return to line
                if (k %4  == 0) {
                    printf("\n%04x | ", j);
                }
                k++;
                fread(&hex, 4, 1, fichier);
                hex = htobe32(hex);
                printf("%08x ", hex);
                hex = 0;
            }
            k = 0;
            printf("\n------------------------------------------\n");
            printf("addr |      data");
            printf("\n\n");
    }
}


//#Displays the selected section, using the HEADER, SEC_HEADER structures and the FILE#//
//#off is the number of the selected section#//
//#sections contains the name and offset of a section#//
//#fichier is used to read the infos about the section#//
//#command : -x#//
void display_sections_int(int off,SEC_HEADER **sections,FILE* fichier){
    int j,k=0;
    int i =off;
    unsigned int hex = 0x0;;
    if (sections[i]){
        fseek(fichier, htobe32(sections[i]->sh_offset), SEEK_SET);
        printf("Section %s\n", sections[i]->sh_name);
        printf("addr |                data");
        printf("\n------------------------------------------");
        for (j = htobe32(sections[i]->sh_offset); j < htobe32(sections[i]->sh_offset) + htobe32(sections[i]->sh_size); j = j + 4) {
                //Return to line
                if (k %4  == 0) {
                    printf("\n%04x | ", j);
                }
                k++;
                fread(&hex, 4, 1, fichier);
                hex = htobe32(hex);
                printf("%08x ", hex);
                hex = 0;
            }
            k = 0;
            printf("\n------------------------------------------\n");
            printf("addr |      data");
            printf("\n\n");
     }
}
/////////////////////////////////////////////

////////////////////SYMBOLS//////////////////
//#Displays the symbols table#//
//#command : -s#//
void display_symbols(SEC_HEADER* symb_tab, SEC_HEADER* str_tab, SYMB_HEADER **symbole){
    unsigned long SYMB_SIZE = htobe32(symb_tab->sh_size);
    int i;
    int LONGUEUR_SYMB = 16;// 16 = size of a line in the symbols tab (bytes)
    int nbr_symb = SYMB_SIZE / LONGUEUR_SYMB;
        for (i=0;i < nbr_symb ;i++){
    	printf("Name :		%s\n", symbole[i]->st_name);
    	printf("Value :		%x\n", symbole[i]->st_value);
    	printf("Size :		%d\n", symbole[i]->st_size);
      
      switch(symbole[i]->st_info >>4){
      		case(0):
      			printf("LOCAL\n");
      			break;
      			case(1):
      			printf("GLOBAL\n");
      			break;
      			case(2):
      			printf("WEAK\n");
      			break;
      			case(13):
      			printf("LOPROC\n");
      			break;
      			case(15):
      			printf("HIPROC\n");
      			break;
      			}
      			
     switch(symbole[i]->st_info & 0xf){
      		case(0):
      			printf("NOTYPE\n");
      			break;
      			case(1):
      			printf("OBJECT\n");
      			break;
      			case(2):
      			printf("FUNC\n");
      			break;
      			case(3):
      			printf("SECTION\n");
      			break;
      			case(4):
      			printf("FILE\n");
      			break;
      			case(13):
      			printf("LOPROC\n");
      			break;
      			case(15):
      			printf("HIPROC\n");
      			break;
      			}

    	printf("Other :		DEFAULT\n");// Unused value : st_other
    	printf("Ndx :		%d\n", symbole[i]->st_shndx);
    	printf("---------------------\n\n");
    	}
}
/////////////////////////////////////////////

////////////////////REL//////////////////////
//#displays the relocation sections informations#//
//#command : -r#//
void display_rel_a(SEC_HEADER** sections, int nbSecs){
	int i = 0, j = 0;
	
	for(i = 0; i < nbSecs; i++)
	{
		if(strstr(sections[i]->sh_name,".rel.") != NULL)
		{
			disp_rel_sections = (REL **) malloc(sections[i]->sh_offset/8 * (sizeof (REL))); // 2 words (8 bytes)
			if (disp_rel_sections == NULL)
        exit(1);
        
			printf("%s : \n",sections[i]->sh_name);
			printf("Decalage|  Info  |   Symb  |  Type  \n");
			for(j = 0; j < htobe32(sections[i]->sh_size); j += 8)
			{
				disp_rel_sections[j] = (REL*) malloc(sizeof (REL));
				if (disp_rel_sections[j] == NULL)
					exit(1);
			
				fseek(fichier,htobe32(sections[i]->sh_offset)+j,SEEK_SET);
				fread(&disp_rel_sections[j]->r_offset,sizeof(int),1,fichier);
				fread(&disp_rel_sections[j]->r_info,sizeof(int),1,fichier);

				printf("%8x %8x ", htobe32(disp_rel_sections[j]->r_offset), htobe32(disp_rel_sections[j]->r_info));
				printf("%8x %8x ", htobe32(disp_rel_sections[j]->r_info) >> 8, (unsigned char)htobe32(disp_rel_sections[j]->r_info));
				printf("\n");
			}
			printf("\n");
		}
		else if(strstr(sections[i]->sh_name,".rela.") != NULL)
		{
			rela_sections = (REL **) malloc(sections[i]->sh_offset/12 * (sizeof (REL))); // 3 words (12 bytes)
			if (rela_sections == NULL)
        exit(1);
        
			printf("%s : \n",sections[i]->sh_name);
			printf("Decalage|  Info  |Addened |  Symb  |  Type  ");
			for(j = 0; j < htobe32(sections[i]->sh_size); j += 12)
			{
				rela_sections[j] = (REL*) malloc(sizeof (REL));
				if (rela_sections[j] == NULL)
					exit(1);
			
				fseek(fichier,htobe32(sections[i]->sh_offset)+j,SEEK_SET);
				fread(&rela_sections[j]->r_offset,sizeof(int),1,fichier);
				fread(&rela_sections[j]->r_info,sizeof(int),1,fichier);

				printf("%8x %8x %8x ", htobe32(rela_sections[j]->r_offset), htobe32(rela_sections[j]->r_info),htobe32(rela_sections[j]->r_addend));
				printf("%8x %8x ", htobe32(rela_sections[j]->r_info) >> 8, (unsigned char)htobe32(rela_sections[j]->r_info));
				printf("\n");
			}
			printf("\n");
		}
	}
}
/////////////////////////////////////////////

////////////////////HELP/////////////////////
//#displays an help#//
//#command : -H#//
void help(){
    printf("////help////\n");
    printf("//commands//\n");
    printf("-f : input file\n");
    printf("    argument required (file)\n");
    printf("\n");
    printf("-h : display header\n");
    printf("\n");
    printf("-S : display section_header\n");
    printf("\n");
    printf("-x : display section\n");
    printf("    argument required (number or name of section)\n");
    printf("\n");
    printf("-s : display symbols\n");
    printf("\n");
    printf("-r : display relocation info\n");
    printf("\n");
    printf("-H : help\n");
    printf("////////////\n");
}
/////////////////////////////////////////////
