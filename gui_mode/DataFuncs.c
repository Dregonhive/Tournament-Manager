#include "DataFuncs.h"

//======================// Propre au fichier//======================//

//--------------------------
int readLine( char line[150], Resultats Tab[], int cptTab) //Lis une ligne du fichier de resultats, enregistre les données.
{
    long i = 0, j = 0;
    char *Resu1, *Resu2;
    
    //-------------
    while (line[i] != ':') // Lecture de la phase
    {
        Tab[cptTab].phase[j] = toupper(line[i]);
        j++;
        i++;
    }
    Tab[cptTab].phase[j] = '\0'; //Evite les erreurs
    i += 2; // Saut d'espace
    j = 0; //remise de la varabile de parcours à 0
    
    //-------------
    while (line[i] != ' ') // Lecture de la premiere equipe
    {
        Tab[cptTab].equipe1[j] = toupper(line[i]);
        j++;
        i++;
    }
    Tab[cptTab].equipe1[j] = '\0'; //Evite les erreurs
    i++; // Saut d'espace
    j = 0; //remise de la varabile de parcours à 0
    
    //-------------
    while (line[i] != ' ') // Lecture de la seconde equipe
    {
        Tab[cptTab].equipe2[j] = toupper(line[i]);
        j++;
        i++;
    }
    Tab[cptTab].equipe2[j] = '\0'; //Evite les erreurs
    i++; // Saut d'espace
    j = 0; //remise de la varabile de parcours à 0
    
    //-------------
    while (line[i] != '-') // Lecture du premier score
    {
        Resu1[j] = line[i];
        j++;
        i++;
    }
    Tab[cptTab].resu1 = atoi(Resu1);
    i++; // Saut du tiret
    j = 0; //remise de la varabile de parcours à 0
    
    //-------------
    while (line[i] != ' ') // Lecture du second score
    {
        Resu2[j] = line[i];
        j++;
        i++;
    }
    
    Tab[cptTab].resu2 = atoi(Resu2);
    
    //------------- Enregistrement du vainquer pour verifier les anomalies
    if (Tab[cptTab].resu1 > Tab[cptTab].resu2)
    {
        strcpy(Tab[cptTab].winner,Tab[cptTab].equipe1);
        strcpy(Tab[cptTab].loser,Tab[cptTab].equipe2);
    }
    else
    {
        strcpy(Tab[cptTab].winner,Tab[cptTab].equipe2);
        strcpy(Tab[cptTab].loser,Tab[cptTab].equipe1);
    }
    
    
    return 0;
}

//======================// Propre à la structure de maillon//======================//

//--------------------------
int allouerData(Team_Data **M)  // Alloquation d'équipe
{
    *M = ((Team_Data*)malloc(sizeof(Team_Data)));
    if ( M == NULL)
    {
        printf("Erreur d'alloquation. \n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

//--------------------------
void affAdrData(Team_Data *m, Team_Data *n) // Affectation d'adresse à droite.
{
    m -> Suivant = n;
}

//--------------------------
void affNameData(Team_Data *m, char name[20]) // Affectation d'un nom à une equipe.
{
    strcpy(m -> nom , name);
}

//--------------------------
Team_Data* initialisation(void) // Initialise une liste de Team_Data (equivaut à maillon).
{
    Team_Data *liste = malloc(sizeof(*liste));
    Team_Data *team = malloc(sizeof(*team));
    
    if (liste == NULL || team == NULL)
    {
        exit(EXIT_FAILURE);
    }
    team -> poule = 0;
    team -> ptsPoule = 0;
    team -> nbButsPoule = 0;
    team -> disqualif = 0;
    affAdrData(team, NULL);
    liste -> Suivant = team;
    
    return liste;
}

//--------------------------
Team_Data* creationData(int numpoule, char* nom)
// Alloue une struct. de données d'equipe ,lui affecte un nom et initialise le reste à 0.
// @param numpoule : le numero de la poule à laquelle appartient l'equipe du nom "nom".
{
    Team_Data *T;
    T = malloc(sizeof(*T));
    T -> poule = numpoule;
    affNameData(T, nom);
    T -> ptsPoule = 0;
    T -> nbButsPoule = 0;
    T -> disqualif = 0;
    affAdrData(T,NULL);
    return T;
}

//--------------------------
Team_Data* previousData (Team_Data *P, Team_Data **Head) // Rend un pointeur sur l'equipe precedente de P.
{
    Team_Data *Q = *Head;
    if (P == *Head)
    {
        // Pas de precedent
    }
    else
    {
        while (Q -> Suivant != P)
            Q = Q -> Suivant;
    }
    return Q;
}

//--------------------------
Team_Data* rechData(Team_Data *head, char* nom) // recherche le maillon de l'equipe du nom "nom".
{
    Team_Data *m;
    int cpt = 1 ;
    m = head ;
    while ( (m != NULL) && (strcmp(nom, m ->nom) != 0) )
    {
        m = m -> Suivant;
        cpt++ ;
    }
    return (m);
}

//--------------------------
void permutData(Team_Data **tete, Team_Data *Data1, Team_Data *Data2) // Permute deux Team_Data ADJACENTES.
{
    // Sauvegarde
    Team_Data *next2, *previous1;
    
    previous1 = previousData(Data1, tete); // Precedent de Data1
    next2 = Data2 -> Suivant; // Suivant de Data2
    
    // Modification eventuelle de la tete.
    if ( *tete == Data1 ) //Data1 est en tete
    {
        *tete = Data2;
        affAdrData(Data1, next2);
        affAdrData(Data2, Data1);
    }
    else
    {
        affAdrData(Data1, next2);
        affAdrData(Data2, Data1);
        affAdrData(previous1, Data2);
    }
}

//--------------------------
int printData(Team_Data* ListHead) //Affiche les données de toutes le equipes de la liste.
{
    Team_Data* P = ListHead;
    printf("             ----------- TEAMS DATA PRINTING -----------            \n");
    while (P != NULL)
    {
        printf("%s - Poule No = %d - %d points de poule - credit de %d buts de poule \n", P -> nom, P -> poule,             P -> ptsPoule, P -> nbButsPoule);
        P = P -> Suivant;
    }
    return 0;
}


//======================// Propre au deroulement du tournoi//======================//

//--------------------------
int TriPoule(Team_Data* listHead, int posInitiale)  // Realise le tri d'une poule en fonction des ptsPoule.
{
    int i = posInitiale, verif = 1, cpt = 0;
    Team_Data *R, *Pos = listHead, *Q = NULL, *SavePart2 = NULL;
    
    
    for(cpt = 0; cpt <= i ; cpt++)
    {
        Pos = Pos -> Suivant;
    }
    SavePart2 = ((((Pos -> Suivant) -> Suivant) -> Suivant)) -> Suivant; // Borne suivante de la coupe.
    affAdrData(previousData(SavePart2, &listHead), NULL); // Coupe momentanée pour scinder la partie à trier.
    
    while (verif == 1)
        // @verif : verifie s'il y'a eu permutation.
    {
        verif = 0;
        Q = Pos;
        R = Q -> Suivant;
        while (R != NULL)
        {
            if (Q -> ptsPoule > R -> ptsPoule)
            {
                permutData(&listHead, Q, R);
                verif = 1;
                
                break;
            }
            else // sinon on passe
            {
                R = R -> Suivant;
                Q = Q -> Suivant;
            }
        }
    }
    
    Pos = listHead; //Remise en place de la pos initialie apres le premier tri.
    for(cpt = 0; cpt <= i ; cpt++)
    {
        Pos = Pos -> Suivant;
    }
    Q = Pos;
    R = Q -> Suivant;
    while (R != NULL) // Cas d'égalité de ptsPoule, permutation en fonction de la difference Encaissés/ Marqués
    {
        if (Q -> ptsPoule == R -> ptsPoule)
        {
            if (R -> nbButsPoule < Q -> nbButsPoule)
            {
                permutData(&listHead, Q, R);
            }
        }
        Q = R;
        R = R -> Suivant;
    }
    
    affAdrData(Q, SavePart2); // Rechainage à l'initiale
    return 0;
}

//--------------------------
void control(Resultats Tab[], int cptTab, Team_Data *Head) //Control le tournoi en simulant les resultats
// @param cptTab = nombre de lignes (de cases) de resultats (AKA le nombre de matchs).
/*
 Anomalies possibles :
 - Equipes supposée être disqualifiée, rejoue un match ulterieur.
 - Au niveau du nombre d'equipes.
 - Au niveau du nombre de matchs.
 */
{
    Team_Data *P = Head, *Q = NULL, *R = NULL;
    int i = 0, j = 0, verif = 0, cptTeam = 0;
    // @var verif : verifie qu'une equipe n'a pas deja été introduite.
    // @var cptTeam : le nombre d'equipes existantes.
    //------------- Enregistrement des equipes
    char pl = 0;
    for (i = 1; i < cptTab; i++)
    {
        Q = P -> Suivant;
        R = Q -> Suivant;
        verif = 0;
        while (R != NULL)
        {
            if (strcmp(R -> nom, Tab[i].equipe1) == 0)
            {
                verif = 1;
            }
            Q = R;
            R = R -> Suivant;
        }
        if (verif == 0)
        {
            pl = Tab[i].phase[6];
            R = creationData(atoi(&pl), Tab[i].equipe1);
            affAdrData(Q, R);
            cptTeam++;
        }
        
        // Reinitialisation pour la seconde equipe.
        Q = P -> Suivant;
        R = Q -> Suivant;
        verif = 0;
        
        while (R != NULL)
        {
            if (strcmp(R -> nom, Tab[i].equipe2) == 0)
            {
                verif = 1;
            }
            Q = R;
            R = R -> Suivant;
        }
        if (verif == 0)
        {
            pl = Tab[i].phase[6];
            R =  creationData(atoi(&pl), Tab[i].equipe2);
            affAdrData(Q, R);
            cptTeam++;
        }
    }
    //-------------------------- Controle du nombre de matchs/ Equipes:
    if (cptTeam != ((cptTab + 1)/2)) // Formule du nombre d'equipes (nombre de matchs connus)
    {
        printf("Nombre d'equipes = %d \n", cptTeam);
        printf("Nombre de matchs = %d \n", cptTab);
        printf("ERREUR! ---> Les nombres ne correspondent pas.");
        exit(EXIT_FAILURE);
    }
    else
    {
        //-------------------------- Prise en compte des matchs
        Team_Data *inter;
        
        //----------------------------------------- Phase de poule.
        int lim = ((cptTeam * 6)/4); // nombre de matchs de poule.
        
        for (i = 1; i <= lim; i++)
        {
            inter = rechData(Head, Tab[i].winner);
            inter -> ptsPoule += 2;
            if (Tab[i].resu1 > Tab[i].resu2)
                inter -> nbButsPoule += Tab[i].resu1 - Tab[i].resu2;
            else
                inter -> nbButsPoule += Tab[i].resu2 - Tab[i].resu1;
            
            
            inter = rechData(Head, Tab[i].loser);
            inter -> ptsPoule += 1;
            if (Tab[i].resu1 < Tab[i].resu2)
                inter -> nbButsPoule += Tab[i].resu1 - Tab[i].resu2;
            else
                inter -> nbButsPoule += Tab[i].resu2 - Tab[i].resu1;
        }
        
        //------------------ Le Tri
        j = 1;
        
        while (j <= (cptTeam - 3))
        {
            TriPoule(Head, j);
            j += 4;
        }
        
        //------------------ Disqualifiquation
        Q = (Head -> Suivant) -> Suivant; //Car Head est une Tete indirecte.
        while (Q != NULL)
        {
            Q -> disqualif = 1;
            strcpy(Q -> phasediscalif, "Poule");
            (Q -> Suivant) -> disqualif= 1;
            strcpy((Q -> Suivant) -> phasediscalif, "Poule");
            Q = ((((Q -> Suivant) -> Suivant) -> Suivant) -> Suivant);
        }
        
        //----------------------------------------- Post-poule.
        Team_Data *interA, *interB;
        for (i = lim + 1; i <= cptTab; i++)
        {
            interA = rechData(Head,Tab[i].equipe1);
            interB = rechData(Head,Tab[i].equipe2);
            
            
            if (interA -> disqualif == 1)  // equipes disqualifiée participant ulterieurierement
            {
                printf("ERREUR! ---> 1 l'equipe %s participe invalidement au match N˚= %d au niveau de la Phase suivante: %s \n", interA -> nom, i, Tab[i].phase);
                exit(EXIT_FAILURE);
            }
            else
            {
                if (interB -> disqualif == 1)
                {
                    printf("ERREUR! ---> l'equipe %s participe invalidement au match N˚= %d au niveau de la Phase suivante: %s \n", interB -> nom, i, Tab[i].phase);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    inter = rechData(Head,Tab[i].loser);
                    inter -> disqualif = 1;
                }
            }
        }
        
        int u = 0;
        inter = (Head -> Suivant) -> Suivant; //Car Head est une Tete indirecte.
        while (u == 0) // Recherche de l'equipe Gagnante
        {
            if (inter -> disqualif == 0)
                u = 1;
            else
                inter = inter -> Suivant;
        }
        printf("Tournoi remporté par l'équipe : %s --- TOURNOI VALIDE. \n", inter -> nom);
    }
}
