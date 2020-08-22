
#include "DataFuncs.h"
#include <term.h>



int main()
{
    char play = 'o';
    while (play == 'o')
    {
    system("clear");
    int choice = 0;
    printf("Veuillez choisir un mode : \n");
    printf("Mode 1 : Simulation de Tournoi. \n");
    printf("Mode 2 : Lecture de Resultats de Tournoi. \nMode ");
    scanf("%d", &choice);
    
    
    switch (choice)
    {
        case 1 :
        {
            Poule* tournment;
            Poule* pool;
            Equipe* head ;
            Equipe* tail;
            char *phase;
            Resultats *matches; //les resultas des matche
            int nombre_poul;
            int nombre_matche=0 ,i ;
            int matche_tournois=0 , winner;
            int nb_mai_allou = 0 , nb_chain = 0 , nb_comp = 0 ;
            EquipePoule TabEquipes[80];
            int cptTabEq = 0, numeroPoule = 1;
            //nombre maillon aloués  ,  nombre de chainage  , nombre de comparaison
            
            /* fin de la declaration des variables */
            
            
            /*****   introduction  nombre de poule  et creation du tournoi  ******/
            
            printf("Veuillez introduire le nombre de poules dans le tournoi (imperativement une puissance de 2) : ");
            scanf("%d", &nombre_poul);
            int nbpoulesave = nombre_poul;
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
                deroulement_poule(head,tail ,matches,&nombre_matche, &numeroPoule);
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
                Equipe *headTab = head;
                for (int j = 1; j <= 4; j++)
                {
                    strcpy(TabEquipes[cptTabEq].nom, headTab -> nom);
                    TabEquipes[cptTabEq].numPoule = headTab -> numPoule;
                    TabEquipes[cptTabEq].points = headTab->points;
                    TabEquipes[cptTabEq].totMarq = headTab->totMarq;
                    TabEquipes[cptTabEq].totEncais = headTab->totEncais;
                    headTab = headTab->next;
                    cptTabEq ++;
                }
                int saver = nb_comp; //pour eviter une anomalie qui fait que nb_comp perde sa valeur
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
            
            if (winner==1) printf("L'equipe gagnante du tournoi est l'equipe :  %s \n",head->nom);
            else printf("l'equipe gagnante du tournoi est l'equipe :  %s \n",tail->nom);
            
            char details;
            printf("\n \n");
            printf("Voullez-Vous afficher les resultats des matchs ? (o/n) --->  ");
            scanf("%s", &details);
            getchar();
            if (details == 'o')
            {
                printf("\n");
                for( i = 1; i <= nombre_matche; i++)
                     printf("%s : %s %s %d-%d \n",matches[i].phase, matches[i].equipe1, matches[i].equipe2, matches[i].resu1 ,matches[i].resu2);
                
            }
            
            printf("Voullez-Vous afficher les resultats des Poules ? (o/n) --->  ");
            scanf("%s", &details);
            getchar();
            if (details == 'o')
            {
                printf("\n");
                for( i = 0; i < cptTabEq; i++)
                   printf("%s - Poule No = %d - %d points de poule - credit de %d buts de poule \n", TabEquipes[i].nom, TabEquipes[i].numPoule,TabEquipes[i].points, TabEquipes[i].totMarq - TabEquipes[i].totEncais);
                
            }
            
             printf("\n \n");
            printf("Voullez-Vous afficher les details techniques ? (o/n) --->  ");
            scanf("%s", &details);
            getchar();
            if (details == 'o')
                {
                    printf("======================================= \n" );
                    printf("Le nombre de maillons alloues = %d \n",nb_mai_allou);
                    printf("Le nombre de chainages = %d \n",nb_chain);
                    printf("Le nombre de comparaisons = %d \n",nb_comp);
                    printf("La taille en octet d'une liste ""Poule"" = %lu \n",4 * sizeof(Equipe));
                    printf("La taille en octet de la liste totale (Liste Tournoi) = %lu \n",nbpoulesave*  4 * sizeof(Equipe));
                    printf("======================================= \n" );
                    
                }
            break;
        }
        case 2 :
        {
            char ligne[MAX_LENGTH];
            int cptTabRes = 0;
            Resultats tabResRead[MAX_MATCH];
            Team_Data *DataHead = NULL ;
            DataHead= initialisation();
            
            //======================
            // File Call part
            char fichier[15];
            printf("Veuillez introduire le chemin du fichier a lire. \n");
            printf("Le chemin du fichier a lire : --> ");
            scanf("%s",fichier);
            FILE *theResults = NULL;
            theResults =fopen(fichier, "r");
            //======================
            
            //======================
            if (theResults != NULL) // Lecture du fichier et prise de donnŽes
            {
                while (fgets(ligne,MAX_LENGTH,theResults) != NULL) //Extraction des Mots. +++ // Affichage du texte en entier.
                {
                    cptTabRes++;
                    readLine(ligne, tabResRead, cptTabRes);
                    
                }
                fclose(theResults);
            }
            else
            {
                printf("ERREUR DE LECTURE DU FICHIER (FICHIER ERRONE) \n");
            }
            control(tabResRead, cptTabRes, DataHead);
        //    printData(DataHead);
            //======================
            break;
        }
    }
        printf("\n \n");
        printf("Appuyez sur ""o"" pour revenir au menu principal \n");
        printf("Appuyez sur n'importe quelle autre touche pour quitter \n ----> Votre choix:  ");
        scanf("%s", &play);
        getchar();
        printf("\n \n");
    }
   

return 0;

}







