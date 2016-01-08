typedef struct {
	unsigned long r_offset ;
	unsigned long r_info;
	long r_addend; //To support RELA
	int rela;
} REL;

void display_rel_sections(FILE* fichier, SEC_HEADER** sections, int nbSecs);

SEC_HEADER ** get_rel_sections(SEC_HEADER ** sections, int nbSecs);

REL** get_rel_entries(SEC_HEADER * section);
