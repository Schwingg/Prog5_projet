#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
FILE *fichier;
///////////////////////////////MAIN///////////////////////////////////
/*
 Allows to quit the program, specifying if a problem occurs
 */
void ferme();

/*
 Frees the structures used
 */
void desalloc();

///////////////////////////////////////////////////////////////////////

///////////////////////////////PARTIE 1////////////////////////////////
///////////////////////////////linked to read_header.c/////////////////
/*
 HEADER structure
 */
typedef struct {
    int ELF;
    int EI_CLASS;
    int EI_DATA;
    int e_entry;
    int e_phoff;
    unsigned int e_shoff;
    int e_ehsize;
    int e_phentsize;
    int e_phnum;
    unsigned int e_shentsize;
    unsigned int e_shnum;
    unsigned int e_shstrndx;
    ///////////
    int version;
    int os_type;
    int abi_ver;
    int elf_ftype;
    int hw_target;
    int elf_ver;
    int flags;
    int pos;
} HEADER;



/*
 Contains the function allowing to read the header
 */
HEADER *read_header(FILE *fichier);

//print function
void display_header(HEADER *hed);

/*
 Allows to skip a defined number of bytes
 octet is the number of bytes to skip 
 */
void jump(int octet);

/*
 Allows to read a defined number of bytes either in Little or Big Endian
 octet indicates the number of bytes to read
 endian indicates the Endianness : 1 for Little, 0 for Big
 */
int read(int octet, int endian);
///////////////////////////////////////////////////////////////////////

///////////////////////////////PARTIE 2////////////////////////////////
///////////////////////////////linked to section_header.c//////////////
/*
 SECTIONS HEADER structure
 */
typedef struct {
    char * sh_name;
    int sh_type;
    int sh_flags;
    unsigned int sh_addr;
    unsigned int sh_offset;
    unsigned int sh_size;
    int sh_link;
    int sh_info;
    int sh_addralign;
    int sh_entsize;
} SEC_HEADER;

//display function
void display_sections_table(HEADER* hed,SEC_HEADER **sections);

/*
 * This program allows to get the header of a section.
 * You must provide to the program a HEADER structure that
 * contain all the information of the ELF header.
 */
SEC_HEADER **section_header(FILE *fichier, HEADER *hed);
///////////////////////////////////////////////////////////////////////

///////////////////////////////PARTIE 3////////////////////////////////
///////////////////////////////linked to read_section.c////////////////
/*
 reads the sections data
 */
int read_section(FILE* fichier, SEC_HEADER **sections, HEADER *hed);

//Display functions
void display_sections_name(char* name,HEADER* hed,SEC_HEADER **sections,FILE* fichier);
void display_sections_int(int off,SEC_HEADER **sections,FILE* fichier);
///////////////////////////////////////////////////////////////////////

///////////////////////////////PARTIE 4////////////////////////////////
///////////////////////////////linked to sybol_header.c////////////////
/*
 Symbols table structure
 */
typedef struct {
    char* st_name;
    unsigned int st_value;
    unsigned int st_size;
    unsigned char st_info;
    unsigned char st_other;
    unsigned short st_shndx;
}SYMB_HEADER;

//display function
void display_symbols(SEC_HEADER* symb_tab, SEC_HEADER* str_tab, SYMB_HEADER **symbole);

SYMB_HEADER **symbole_header(FILE* fichier, SEC_HEADER* symb_tab, SEC_HEADER* str_tab);
///////////////////////////////////////////////////////////////////////

///////////////////////////////PARTIE 5////////////////////////////////
///////////////////////////////linked to rel.c/////////////////////////
/*
 relocable sections structure
 */
typedef struct {
	unsigned long r_offset ;
	unsigned long r_info;
	long r_addend; //To support RELA
	int rela;
} REL;

//display function
void display_rel_a(SEC_HEADER** sections, int nbSecs);

SEC_HEADER ** get_rel_sections(SEC_HEADER ** sections, int nbSecs, int * nb_rel_sec);

REL** get_rel_entries(SEC_HEADER * section, int* nb_entrees);
///////////////////////////////////////////////////////////////////////


///////////////////////////////OPTIONS//////////////////////////////////
///////////////////////////////linked to projet.c///////////////////////
/*
 Commands structure
 */
typedef struct {
    int header;
	int section_head;
	int section;
	int symbols;
	int help;
	int reloc;
	char* fich;
	int sec_type; // 0 si int, 1 si char
	char* sec_name;
	int sec_num;
} PAR;

//parameters and commands handler
void parameters(int argc,char *argv[],PAR *par);

//help function
void help();
///////////////////////////////////////////////////////////////////////
void num_section(HEADER * hdr, SEC_HEADER ** sections, int nb_rel_secs, SYMB_HEADER ** symb, FILE * fichier);

HEADER *hed;

SEC_HEADER **sections;

SYMB_HEADER **symb;

SEC_HEADER** rel_sections;

REL ** rel_section;

REL **rela_sections;

REL **disp_rel_sections;

PAR *par;

int nbr_rel;
int nbr_symb;//nombre de symboles dans la table
