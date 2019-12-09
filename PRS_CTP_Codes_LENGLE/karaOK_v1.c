/* ------------------------------------------------------------------------ */
/*	Programme karaOK														*/
/*																			*/
/*	Version 0								par	NOM Prénom 					*/
/*																			*/
/*						le 26 Novembre	2019									*/
/*																			*/
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/*					E N T Ê T E S    S T A N D A R D S						*/
/* ------------------------------------------------------------------------ */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

#include <time.h>			/* pour nanosleep()								*/
#include <libgen.h>			/* pour basename()								*/

/* ------------------------------------------------------------------------ */
/*					E N T Ê T E S    S P É C I F I Q U E S					*/
/* ------------------------------------------------------------------------ */
#include "common.h"

/* ------------------------------------------------------------------------ */
/*				C O N S T A N T E S     S Y M B O L I Q U E S				*/
/* ------------------------------------------------------------------------ */
#define	DUREE_VIE_PERE	8
#define	DUREE_VIE_FILS	3
#define NBMAX_FILS		7

/* ------------------------------------------------------------------------ */
/*						M A C R O - F O N C T I O N S						*/
/* ------------------------------------------------------------------------ */


/* ------------------------------------------------------------------------ */
/*				P R O T O T Y P E S    D E    F O N C T I O N S				*/
/* ------------------------------------------------------------------------ */
void processusFils(int);
void welcome(void);
void initialWait(int) ;

/* ------------------------------------------------------------------------ */
/*				V A R I A  B L E S     G L O B A L E S						*/
/* ------------------------------------------------------------------------ */

char * Msg [NBMAX_FILS] =
{
    "Do, le dos il a bon dos",
    "Ré, rayon de soleil d'or",
    "Mi, c'est la moitié d'un tout",
    "Fa, c'est facile à chanter",
    "Sol, la terre où vous marchez",
    "La, l'endroit où nous allons",
    "Si, siffler comme un pinson",
};

pid_t pidFils [NBMAX_FILS];

struct random_data rd[NBMAX_FILS];
char state[NBMAX_FILS][32];


/* ------------------------------------------------------------------------ */
/*					F O N C T I O N    P R I N C I P A L E					*/
/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
    int nbFils = 0;

    /* -------------------------------------------------------------------- */
    /*	Traitement des arguments de la ligne de commande					*/
    /* -------------------------------------------------------------------- */
    if (argc > 1)
        nbFils = atoi(argv[1]);
    if (nbFils <= 0)
        nbFils = 1;		// Un seul fils, par défaut
    else if (nbFils > NBMAX_FILS)
        nbFils = NBMAX_FILS;

    /* -------------------------------------------------------------------- */
    /*	Message de bienvenue												*/
    /* -------------------------------------------------------------------- */
    welcome();

    /* -------------------------------------------------------------------- */
    /*	Création des processus fils											*/
    /* -------------------------------------------------------------------- */
	pid_t pid;
    for (int i = 0; i < nbFils; i++)
    {
        CHECK(pidFils[i] = fork(), "fork()");
        if (pidFils[i] == 0)
        {
        	
            processusFils(i);	/*	la numérotation des fils commence à 0	*/
            
        }
        else 		/* suite du processus père								*/
        {
            // !!! L'appel ci-dessous sera mis en commentaire, ultérieurement
           // system("echo ;ps -o pid,ppid,size,cls,comm,cmd");
           
        }
    }

    /* -------------------------------------------------------------------- */
    /*	Suite et fin du processus père										*/
    /* -------------------------------------------------------------------- */


    //	!!! La ligne ci-dessous sera mise en commentaire, ultérieurement
   // sleep(DUREE_VIE_PERE);
   for(int i = 0; i < nbFils; i++ ){
   	pid = wait(&pidFils[i]);
           fprintf(stderr, "\tFils %d : \tfin du processus de pid : %d\n", i+1 , pid);
   }

    setTerm(YELLOW);
    system("echo; ps -l");
    printf("\nFin du programme %s de pid = %d\n\n",
           basename(argv[0]), getpid());
    resetTerm();
    exit(EXIT_SUCCESS);
}
/* ------------------------------------------------------- Fin de main ---- */


/* ------------------------------------------------------------------------ */
/*		Processus Fils														*/
/*																			*/
/*	Cette fonction reçoit comme paramètre le n° du processus fils (entre	*/
/*	0 et nbFils -1															*/
/*																			*/
/*	Ce processus se termine et fournissant le n° du fils reçu en paramètre	*/
/*	comme code de terminaison												*/
/* ------------------------------------------------------------------------ */
void processusFils(int no)
{
/*
    struct timespec delai = { .tv_sec = DUREE_VIE_FILS, .tv_nsec = 0L};

    fprintf(stderr, "\n\tFils %d : \tlancement effectif du processus %d,"
            " fils de %d\n", no + 1, getpid(), getppid());

    nanosleep(&delai, NULL);

    fprintf(stderr, "\tFils %d : \tfin du processus %d\n",
            no + 1, getpid());

    exit(no);*/
    
    
    struct timespec delai = { .tv_sec = 0, .tv_nsec = 100000000L};
    initialWait(no);
    fprintf(stderr, "\n\tFils %d : \tlancement effectif du processus %d,"
            " fils de %d\n", no + 1, getpid(), getppid());
    //sleep(DUREE_VIE_FILS);
    setTerm(RED + no);
    printf("\t\"");
    for (char * p = Msg[no]; *p != '\0'; p++){
    	printf("%c", *p);
    	fflush(stdout);
    	 nanosleep(&delai, NULL);
    }
    printf("\"\n");
    resetTerm();
    //fprintf(stderr, "\tFils %d : \tfin du processus %d\n",no + 1, getpid());

    exit(no);
    
}


/* ------------------------------------------------------------------------ */
void initialWait(int no)
{
    int32_t random = 0;
    struct timespec delai = {.tv_sec = 1, .tv_nsec = 0};

    initstate_r(0, state[no], sizeof(state[0]), &rd[no]);
    srandom_r(getpid(), &rd[no]);
    random_r(&rd[no], &random);

    delai.tv_nsec = (random % 32767L) * 50000L;
    fprintf(stderr,"Durée d'attente du fils %d = %d ms\n", no + 1,
            (int)((delai.tv_nsec + delai.tv_sec * 1000000000) / 1000000L));
    nanosleep(&delai, NULL);
}


/* ------------------------------------------------------------------------ */
void welcome(void)
{
    clearScreen();
    setTerm(YELLOW);
    printf("\t+-------------------------------------------------+\n");
    printf("\t|    Je suis le processus %5d, fils de %5d    |\n",
           getpid(), getppid());
    printf("\t+-------------------------------------------------+\n");
    resetTerm();

#if defined(_REFRAIN_)
    fprintf(stderr, "\nExtrait du refrain ... \n");
    for (int i = 0; i < NBMAX_FILS; i++)
    {
        fprintf(stderr, "\t\"");
        for (char * p = Msg[i]; *p != '\0'; p++)
            fprintf(stderr, "%c", *p);
        fprintf(stderr, "\"\n");
    }
    fprintf(stderr, "\n");
#endif
}
/* ------------------------------------------------------------- THE END -- */


