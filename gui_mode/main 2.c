
#include "func_tp.h"




int main2()
{

    Poule* tournment;
    Poule* pool;
    Equipe* head ;
    Equipe* tail;
    char *phase;
    Resultats *matches; //les resultas des matche
    int nombre_poul;
    int nombre_matche=0 ,i;
    int matche_tournois=0 , winner;
    int nb_mai_allou=0 , nb_chain=0 , nb_comp=0 ;
        //nombre maillon aloués  ,  nombre de chainage  , nombre de comparaison

/* fin de la declaration des variables */


    /*****   introduction  nombre de poul  et creation du tournois  ******/

    printf("veillez introduire le nombre de poule dans le tournois (le nombre de poule doit etre une puissance de 2 : 1, 2 , 4 ,8... ) :");
    scanf("%d", &nombre_poul);
    printf("\n");
    matches=malloc(sizeof(Resultats)*nombreMatch(nombre_poul));
    creationTournoi(&tournment,nombre_poul,&nb_mai_allou,&nb_chain,&nb_mai_allou);
    printf("\n\n");


    /*****     phase preliminaire   ******/
    pool = tournment;
    for(i=1 ; i<=nombre_poul ; i++)
    {
        head=pool->tete;
        tail=pool->queue;
        deroulement_poule(head,tail ,matches,&nombre_matche);
        aff_tete(pool,head);
        aff_queue(pool,tail);
        pool=suivant(pool);
    }




    /******   classement des equipes dans la poule    ******/
    pool = tournment;
    for(i=1 ; i<=nombre_poul ; i++)
    {
        head=pool->tete;
        tail=pool->queue;
        classement(&head,&tail ,&nb_comp , &nb_chain);
        aff_tete(pool,head);
        aff_queue(pool,tail);
        pool=suivant(pool);
    }




if(nombre_poul>=2)
{
    /***** passage de la phase prelliminaire  au tournois *****/
    prem_to_tournois(tournment , &nb_chain);
    nombre_poul=nombre_poul/2;
    printf("\n\n");





    /*****    phase poste_preleminaire   *****/
    pool = tournment;
    for(i=1 ; i<=nombre_poul ; i++)
    {
        head=pool->tete;
        tail=pool->queue;
        deroulement_post_poule(&head,&tail ,matches,&nombre_matche, &matche_tournois , &nb_mai_allou , &nb_chain);
        aff_tete(pool,head);
        aff_queue(pool,tail);
        pool=suivant(pool);
    }
    printf("\n\n");





    /*****   phase tournois  (quand on a 4 pool et plus)   *****/
    while (nombre_poul>=2)
    {
        organisation_tournois(tournment, &nb_chain);
        nombre_poul=nombre_poul/2;


        pool = tournment;
        for(i=1 ; i<=nombre_poul ; i++)
        {
            head=pool->tete;
            tail=pool->queue;
            deroulement_tournois(&head,&tail ,nombre_poul, matches,&nombre_matche, &matche_tournois ,&nb_mai_allou ,&nb_chain);
            aff_tete(pool,head);
            aff_queue(pool,tail);
            pool=suivant(pool);
        }
    }
}




    /******    la finale     ******/
    phase="la finale";
    nombre_matche++;
    matche_tournois++;
    head=tournment->tete;
    tail=tournment->queue;
    winner=simulMatch_post_poule( &head, &tail ,matche_tournois,matches,nombre_matche,phase ,&nb_chain);
    if (winner==1) printf("l'equipe gagnante de notre tournois est :  %s \n",head->nom);
    else printf("l'equipe gagnante de notre tournois est :  %s \n",tail->nom);



// for(i=1;i<=nombre_matche;i++)
// {
//     printf("les resulats du matche ( la phase est : %s) %d sont : \n %s %d - %d %s \n",matches[i].phase,i,matches[i].equipe1 , matches[i].resu1 ,matches[i].resu2 ,matches[i].equipe2);
// }

return 0;

}







