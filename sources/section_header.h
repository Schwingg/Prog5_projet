
typedef struct {
    int sh_name;
    int sh_type;
    int sh_flags;
    int sh_addr;
    int sh_offset;
    int sh_size;
    int sh_link;
    int sh_info;
    int sh_addralign;
    int sh_entsize;
} SEC_HEADER;

FILE* fichier

SEC_HEADER *section_header(FILE *fichier)