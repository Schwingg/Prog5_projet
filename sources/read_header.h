

/*
 contient la fonction permettant de faire la lecture du header
 */
int read_header(FILE *fichier);

/*
 * permet de sauter un nombre definit d'octet
 * octet est le noombre d'octet qu'il faut sauter 
 */
void jump(int octet);

/*
 * permet de lire un nombre definit d'octet soit en little soit en big endian
 * octet indique le nombre d'octet quil faut lire 
 * endian est la methode dencodage 1 pour little 0 pour big
 */
int read(int octet, int endian);
