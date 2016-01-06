typedef struct {
    char* st_name;
    unsigned int st_value;
    unsigned int st_size;
    unsigned char st_info;
    unsigned char st_other;
    unsigned short st_shndx;
}SYMB_HEADER;

SYMB_HEADER **symbole_header(FILE* fichier, SEC_HEADER* symb_tab, SEC_HEADER* str_tab);
