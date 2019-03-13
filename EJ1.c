#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

int main (int argc, char **argv){

		static struct option long_options[] =
	{


		{"username",	 no_argument,	   0, 'u'},
		{"useruid",  no_argument,	   0, 'i'},
		{"groupname",  no_argument, 0, 'g'},
		{"groupuid",  no_argument, 0, 'd'},
		{"allgroups",	no_argument, 0, 'e'},
		{"allinfo",	required_argument, 0, 'a'},
		{"bactive",	required_argument, 0, 'b'},

		{0, 0, 0, 0}
	};

    char *avalue = NULL;
    int c;
    char *lgn;
    char *lgn1;
    char *user="LOGNAME";
    struct group *auxg;
    struct passwd *pw;
    struct passwd *pw1;
    struct group *gr;
    struct group *gr1;

    int option_index = 0;

    opterr = 0; 



    if ((lgn = getenv(user) ) == NULL || (pw = getpwnam(lgn)) == NULL)
        {
            fprintf(stderr, "Get of user information failed.\n");
            exit(1);
        }

    gr = getgrgid(pw->pw_gid);

    while ((c = getopt_long (argc, argv, "uigdea:b", long_options, &option_index)) != -1)
    {
      
        switch (c)
        {
		     case 'u':
		         printf("Nombre: %s\n", pw->pw_gecos);
		         break;

		     case 'i':
		         printf("UID: %d\n", pw->pw_uid);
		         break;

		     case 'g':
		         printf("Nombre del grupo principal: %s\n", gr->gr_name);
		         break;

		     case 'd':
		         printf("Número de grupo principal: %d\n", pw->pw_gid);
		         break;  

		     case 'e':
		     setgrent();
		     while( (auxg = getgrent()) != NULL){

		     }		   
		     endgrent();
		     break;  

		     case 'a':

		        avalue=optarg;

		        if ((lgn1 = avalue ) == NULL || (pw1 = getpwnam(lgn1)) == NULL)
        		{
           		fprintf(stderr, "No se encuentra el usuario\n");
            	exit(1);
            	}

      			printf("Nombre: %s\n", pw1->pw_gecos);
				printf("UID: %d\n", pw1->pw_uid);
				gr1 = getgrgid(pw1->pw_gid);
				printf("Nombre del grupo principal: %s\n", gr1->gr_name);
				printf("Número de grupo principal: %d\n", pw1->pw_gid);

		     break;

		     case 'b':
		     printf("Número de grupo principal: %d\n", pw->pw_gid);
		     printf("Nombre del grupo principal: %s\n", gr->gr_name);
		     break;
		     case '?':
		    	 if (optopt == 'a') //Para el caso de que 'a' no tenga el argumento obligatorio.
		             fprintf (stderr, "La opción %c requiere un argumento. Valor de opterr = %d\n", optopt, opterr);
		         else if (isprint (optopt)) //Se mira si el caracter es imprimible
		             fprintf (stderr, "Opción desconocida \"-%c\". Valor de opterr = %d\n", optopt, opterr);
		         else //Caracter no imprimible o especial
		             fprintf (stderr, "Caracter `\\x%x'. Valor de opterr = %d\n", optopt, opterr);
		         return 1;

		     default:
		         abort ();
        }
	}
}