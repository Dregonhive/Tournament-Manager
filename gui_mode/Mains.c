//
//  Mains.c
//  TP BASKET SDL
//
//  Created by Meave on 14/04/2017.
//  Copyright © 2017 Dregon Corp. All rights reserved.
//

#include "Mains.h"
#include "DataFuncs.h"



void mainLecture(void)
{
    const char *text ;
    char ligne[MAX_LENGTH];
    int cptTabRes = 0;
    Resultats tabResRead[MAX_MATCH];
    Team_Data *DataHead = NULL ;
    DataHead= initialisation();
    
    //======================
    // File Call part
    char* fichier = "Fichier.txt";
    FILE *theResults = NULL;
    theResults =fopen(fichier, "r");
    //======================
    
    //======================
    if (theResults != NULL) // Lecture du fichier et prise de données
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
        text = "ERREUR DE LECTURE DU FICHIER (FICHIER ERRONE) \n";
    }
    
  //  printData(DataHead);
    //======================

  //   printf("%s \n ",tes);
}
