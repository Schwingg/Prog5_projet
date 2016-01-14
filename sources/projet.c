
#include "projet.h"



//Closes the file used by the program
void ferme() {
    fclose(fichier);
}

//frees the structures used by the program
void desalloc() {
    int i;
 
    free(rel_sections);
    
    free(disp_rel_sections);
    
    free(rela_sections);
    
    for (i = 0; i < nbr_symb; i++) {
        free(symb[i]); 	
      }
    free(symb);
    
    for (i = 0; i < hed->e_shnum; i++) {
        free(sections[i]);
    	}
    free(sections);
 
    free(hed);
    free(par);
}

//defines the usable parameters and their specifications
struct option longopts[] = {
		{ "header", no_argument, NULL, 'h' },
		{ "section_header", no_argument, NULL, 'S' },
		{ "section", required_argument, NULL, 'x' },
		{ "symbols", no_argument, NULL, 's' },
		{ "help", no_argument, NULL, 'H' },
		{ "file", no_argument, NULL, 'f' },
		{ "reloc", no_argument, NULL, 'r' },
		{ NULL, 0, NULL, 0 }
	};

//parameter handler, initializes the PAR structure
//each user command activates a boolean
void parameters(int argc,char *argv[], PAR *par){
    int opt;
    par->header = 0;
    par->section_head = 0;
    par->section=0;
    par->sec_type = 0;
    par->symbols = 0;
    par->help = 0;
    par->reloc =0;
    while ((opt = getopt_long(argc, argv, "hSx:sHf:r", longopts, NULL)) != -1) {
		switch(opt) {
		case 'h':
			par->header = 1;
			break;
		case 'S':
			par->section_head = 1;
			break;
		case 'x':
			par->section=1;
			if(!atoi(optarg) && optarg[0] != '0'){
			    par->sec_type = 1;
			}
			if(par->sec_type==0){
			    par->sec_num = strtol(optarg,NULL,10);
			}
			else{
			    par->sec_name = optarg;
			}
			break;
		case 's':
			par->symbols = 1;
			break;
		case 'H':
			par->help = 1;
			break;
		case 'f':
			par->fich = optarg;
			break;
		case 'r':
			par->reloc = 1;
			break;
		default:
			fprintf(stderr, "option non reconnue %c\n", opt);
			exit(1);
		}
	}
}
int main(int argc, char *argv[]) {
    //PARAMETERS
  par =(PAR*) malloc(sizeof(PAR));
	parameters(argc,argv,par);
	
    if (argc > 1) {
        //If the Help command has been activated, just show the help and exit
        //Else do the calculations    
        if(!par->help){
            ///###PHASE1###///
            
            //Open the file passed in argv[1] 
            if ((fichier = fopen(par->fich, "r"))) {
            } else {
                printf("impossible de lire le fichier\n");
                return 1;
            }
            
            //PART 1
            hed = read_header(fichier);
            if(par->header ==1){
                display_header(hed);
            }
            // If the file is an ELF 32 file
            if (hed->ELF == 1 && hed->EI_DATA == 0 && hed->EI_CLASS == 32) {
                
                //PART 2
                //Reading of the section header          
                sections = section_header(fichier, hed);
                if(par->section_head ==1 ){
                    display_sections_table(hed,sections);
                }
                
                //PART 3
                //Sections content reading
                if (read_section(fichier, sections, hed) == 1) {
                    printf("Erreur lors de lallocation du pointeur");
                    return 1;
                }
                if (par->section == 1){
                    if(par->sec_type==1){
                        display_sections_name(par->sec_name,hed,sections,fichier);
                    }
                    else{
                        display_sections_int(par->sec_num,sections,fichier);
                    }
                }
                //PART 4
                //Symbols reading
                int j, x, i;
                for (i = 0; i < hed->e_shnum; i++) {
                    if (strcmp(sections[i]->sh_name, ".symtab") == 0) {
                        j = i;
                    }
                    if (strcmp(sections[i]->sh_name, ".strtab") == 0) {
                        x = i;
                    }
                }
                symb = symbole_header(fichier, sections[j], sections[x]);
                if(par->symbols == 1){
                    display_symbols(sections[j], sections[x], symb);
                }

			    //PART 5
			    //Reloc sections display
			    if (par->reloc == 1){
			    display_rel_a(sections, hed->e_shnum);
                }
                
            ///###PHASE2###///
	        // Step 6 to 9
	        int a = 0;
	        get_rel_sections(sections,hed->e_shnum,&a);
	        num_section(hed,sections,a,symb,fichier);

                desalloc();
                return 0;
                
            } else {// Header reading returned an error
                ferme();
                free(hed);
                printf("Le fichier d'entrée n'est pas un fichier ELF 32 bits ARM.\n");
                return 1;
            }
            
        }
        else{//the -H command has been activated
            help();
        }
    }
     else {// argv[1] is empty
        help();
        return 1;
    }
    return 0;
}
