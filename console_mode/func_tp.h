#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*******************structures utilisées****************************************/
typedef struct Equipe //Structure de base (= Maillon)
{
    char nom[20];
    int numPoule;
    int totEncais;
    int totMarq;
    int points; //Phase de poule
    int numMatch; // Post-poule
    struct Equipe *next;
    struct Equipe *prev;
} Equipe;


typedef struct Poule{
    Equipe* tete;
    Equipe* queue;
    struct Poule* next;
    }Poule;

typedef struct Resultats //pour le tableau des resultas
{
    char equipe1[20];
    char equipe2[20];
    int  resu1;
    int  resu2;
    char phase[20];
    char winner[15];
    char loser[15];
    char Note [7];
}Resultats;

typedef struct EquipePoule //on s'en servira pour l'affichage les resultat des equipe apres la phase poule
{
    char nom[20];
    int numPoule;
    int totEncais;
    int totMarq;
    int points;
} EquipePoule;



    /*********************fuction***********************/

    /*pour la structure Equipe*/
Equipe* allouerB();

void libererB(Equipe**ancien);

void affName(Equipe *m, char name[20]);

void affAdrGB(Equipe *m, Equipe *n);

void affAdrDB(Equipe *m, Equipe *n);

void affname(Equipe *m, char name[20]);

Equipe* suivantB(Equipe* T );

void supprimeB(Equipe **m , int* nb_chain);




    /*pour la structure maillon */
Poule* allouer();

void aff_adr(Poule *p , Poule *q);

void aff_tete(Poule *p , Equipe *Eq);

void aff_queue(Poule *p , Equipe *Eq);

void supprime(Poule **m ,Poule ** prev , int *nb_chain);

Poule* suivant(Poule *p);




   /*relatif au programme */
void creationEquipe( Equipe **T, int numpoule , int * nb_eq_allou, char* namae  );

void creationPoule( Equipe** tete ,Equipe** queue, int numeroPoule ,  int * nb_eq_allou , int *nb_chain, int *step);

void creationTournoi( Poule** tournois, int nbPoule, int * nb_eq_allou , int* nb_chain , int *nb_poul_allou);

void simulMatch( Equipe *team1, Equipe *team2, Resultats tab[],int cptr ,char* phase);

void deroulement_poule(Equipe* tete , Equipe* queue , Resultats tab[] , int *nb_match, int *numPoule);

void classement(Equipe **tete, Equipe **queue , int* nb_comp ,int* nb_chain);

void permutEq(Equipe**tete ,Equipe**queue, Equipe *eq1, Equipe *eq2 ,  int * nb_chain);

void fusion_poul( Equipe**tete1,Equipe** queue1 , Equipe**tete2 ,Equipe** queue2 , int*nb_chain);

void prem_to_tournois(Poule* tete_tournois  , int*nb_chain);

int simulMatch_post_poule( Equipe **team1, Equipe **team2,int num_match , Resultats tab[],int cptr , char phase [30] , int*nb_chain); //cptr c pour l'indice du tableau des resulats

void deroulement_post_poule(Equipe** tete , Equipe** queue , Resultats tab[] , int* nb_match , int *match_tournois , int* nb_eq_allou ,int*nb_chain);//deroulement des matche dans une poul apres la phase eliminatoire         team->tete = tete; team->queue = tail;

void fusion_post_poul(Equipe**tete1,Equipe** queue1 , Equipe**tete2 ,Equipe** queue2 ,int*nb_chain); //fusionne le poul apres la phase eliminatoire

void organisation_tournois(Poule* tete_tournois ,int *nb_chain);//assure l'organisation du tournois en poul de 4 element chacune apres la phase eliminatoire

void deroulement_tournois(Equipe** tete , Equipe** queue , int np ,Resultats tab[] , int* nb_match , int *match_tournois , int*nb_eq_allou , int*nb_chain); //ce module assure le deroulement des matches dans les poul en utilsant la règle d’organiser les affrontements en nombre pair et impair.

int pair(int chifre);//renvois 1 lorsque chifre est pair et 0 sinon

int nombreMatch (int np);// Calculer le nombre total de matchs qui auront lieu --- np = Nombre de Poules

