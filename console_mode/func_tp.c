
#include "func_tp.h"


//--------------------------/* Controle de Structure "Equipe" */--------------------------//

//-------------------------------------
Equipe* allouerB()  // Alloquation d'Žquipe
{
    Equipe *M = ((Equipe*)malloc(sizeof(Equipe)));
    if ( M == NULL)
    {
        printf("Erreur d'alloquation. \n");
        exit(EXIT_FAILURE);
    }
    return M;
}

//-------------------------------------
void libererB(Equipe **ancien) // Liberation d'Žquipe
{
    free(*ancien) ;
    *ancien = NULL;
}

//-------------------------------------
void affName(Equipe *m, char name[20]) // Affectation d'un nom ˆ une equipe.
{
    strcpy(m -> nom , name);
}

//-------------------------------------
void affAdrDB(Equipe *m, Equipe *n) // Affectation d'adresse ˆ droite.
{
    m -> next = n;
}

//-------------------------------------
void affAdrGB(Equipe *m, Equipe *n) // Affectation d'adresse ˆ gauche.
{
    m -> prev = n;
}

//-------------------------------------
Equipe* suivantB(Equipe* T ) // Rend un pointeur vers l'equipe suivante
{
    return(T->next);
}

//-------------------------------------
void supprimeB(Equipe **m , int* nb_chain) // Supprime (Libere) une equipe de la liste.
{
    Equipe *p;
    if ((*m) -> prev != NULL)
    {
        p = ((*m) -> prev);
        p -> next = ((*m)->next);
        *nb_chain +=1;
    }
    if ((*m) -> next != NULL)
    {
        p = ((*m) -> next);
        p -> prev = ((*m) -> prev);
        *nb_chain +=1;
    }
    free (*m);
    *m = NULL;
}



//--------------------------/* Controle de Structure "Poule" (grande liste) */--------------------------//
                              /* Poule = Structure de liste */
//-------------------------------------
Poule* allouer() // Alloquation de Poule.
{
    Poule *M = ((Poule*)malloc(sizeof(Poule)));
    if ( M == NULL)
    {
        printf("Erreur d'alloquation. \n");
        exit(EXIT_FAILURE);
    }
    return M;
}

//-------------------------------------
void aff_adr(Poule *p , Poule *q) // Affectation d'adresse au Poule.
{
    p -> next = q ;
}

//-------------------------------------
void aff_tete(Poule *p , Equipe *Eq) // Affecte l'equipe "Eq" ˆ la tete de "p".
{
    p -> tete = Eq;
}

//-------------------------------------
void aff_queue(Poule *p , Equipe *Eq) // Affecte l'equipe "Eq" ˆ la queue de "p".
{
    p -> queue = Eq;
}

//-------------------------------------
void supprime(Poule **m ,Poule ** prev , int *nb_chain) // Supprime (Libere) le Poule "m" de la liste.
{
    if ((*prev)!= NULL)
    {
        (*prev) -> next = ((*m) -> next);
        *nb_chain+=1;
    }
    free(*m);
    *m = NULL;
}

//-------------------------------------
Poule* suivant(Poule *p) // Rend un pointeur vers l'equipe suivante
{
    return(p -> next);
}


//--------------------------/* Fonction de Creation/ Initialisation */--------------------------//
//-------------------------------------
void creationEquipe( Equipe **T, int numpoule , int * nb_eq_allou, char* namae)  //nb_eq_allou = nombre de pointeur aquipe allouer , nb_comp = nombre de comparaisons  effectuées   , nb_chain = nombre de chainage effetuer
// Alloue une equipe ,lui affecte un nom et initialise le reste ˆ 0.
// @param numpoule : le numero de la poule ˆ laquelle appartient l'equipe T
{
    *T = allouerB(); // ------------------------ ********** Alloquation equipe
    *nb_eq_allou+=1;
    affAdrGB(*T,NULL);
    affAdrDB(*T,NULL);
    affName(*T, namae);
    (*T) -> totEncais = 0;
    (*T) -> totMarq = 0;
    (*T) -> points = 0;
    (*T) -> numMatch = 0;
    (*T) -> numPoule = numpoule;
}

//-------------------------------------
void creationPoule( Equipe** tete ,Equipe** queue, int numeroPoule ,  int * nb_eq_allou , int *nb_chain, int *Step)
// Crée une poule (liste) identifiée par "numPoule" ˆ partir de 4 Žquipes crŽes dans ce module mŽme.
// Rend un pointeur vers la premiere et derniere equipe de la poule.
{
    Equipe* P = NULL;
    Equipe* Q = NULL;
    int i = 0;
    
    *tete = NULL;
    
    //====================== Lecture Automatique des noms.
    srand(time(NULL));
    char ligne[40];
    int randJump, jumper;
    //======================
    // File Call part
    char* fichier = "countries.txt";
    FILE *theNames = NULL;
    theNames =fopen(fichier, "r");
    //======================
    if (theNames == NULL)
    {
        printf("ERREUR DE LECTURE DU FICHIER DES NOMS (FICHIER ERRONE/ INTROUVABLE) \n");
    }
    else
    {
        for (int stp = 0; stp <= *Step + 3; stp++)
            fgets(ligne,35,theNames);
        for (i = 1; i <= 4; i++)
        {
            //======================
            randJump =(rand() % (6 - 3 +1)) + 3 ;
            *Step += randJump;
            for( jumper = 0; jumper <= randJump; jumper++)
            {
                fgets(ligne,35,theNames);
            }
            ligne[strlen(ligne) - 1] = '\0';
            creationEquipe(&P,numeroPoule,nb_eq_allou, ligne);
            if (*tete == NULL) // Generation de la tete.
            {
                *tete = P;
            }
            else
            {
                affAdrDB(Q,P);               // ------------------------ ********** Chainage equipe
                affAdrGB(P,Q);              // ------------------------ ********** Chainage equipe
                *nb_chain+=2;
            }
            Q = P;
        }
        *queue = P;           // Generation de la queue.
    }
    fclose(theNames);
}

//-------------------------------------
void creationTournoi( Poule** tournois, int nbPoule, int * nb_eq_allou , int* nb_chain , int *nb_poul_allou)
// Genere la structure totale du Tournoi : un nombre "nbPoule" de poules crŽes dans ce module mŽme et reliŽes par la structure "Poule".
{
    Poule *p = NULL;
    Poule *q = NULL;
    Equipe *head = NULL;
    Equipe *tail = NULL;
    int k, step = 0;
    *tournois = NULL;
    
    for(k = 1; k <= nbPoule; k++)
    {
        p = allouer();
        *nb_poul_allou+=1;
        aff_adr(p, NULL);
        creationPoule(&head, &tail, k , nb_eq_allou , nb_chain, &step);
        aff_tete(p, head);
        aff_queue(p, tail);
        
        if (*tournois== NULL) // Generation de la tete.
        {
            *tournois = p;
        }
        else
        {
            aff_adr(q, p);
            *nb_chain+=1;
        }
        q = p;                // Generation de la queue.
    }
}


//--------------------------/* Fonction de Simulation */--------------------------//

// 1-------------------------------------
void simulMatch( Equipe *team1, Equipe *team2, Resultats tab[],int cptr ,char* phase)
//Simule un match dont les scores sont aleatoires, + sauvegarde des donnŽes pour l'affichge uniquement
//@param cptr : pour varier legerement les chances du cas de forfait. (plus on avance dans le tournoi, moins on a de chance de tomber sur un forfait.
{
    int score1 = 0, score2 = 0, diff = 0;

    int Forfait = rand()%(48 + cptr);  // Cas tres rare d'un forfait
    if (Forfait == 0)
    {
        team1 -> points += 2;
        char note[30] = "Forfait de l'equipe : ";
        strcat(note, team2-> nom);
        strcpy(tab[cptr].Note, note);
    }
    else
    {
        score1 = rand()%(120-30) + 30;
        score2 = rand()%(120-30) + 30;
        diff = score1 - score2;

        while (diff == 0) //Pour le cas d'égalité /Prolongations
        {
            score1 += (rand()%(15)) ;
            score2 += (rand()%(15)) ;
            diff = score1 - score2;
        }

        // Mise ˆ jour des donnŽes d'equipes
        team1 -> totMarq = (team1 -> totMarq) + score1;
        team1 -> totEncais = (team1 -> totEncais) + score2;
        team2 -> totMarq = (team2 -> totMarq) + score2;
        team2 -> totEncais = (team2 -> totEncais) + score1;



        diff = (abs(diff) / diff); // Formule pour le switch
        switch(diff) // Affectation des points
        {
            case (1) : // team1 wins
                team1 -> points += 2;
                team2 -> points += 1;
                break;
            case  (-1) :  //team2 wins
                team1 -> points += 1;
                team2 -> points += 2;
                break;
        }
    }



    //Sauvegarde dans le tableau des resultats.
    strcpy(tab[cptr].phase , phase);
    strcpy(tab[cptr].equipe1, team1->nom);
    strcpy(tab[cptr].equipe2, team2->nom);
    tab[cptr].resu1 = score1;
    tab[cptr].resu2 = score2;

}

// 2-------------------------------------
int simulMatch_post_poule( Equipe **team1, Equipe **team2,int num_match , Resultats tab[],int cptr , char phase [30] , int*nb_chain)
// Simule un match hors poule (presque identique au module precedent, ˆ la difference que celui-ci gere les suppression en cas de defaite
//@param cptr : indice du tableau des resulats
{
    int score1, score2, diff, winner = 0 ;
    
    //generation des resultats.
    score1 = rand()%(120-30) + 30;
    score2 = rand()%(120-30) + 30;
    diff = score1 - score2;
    
    while (diff == 0) //Pour le cas d'égalité /Prolongations
    {
        score1 += (rand()%(15)) ;
        score2 += (rand()%(15)) ;
        diff = score1 - score2;
    }
    
    // Mise ˆ jour des donnŽes d'equipes
    (*team1) -> totMarq = (*team1) -> totMarq + score1;
    (*team1) -> totEncais = (*team1) -> totEncais + score2;
    (*team2) -> totMarq = (*team2) -> totMarq + score2;
    (*team2) -> totEncais = (*team2) -> totEncais + score1;
    
    
    //Sauvegarde
    strcpy(tab[cptr].phase , phase);
    strcpy(tab[cptr].equipe1, (*team1)->nom);
    strcpy(tab[cptr].equipe2, (*team2)->nom);
    tab[cptr].resu1 = score1;
    tab[cptr].resu2 = score2;
    
    
    diff = (abs(diff) / diff); // Odd formula for the upcoming switch
    switch(diff) // Affectation des points
    {
        case (1) : // team1 wins
            (*team1)->numMatch = num_match;
            supprimeB(team2,nb_chain);
            winner = 1;
            break;
        case  (-1) :  //team2 wins
            (*team2)->numMatch = num_match;
            supprimeB(team1 , nb_chain);
            winner = 2;
            break;
    }
    
    return winner;
}

//--------------------------/* Fonction de Deroulement */--------------------------//

// 1-------------------------------------
void organisation_tournois(Poule* tete_tournois ,int *nb_chain)
//assure l'organisation du tournois en poule de 4 element chacune apres la phase eliminatoire
{
    Poule*p;
    Poule*old;
    Poule*q;
    Equipe*head1;
    Equipe*tail1;
    Equipe*head2;
    Equipe*tail2;
    p=tete_tournois;
    
    if (p->next == NULL) //le tournois contient qu'une seule poule
    {
        return ;
    }
    else
    {
        q=suivant(p);
        if (q->next == NULL)//la tournois contient que de deux poule
        {
            head1=(p->tete) ;
            tail1=(p->queue);
            head2=q->tete;
            tail2=q->queue;
            fusion_post_poul( &head1, &tail1 , &head2,&tail2,nb_chain);
            p->tete=head1;
            p->queue=tail1;
            supprime(&q,&p,nb_chain);
        }
        else
        {
            while(q->next != NULL) //la boucle se repete jusqu'a ce qu'on arive a l'avant derniere iteration
            {
                head1=allouerB(); //les allocation c'est pour pouvoir les reeutiliser
                head2=allouerB();
                head1=(p->tete) ;
                tail1=(p->queue);
                head2=q->tete;
                tail2=q->queue;
                fusion_post_poul( &head1, &tail1 , &head2,&tail2,nb_chain);
                p->tete=head1;
                p->queue=tail1;
                old=q->next;
                supprime(&q,&p,nb_chain);
                q=allouer();
                p=old;
                q=suivant(p);
            }//identique au cas if (q->next == NULL)
            head1=allouerB();
            head2=allouerB();
            head1=(p->tete) ;
            tail1=(p->queue);
            head2=q->tete;
            tail2=q->queue;
            fusion_post_poul( &head1, &tail1 , &head2,&tail2,nb_chain);
            p->tete=head1;
            p->queue=tail1;
            supprime(&q,&p,nb_chain);
        }
    }
}

// 2-------------------------------------
void deroulement_poule(Equipe* tete , Equipe* queue , Resultats tab[] , int *nb_match, int *numPoule)
// Simule une phase de Poule (Les 6 match de la phase)
// @param nb_match = nombre de match jouŽ jusqu'a present, sert en tant qu'indice du tableau des resulats
{

    // Pour l'enregistrement de la phase.
    char phase [10] = "Poule ";
    char number[3];
    sprintf(number, "%d", *numPoule);
    strcat(phase, number);
    *numPoule += 1;
    
    //simulation des 6 matchs de poule
    Equipe* suiv_tete = suivantB(tete);
    *nb_match+=1;
    simulMatch(tete , suiv_tete , tab , *nb_match ,phase);

    Equipe* prev_queue = queue -> prev;
    *nb_match+=1;
    simulMatch(prev_queue , queue , tab , *nb_match,phase);

    *nb_match+=1;
    simulMatch(tete , queue , tab , *nb_match,phase);


    *nb_match+=1;
    simulMatch(suiv_tete , prev_queue , tab , *nb_match,phase);


    *nb_match+=1;
    simulMatch(tete , prev_queue , tab , *nb_match,phase);


    *nb_match+=1;
    simulMatch(suiv_tete , queue , tab , *nb_match,phase);
}

//3 -------------------------------------
void classement(Equipe **tete, Equipe **queue , int* nb_comp ,int*nb_chain)
// Realise le classement (tri) d'une seule poule.
{
    Equipe *p = NULL;
    Equipe *q = NULL;
    Equipe *precedent;

    p = *tete;
    q = suivantB(*tete);

    while (q != NULL)
    {
        if ((p -> points) < (q -> points))
        {
            *nb_comp  = *nb_comp + 1; //*nb_comp---------------------------------------------------------------
            if ((p -> prev) == NULL) //Cas ou p = tete
            {
                permutEq(tete, queue, p, q ,nb_chain);
                p =* tete;
                q= ((*tete) ->next);
                nb_comp+=1;
            }

            else //Cas General
            {
                precedent= (p->prev); //pour revenir une case en arriere
                permutEq(tete,queue,p,q ,nb_chain);
                p=precedent;
                q=precedent->next;

            }
        }

        else if ((p->points) == (q->points))
        {
            (*nb_comp)+=1;
            if ((p->totMarq) < (q->totMarq))
            {
                *nb_comp+=1;
                if ((p->prev) == NULL) //cas ou p = tete
                {
                    permutEq(tete,queue,p,q ,nb_chain);
                    p=*tete;
                    q= ((*tete)->next);
                }
                else //cas general
                {
                    precedent= (p->prev); //pour revenir une case en arriere
                    permutEq(tete,queue,p,q ,nb_chain);
                    p=precedent;
                    q=precedent->next;
                }
            }

            else if ((p->totMarq) == (q->totMarq))
            {
                (*nb_comp)+=1;
                if ((p->totEncais) > (q->totEncais))
                {
                    *nb_comp+=1;
                    if ((p->prev) == NULL) //cas ou p = tete
                    {
                        permutEq(tete,queue,p,q ,nb_chain);
                        p=*tete;
                        q= ((*tete)->next);
                    }
                    else //cas general
                    {
                        precedent= (p->prev); //pour revenir une case en arriere
                        permutEq(tete,queue,p,q ,nb_chain);
                        p=precedent;
                        q=precedent->next;
                    }
                }

                else if ((p->totEncais) == (q->totEncais))
                {
                    (*nb_comp)+=1;
                    printf("match mabyou3 ;), refaite le matche :3");
                    break;
                }

                else //(p->totEncais) > (q->totEncais)
                {
                    p=q;
                    q=suivantB(q);
                }
            }

            else //cas (p->totMarq) > (q->totMarq)
            {
                p=q;
                q = suivantB(q);
            }
        }

        else //cas ((p->points) > (q->points))
        {
            p=q;
            q=suivantB(q);
        }
    }
}

// 4-------------------------------------
void deroulement_post_poule(Equipe** tete , Equipe** queue , Resultats tab[] , int* nb_match , int *match_tournois , int* nb_eq_allou ,int*nb_chain)
//deroulement des matchs dans une poule apres la phase eliminatoire
{
    Equipe*p = (*tete)->next;
    Equipe*q = (*queue)->prev;
    int condi1=0 , condi2=0;
    char phase [] ="Post-Poule";
    
    *nb_match=(*nb_match) +1;
    *match_tournois=(*match_tournois) +1;
    condi1=simulMatch_post_poule( tete, queue, *match_tournois ,  tab,*nb_match ,phase,nb_chain); //le 1er de la 1ere pouleavec le 2eme de la 2eme poul
    
    *nb_match=(*nb_match) +1;
    *match_tournois=(*match_tournois) +1;
    condi2 =simulMatch_post_poule(  &p, &q, *match_tournois ,  tab,*nb_match,phase ,nb_chain);//le 1er de la 2eme pouleavec le 2eme de la 1ere poul
    
    //rŽinitialisation de la tete et la queue
    if ((condi2 == 1) && (condi1 == 1))//
    {
        *queue = allouerB();
        *nb_eq_allou+=1;
        *queue = p;
    }
    if ((condi2 == 2) && (condi1 == 1))//
    {
        *queue = allouerB();
        *nb_eq_allou+=1;
        *queue = q;
    }
    if ((condi2 == 1) && (condi1 == 2))//
    {
        *tete = allouerB();
        *nb_eq_allou+=1;
        *tete = p;
    }
    if ((condi2 == 2) && (condi1 == 2))//
    {
        *tete = allouerB();
        *nb_eq_allou+=1;
        *tete = q;
    }
    
}

// 5-------------------------------------
void prem_to_tournois(Poule* tete_tournois  , int*nb_chain) //de preliminaire au tournois
{
    Poule*p;
    Poule*old;
    Poule*q;
    Equipe*head1;
    Equipe*tail1;
    Equipe*head2;
    Equipe*tail2;
    p=tete_tournois;

    if (p->next == NULL)
    {
        return ;
    }
    else
    {
        q=suivant(p);
        if (q->next == NULL)
        {
            head1=(p->tete) ;
            tail1=(p->queue);
            head2=q->tete;
            tail2=q->queue;
            fusion_poul( &head1, &tail1 , &head2,&tail2 ,nb_chain);
            p->tete=head1; //renouvlement de la tete et de la queue
            p->queue=tail1;
            supprime(&q,&p ,nb_chain);//supression des maillon de tournois qui ne seront plus utilisé
        }
        else
        {
            while(q->next != NULL) //la boucle se repete jusqu'a ce qu'on arive a l'avant derniere iteration
            {
                head1=allouerB(); //les allocation c'est pour pouvoir les reeutiliser
                head2=allouerB();
                head1=(p->tete) ;
                tail1=(p->queue);
                head2=q->tete;
                tail2=q->queue;
                fusion_poul( &head1, &tail1 , &head2,&tail2,nb_chain);
                p->tete=head1;
                p->queue=tail1;
                old=suivant(q);
                supprime(&q,&p ,nb_chain);
                q=allouer();
                p=old;
                q=suivant(p);
            }//identique au cas if (q->next == NULL)
            
            head1=allouerB();
            head2=allouerB();
            head1=(p->tete) ;
            tail1=(p->queue);
            head2=q->tete;
            tail2=q->queue;
            fusion_poul( &head1, &tail1 , &head2,&tail2,nb_chain);
            p->tete=head1;
            p->queue=tail1;
            supprime(&q,&p,nb_chain);
        }
    }
}




// 6-------------------------------------
void deroulement_tournois(Equipe** tete , Equipe** queue , int np ,Resultats tab[] , int* nb_match , int *match_tournois , int*nb_eq_allou , int*nb_chain)
//ce module assure le deroulement des matches dans les poule en utilsant la rŽgle d'organiser les affrontements en nombre pair et impair.
{
    Equipe*p = (*tete)->next;
    Equipe*q = (*queue)->prev;
    Equipe* suiv_pair , *suiv_impair ,*winner1 = NULL;
    int memory_match1 , memory_match2;
    char *phase;
    int condi1=0 , condi2=0 ,condi3=0 ;
    switch (np)
    {
        case 1:
            phase="Demi-Finale";
            break;
        case 2:
            phase="Cart de Finale";
            break;
        case 4:
            phase="Huitieme de Finale";
            break;
        default:
            phase="tournois";
            break;
    }
    
    
    if (pair((*tete)->numMatch)==1) //cas la tete a un num de match paire
    {
        /***** le premier matche *****/
        suiv_pair=p;
        while (pair(suiv_pair->numMatch) != 1) //recherche d'une equipe paire
        {
            suiv_pair=suivantB(suiv_pair);
        }
        
        
        *nb_match=(*nb_match) +1;    //incrementation des indice du tableau des resultas
        *match_tournois=(*match_tournois) +1;
        
        
        memory_match1 =(*tete)->numMatch;     //sauvegarde des resultas pour que les match se deroul sans modification des numero de match
        memory_match2 = suiv_pair->numMatch;
        
        if (suiv_pair == *queue) condi1=1; //pour savoir si suiv_pair est la queue ou pas
        
        condi2=simulMatch_post_poule( tete, &suiv_pair,*match_tournois,  tab,*nb_match,phase,nb_chain);
        
        //reinitialisation de la tete et de la queue
        if (condi2 == 2) //le cas ou la tete a ete suprimer
        {
            *tete = allouerB();
            *nb_eq_allou+=1;
            *tete = p;//p est le suivant de tete
            winner1=suiv_pair;
            winner1->numMatch = memory_match2;
        }
        if(condi2==1)
        {
            if (condi1==1) //le cas ou suiv_pair est la queue et il a ete suprimer
            {
                *queue = allouerB();
                *nb_eq_allou+=1;
                *queue = q;
            }
            winner1=*tete;
            winner1->numMatch = memory_match1;
        }
        
        
        
        /***** le deuxieme matche *****/
        condi1=0;
        condi2=0;
        q = (*queue)->prev;//en cas de supression de la queue ca nous servira de remplacement
        p=*tete;
        
        // recherche des equipes
        while (pair(p->numMatch) != 0) //recherche d'une equipe qui a un matche impair
        {
            p= suivantB(p);
        }
        
        suiv_impair= suivantB(p);
        while (pair(suiv_impair->numMatch) != 0) //recherche d'une equipe qui a un matche impair
        {
            suiv_impair= suivantB(suiv_impair);
        }
        
        
        
        *nb_match=(*nb_match) +1; //incrementation des indice du tableau des resultas
        *match_tournois=(*match_tournois) +1;
        
        if(p==*tete) condi1=1; //pour savoir si p est la tete ou pas
        if (suiv_impair == *queue) condi2=1;  //pour savoir si suiv_impair est la queue ou pas
        condi3=simulMatch_post_poule( &p, &suiv_impair,*match_tournois,  tab,*nb_match,phase,nb_chain);
        
        //reinitialisation de la tete et de la queue
        if ((condi1==1) && (condi3==2)) //le cas ou la tete a ete suprimer
        {
            *tete = allouerB();
            *nb_eq_allou+=1;
            *tete = q;
        }
        if((condi2==1) && (condi3==1)) //le cas ou suiv_impair est la queue et il a ete suprimer
        {
            *queue = allouerB();
            *nb_eq_allou+=1;
            *queue = q;
        }
        
        
        
        winner1->numMatch=(*match_tournois)-1;
        
    }
    else  //cas la tete a un num de match impaire
    {
        suiv_impair=p;
        while (pair(suiv_impair->numMatch) != 0) //recherche d'une equipe qui a un matche impair
        {
            suiv_impair=suivantB(suiv_impair);
        }
        
        *nb_match=(*nb_match) +1;    //incrementation des indice du tableau des resultas
        *match_tournois=(*match_tournois) +1;
        
        
        memory_match1 =(*tete)->numMatch;
        memory_match2 = suiv_impair->numMatch;
        
        if (suiv_impair == *queue) condi1=1;
        condi2=simulMatch_post_poule( tete, &suiv_impair,*match_tournois,  tab,*nb_match,phase,nb_chain);
        
        //reinitialisation de la tete et de la queue
        if (condi2==2) //le cas ou la tete a ete suprimer
        {
            *tete = allouerB();
            *nb_eq_allou+=1;
            *tete = p;
            winner1=suiv_impair;
            winner1->numMatch = memory_match2;
        }
        if(condi2==1)
        {
            if (condi1==1) //le cas ou suiv_impair est la queue et il a ete suprimer
            {
                *queue = allouerB();
                *nb_eq_allou+=1;
                *queue = q;
            }
            winner1=*tete;
            winner1->numMatch = memory_match1;
        }
        
        
        
        condi1=0;
        condi2=0;
        q = (*queue)->prev;
        p=*tete;
        while (pair(p->numMatch) != 1) //recherche d'une equipe qui a un matche pair
        {
            p=suivantB(p);
        }
        
        
        suiv_pair= suivantB(p);
        while (pair(suiv_pair->numMatch) != 1) //recherche d'une equipe qui a un matche pair
        {
            suiv_pair=suivantB(suiv_pair);
        }
        
        *nb_match=(*nb_match) +1; //incrementation des indice du tableau des resultas
        *match_tournois=(*match_tournois) +1;
        
        if(p==*tete) condi1=1;
        if (suiv_pair == *queue) condi2=1;
        condi3=simulMatch_post_poule( &p, &suiv_pair,*match_tournois,  tab,*nb_match,phase ,nb_chain);
        
        //reinitialisation de la tete et de la queue
        if ((condi1==1) && (condi3==2)) //le cas ou p estla  tete et il a ete suprimer
        {
            *tete = allouerB();
            *nb_eq_allou+=1;
            *tete = q;
        }
        if((condi2==1) && (condi3==1)) //le cas ou suiv_pair est la queue et il a ete suprimer
        {
            *queue = allouerB();
            *nb_eq_allou+=1;
            *queue = q;
        }
        winner1->numMatch=(*match_tournois)-1;
        
    }
}

//--------------------------/* Fonctions de Traitement */--------------------------//

//1 -------------------------------------
void permutEq(Equipe**tete ,Equipe**queue, Equipe *eq1, Equipe *eq2 ,  int *nb_chain)
// permute deux equipes (AKA rechainage)
{
    // Sauvegarde
    Equipe *next1, *prev1 ,*next2 ;
    int cpt=0;//l'indicateur de permutation
    next1 = eq1->next; //suivant de eq1
    prev1 = eq1->prev; //precedent de eq1
    next2 = eq2->next; //le suivant de eq2
    
    
    //modification de la tete et/ou de la queue
    if ((eq1->prev)==NULL) // Cas eq1 est la tete
    {
        *tete=eq2;
        cpt=1;
    }
    if ((eq2->next)==NULL) // Cas eq2 est la queue
    {
        *queue=eq1;
        cpt+=2;
    }
    
    // Permutation
    switch (cpt)
    {
        case 0: //cas simple
            if ((eq1->next) == eq2) //le cas ou ils se suivent
            {
                affAdrDB(prev1 ,eq2);//le suivant du precedent de eq1
                affAdrGB(next2 ,eq1);//le precedent du suivant de eq2
                affAdrDB(eq1 , (eq2->next));
                affAdrGB(eq1 , eq2 );
                affAdrDB(eq2 , eq1 );
                affAdrGB(eq2 ,prev1);
            }
            else
            {
                affAdrDB(prev1 ,eq2);//prev1->next = eq2; //le suivant du precedent de eq1
                affAdrGB(next2 ,eq1);//next2->prev = eq1; //le precedent du suivant de eq2
                affAdrDB(eq1 , (eq2->next));//eq1->next = eq2->next;
                affAdrGB(eq1 , eq2->prev );//eq1->prev = eq2->prev;
                affAdrDB(eq2 , next1 ); //eq2->next = eq1;
                affAdrGB(eq2 ,prev1); //eq2->prev = prev1;
            }
            *nb_chain+=6;
            break;
            
        case 1: //cas eq1 est la tete
            if ((eq1->next) == eq2) //le cas ou il se suive
            {
                affAdrGB(next2 ,eq1);//next2->prev = eq1; //le precedent du suivant de eq2
                affAdrDB(eq1 , (eq2->next)); //eq1->next = eq2->next;
                affAdrGB(eq1 , eq2 ); //eq1->prev = eq2;
                affAdrDB(eq2 , eq1 ); //eq2->next = eq1;
                affAdrGB(eq2 ,prev1); //eq2->prev = prev1;
            }
            else //le cas ou ils sont separé
            {
                
                affAdrGB(next2 ,eq1);//next2->prev = eq1; //le precedent du suivant de eq2
                affAdrDB(eq1 , (eq2->next));//eq1->next = eq2->next;
                affAdrGB(eq1 , eq2->prev );//eq1->prev = eq2->prev;
                affAdrDB(eq2 , next1 ); //eq2->next = eq1;
                affAdrGB(eq2 ,prev1); //eq2->prev = prev1;
            }
            *nb_chain+=5;
            break;
            
        case 2: //cas eq2 est la queue
            if ((eq1->next) == eq2) //le cas ou il se suive
            {
                affAdrDB(prev1 ,eq2);//prev1->next = eq2; //le suivant du precedent de eq1
                affAdrDB(eq1 , (eq2->next)); //eq1->next = eq2->next;
                affAdrGB(eq1 , eq2 ); //eq1->prev = eq2;
                affAdrDB(eq2 , eq1 ); //eq2->next = eq1;
                affAdrGB(eq2 ,prev1); //eq2->prev = prev1;
            }
            else //le cas ou ils sont separé
            {
                affAdrDB(prev1 ,eq2);//prev1->next = eq2; //le suivant du precedent de eq1
                affAdrDB(eq1 , (eq2->next));//eq1->next = eq2->next;
                affAdrGB(eq1 , eq2->prev );//eq1->prev = eq2->prev;
                affAdrDB(eq2 , next1 ); //eq2->next = eq1;
                affAdrGB(eq2 ,prev1); //eq2->prev = prev1;;
            }
            *nb_chain+=5;
            break;
            
        case 3://cas eq1 est la tete et eq2 est la queue
            if ((eq1->next) == eq2) //le cas ou il se suive
            {
                affAdrDB(eq1 , (eq2->next)); //eq1->next = eq2->next;
                affAdrGB(eq1 , eq2 ); //eq1->prev = eq2;
                affAdrDB(eq2 , eq1 ); //eq2->next = eq1;
                affAdrGB(eq2 ,prev1); //eq2->prev = prev1;
            }
            else //le cas ou ils sont separé
            {
                affAdrDB(eq1 , (eq2->next));//eq1->next = eq2->next;
                affAdrGB(eq1 , eq2->prev );//eq1->prev = eq2->prev;
                affAdrDB(eq2 , next1 ); //eq2->next = eq1;
                affAdrGB(eq2 ,prev1); //eq2->prev = prev1;;
            }
            *nb_chain+=4;
            break;
    }
}

//2 -------------------------------------
void fusion_poul( Equipe**tete1,Equipe** queue1 , Equipe**tete2 ,Equipe** queue2 , int*nb_chain)
// Fusionne deux poule (apres la phase de poule, pour preparer ˆ la phase suivante)
{
    Equipe*p;
    Equipe*q1;
    Equipe*q2;
    Equipe*q3;
    
    // chainage
    q1=*queue1;
    *queue1=(*tete2)->next;
    affAdrDB(*queue1 , NULL);
    p=(*tete1)->next;
    affAdrDB(p,*tete2);
    affAdrGB(*tete2 ,p);
    (*tete2)=NULL;
    nb_chain+=3;
    
    /* liberation */
    q2=q1->prev;
    libererB(&q2);
    libererB(&q1);
    q3=(*queue2)->prev;
    libererB(&q3);
    libererB(queue2);
    libererB(tete2);
    
    
}

// 3-------------------------------------
void fusion_post_poul(Equipe**tete1,Equipe** queue1 , Equipe**tete2 ,Equipe** queue2 ,int*nb_chain)
//fusionne les pseudo-poules apres la phase eliminatoire
{
    //chainage
    affAdrDB(*queue1,*tete2);
    affAdrGB(*tete2,*queue1);
    *nb_chain+=2;
    *queue1=*queue2;
    //liberation
    *queue2=NULL;
    free(*queue2);
    *tete2=NULL;
    free(*tete2);
}
int pair(int chifre)   //renvois 1 si chifre est pair et 0 si il est impair
{
    if (chifre% 2 == 0) return 1;
    else return 0;
}

int nombreMatch (int np) // Calculer le nombre total de matchs qui auront lieu --- np = Nombre de Poules
{
    int nb;
    nb = np * 6;  //Phase de poule
    while  (np != 0)
    {
        nb += np;
        np /= 2;
    }
    return nb;
}

