
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
} HEADER;

FILE* fichier;


/*
 Contains the function allowing to read the header
 */
HEADER *read_header(FILE *fichier);

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
