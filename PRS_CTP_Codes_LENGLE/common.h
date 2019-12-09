/* ------------------------------------------------------------------------ */
/*	Fichier common.h														*/
/* ------------------------------------------------------------------------ */


#if ! defined( _COMMON_H_ )
#define _COMMON_H_

enum
{
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    BLINK = 5,
    HIGH  = 1,
    INV   = 7,
};


/* ------------------------------------------------------------------------ */
/*						M A C R O - F O N C T I O N S						*/
/* ------------------------------------------------------------------------ */
#define CHECK(sts, msg)				\
	if (-1 == (sts) ) 				\
	{								\
		perror(msg);				\
		exit(EXIT_FAILURE);			\
	}

#define CHECK_IFNULL(sts, msg)	    \
	if (NULL == (sts) ) 			\
	{								\
		perror(msg);				\
		exit(EXIT_FAILURE);			\
	}

/* ------------------------------------------------------------------------ */
/*          GESTION DU MODE D'AFFICHAGE SUR LE TERMINAL                     */
/* ------------------------------------------------------------------------ */
#define clearScreen()  	{ printf("\033[H\033[2J");fflush(stdout); }
#define setTerm(param)  { printf("\033[1m\033[%dm", param); fflush(stdout); }
#define resetTerm()		setTerm(0)


/* ------------------------------------------------------------------------ */
/*      N O M S   D E S   F I C H I E R S   S E M A P H O R E S            	*/
/* ------------------------------------------------------------------------ */

#define SEM_ECRAN      	"sem_ecran"
#define	SEM_SYNCHRO		"sem_synchro"

#endif
