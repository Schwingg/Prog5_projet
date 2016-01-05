

/*
 Contains the function allowing to read the header
 */
int read_header(FILE *fichier);

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
