#include "section_header.h"

typedef struct {
	unsigned long r_offset ;
	unsigned long r_info;
} REL;

typedef struct{
	unsigned long r_offset;
	unsigned long r_info;
	long r_addend;
} RELA;

REL** get_rel_sections(FILE* fichier, SEC_HEADER** sections, int nbSecs);
