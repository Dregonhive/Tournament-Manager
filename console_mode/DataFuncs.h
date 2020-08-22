//
//  Data Funcs.h
//  TP-file
//
//  Created by Meave on 04/04/2017.
//  Copyright © 2017 Dregon Corp. All rights reserved.
//

#ifndef Data_Funcs_h
#define Data_Funcs_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "func_tp.h"

#define MAX_LENGTH 200
#define MAX_MATCH 100
#define back printf("\n");

typedef struct Team_Data
{
    char nom[20];
    int poule;
    int  ptsPoule;
    int nbButsPoule; //Encaissés - Reçus.
    int  disqualif;  //1 si disqualifiée, 0 sinon.
    struct Team_Data* Suivant;
}Team_Data;

typedef struct List
{
    Team_Data *first;
} List;

/*typedef struct Resultats
{
    char equipe1[20];
    char equipe2[20];
    int  resu1;
    int  resu2;
    char phase[10];
    char winner[15];
    char loser[15];
    char Note [7];
}Resultats; */


int readLine( char line[150], Resultats Tab[], int cptTab);
Team_Data* initialisation(void);
int allouerData(Team_Data** M);
void affAdrData(Team_Data *m, Team_Data *n);
void affNameData(Team_Data *m, char name[20]);

Team_Data* creationData(int numpoule, char* nom);
Team_Data* rechData(Team_Data *head, char* nom);
Team_Data* previousData (Team_Data *P, Team_Data **Head);
void permutData(Team_Data **tete, Team_Data *Data1, Team_Data *Data2);
int printData(Team_Data* ListHead);


int TriPoule(Team_Data* listHead, int posInitiale) ;
void control(Resultats Tab[], int cptTab, Team_Data *Head);


#endif /* Data_Funcs_h */
