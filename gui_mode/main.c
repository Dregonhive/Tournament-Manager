#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "DataFuncs.h"

#define WINDOW_WIDTH 635
#define WINDOW_HEIGHT 670


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

SDL_Texture* loadTexture(const char* file, SDL_Renderer *ren){
    //Initialize to nullptr to avoid dangling pointer issues
    SDL_Texture *texture = NULL;
    //Load the image
    SDL_Surface *loadedImage = SDL_LoadBMP(file);
    //If the loading went ok, convert to texture and return the texture
    if (loadedImage != NULL)
    {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        //Make sure converting went ok too
        
    }
    
    return texture;
}

int main(int argc, char** argv)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    TTF_Init();
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    
    int Mode = 1; // Condition d'affichage du menu principale.
    
    // Bouton quitter
    SDL_Surface* quitter = NULL;
    SDL_Surface* quitterLow = NULL;
    SDL_Surface* quitterHigh = NULL;

    // Bouton mode1
    SDL_Surface* mode1 = NULL;
    SDL_Surface* mode1Low = NULL;
    SDL_Surface* mode1High = NULL;
    
    SDL_Surface* mode2 = NULL;
    SDL_Surface* mode2Low = NULL;
    SDL_Surface* mode2High = NULL;
    
    SDL_Texture* fileSample = NULL;
    
    SDL_Texture* OKbutton = NULL;
    SDL_Texture* OKbuttonLow = NULL;
    SDL_Texture* OKbuttonHigh = NULL;
    
    SDL_Texture* Returnbutton = NULL;
    SDL_Texture* ReturnbuttonLow = NULL;
    SDL_Texture* ReturnbuttonHigh = NULL;
    
    SDL_Texture* Nextbutton = NULL;
    SDL_Texture* NextbuttonLow = NULL;
    SDL_Texture* NextbuttonHigh = NULL;
    
    SDL_Texture* Ouibutton = NULL;
    SDL_Texture* OuibuttonLow = NULL;
    SDL_Texture* OuibuttonHigh = NULL;
    
    SDL_Texture* Nonbutton = NULL;
    SDL_Texture* NonbuttonLow = NULL;
    SDL_Texture* NonbuttonHigh = NULL;
    
    SDL_Texture* Team4 = NULL;
    SDL_Texture* Team4Low = NULL;
    SDL_Texture* Team4High = NULL;
    SDL_Texture* Team8 = NULL;
    SDL_Texture* Team8Low = NULL;
    SDL_Texture* Team8High = NULL;
    SDL_Texture* Team16 = NULL;
    SDL_Texture* Team16Low = NULL;
    SDL_Texture* Team16High = NULL;
    SDL_Texture* Team32 = NULL;
    SDL_Texture* Team32Low = NULL;
    SDL_Texture* Team32High = NULL;
    
    const char* textToRender = 0;
    const char* textToRender2 = 0;
    const char* textToRender3 = 0;
    SDL_Surface * Texty = NULL;
    SDL_Surface * Texty2 = NULL;
    SDL_Surface * Nota = NULL;
    
    
    SDL_Renderer* render = NULL;
   
    TTF_Font* font = TTF_OpenFont("chalk.ttf", 18);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    
    TTF_Font* fontspec = TTF_OpenFont("chalk.ttf", 16);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    
    TTF_Font* fontsmall = TTF_OpenFont("chalk.ttf", 12);
    TTF_SetFontStyle(fontsmall, TTF_STYLE_BOLD);
    
    TTF_Font* fontbig = TTF_OpenFont("chalk.ttf", 22);
    TTF_SetFontStyle(fontbig, TTF_STYLE_BOLD);
    
    TTF_Font* fonttitle = TTF_OpenFont("chalk.ttf", 48);
    TTF_SetFontStyle(fonttitle, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
    
    SDL_Color white = { 255, 255, 255 };
    SDL_Color black = { 0, 0, 0 };
    
    if( font == NULL )
    {
        fprintf(stdout,"Loading_Font Error (%s)\n",SDL_GetError());
        return 0;
    }
    
    window = SDL_CreateWindow("Tournament Manager",SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    
    if (window == NULL)
    {
        fprintf(stdout,"Create_Window Error (%s)\n",SDL_GetError());
        return -1;
    }
    
    else
    {
      
        int OKW = 0, OKH = 0, TEAMH = 0, TEAMW = 0, NbPoules = 0;
        
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        //  rect = SDL_CreateRGBSurface(0, 64, 48, 32, 0, 0, 0, 0);
        //SDL_SetRenderDrawColor(render,20,20,200,20);
        surface = SDL_GetWindowSurface(window);
        
        
        fileSample = loadTexture("./fileSample.bmp", render);
        
        OKbuttonLow = loadTexture("./OK.bmp", render);
        OKbuttonHigh = loadTexture("./OKhigh.bmp", render);
        SDL_QueryTexture(OKbuttonLow, NULL, NULL, &OKW, &OKH);
        OKbutton = OKbuttonLow;
        
        ReturnbuttonLow = loadTexture("./retour.bmp", render);
        ReturnbuttonHigh = loadTexture("./retourhigh.bmp", render);
        Returnbutton = ReturnbuttonLow;
        
        NextbuttonLow = loadTexture("./suivant.bmp", render);
        NextbuttonHigh = loadTexture("./suivanthigh.bmp", render);
        Nextbutton = NextbuttonLow;
        
        OuibuttonLow = loadTexture("./oui.bmp", render);
        OuibuttonHigh = loadTexture("./ouihigh.bmp", render);
        Ouibutton = OuibuttonLow;
        
        NonbuttonLow = loadTexture("./non.bmp", render);
        NonbuttonHigh = loadTexture("./nonhigh.bmp", render);
        Nonbutton = NonbuttonLow;
        
        
        Team4Low = loadTexture("./4.bmp", render);
        Team4High = loadTexture("./4high.bmp", render);
        Team4 = Team4Low;
        SDL_QueryTexture(Team4Low, NULL, NULL, &TEAMW, &TEAMH);
        
        Team8Low = loadTexture("./8.bmp", render);
        Team8High = loadTexture("./8high.bmp", render);
        Team8 = Team8Low;
        
        Team16Low = loadTexture("./16.bmp", render);
        Team16High = loadTexture("./16high.bmp", render);
        Team16 = Team16Low;
        
        Team32Low = loadTexture("./32.bmp", render);
        Team32High = loadTexture("./32high.bmp", render);
        Team32 = Team32Low;
        
        int buttonH, buttonW; // (buttonH and buttonW are standards)
        // Bouton quitter
        int XQuit = 0, YQuit = 80; // XYQuit to position the button
        quitterLow = SDL_LoadBMP("./quitter.bmp");
        quitterHigh = SDL_LoadBMP("./quitterhigh.bmp");
        SDL_Texture* quitterButton = SDL_CreateTextureFromSurface(render, quitterHigh);
        SDL_QueryTexture(quitterButton, NULL, NULL, &buttonW, &buttonH);
        
        // Bouton Mode1
        int XMode1 = 0, YMode1 = -80; // XYMode1 to position the button
        mode1Low = SDL_LoadBMP("./mode1.bmp");
        mode1High = SDL_LoadBMP("./mode1high.bmp");
        SDL_Texture* mode1Button = NULL;
        
        // Bouton Mode2
        int XMode2 = 0, YMode2 = 00; // XYMode1 to position the button
        mode2Low = SDL_LoadBMP("./mode2.bmp");
        mode2High = SDL_LoadBMP("./mode2high.bmp");
        SDL_Texture* mode2Button = NULL;
        
        SDL_Texture* background = loadTexture("./back.bmp",render);
        SDL_Texture* backmenu = loadTexture("./backmenu.bmp",render);
        SDL_Texture* backend = loadTexture("./backend.bmp",render);
        SDL_Texture* board = loadTexture("./chalkboard.bmp",render);
        SDL_Texture* largeboard = loadTexture("./chalkboardlarge.bmp",render);
        SDL_Texture* largeboard1 = loadTexture("./chalkboardlarge1.bmp",render);
        SDL_Texture* titleboard = loadTexture("./chalktitle.bmp",render);
  
        
        SDL_Texture * textimg = NULL;
        SDL_Texture * textimg2 = NULL;
        SDL_Texture * textimgnota = NULL;
        
        
        
        // char* text = "";
        
        int exit = 0;
        SDL_Event ev;
        
        Poule* tournment;
        Poule* pool;
        Equipe* head ;
        Equipe* tail;
        char *phase, momentText[30000];
        Resultats *matches; //les resultas des matche
        int nombre_poul;
        int nombre_matche=0 ,i ;
        int matche_tournois=0 , winner;
        int nb_mai_allou = 0 , nb_chain = 0 , nb_comp = 0 ;
        EquipePoule TabEquipes[80];
        int cptTabEq = 0;
        int wentonce = 0;
        int numeroPoule = 1;
        while (!exit)
        {
            while (SDL_PollEvent(&ev) != 0)
            {
                if (ev.type == SDL_QUIT)
                { Mode = 0; }
                else
                {
                    int condOui = ((ev.button.x > (150 - 0)) && (ev.button.x < (150 + (OKW)))
                                    && (ev.button.y > 450 ) && (ev.button.y < 450 + (OKH)) );
                    
                    int condNon = ((ev.button.x > (350 - 0)) && (ev.button.x < (350 + (OKW)))
                                    && (ev.button.y > 450 ) && (ev.button.y < 450 + (OKH)) );
        
                     int condQuit = ((Mode == 1) && (ev.button.x > (320 - (buttonW/2))) && (ev.button.x < (320 + (buttonW/2)))
                        && (ev.button.y > 440 + YQuit - (buttonH/2) ) && (ev.button.y < 440 + YQuit + (buttonH/2)) );
                     if (ev.type == SDL_MOUSEMOTION)
                     {
                         if (condQuit)
                             quitter = quitterHigh;
                     
                         else
                             quitter = quitterLow;
                     }
                     if ((ev.type == SDL_MOUSEBUTTONDOWN) && condQuit) // To quit.
                     {
                         Mode = 0;
                     }
                    
                    // Bouton mode1
                    int condMode1 = ((Mode == 1) && (ev.button.x > (320 - (buttonW/2))) && (ev.button.x < (320 + (buttonW/2))) && (ev.button.y > 290 + YMode1 - (buttonH/2)) && (ev.button.y < 290 + YMode1 + (buttonH/2)) );
                    if (ev.type == SDL_MOUSEMOTION)
                    {
                        if (condMode1)
                            mode1 = mode1High;
                        
                        else
                            mode1 = mode1Low;
                    }
                    
                    if ((ev.type == SDL_MOUSEBUTTONDOWN) && condMode1 && Mode == 1) // Mode Lecture
                    {
                        Mode = 21;
                    }
                    if (Mode == 21)
                    {
                        
                        int condOK1 = ((ev.button.x > (240 - 0)) && (ev.button.x < (240 + (OKW)))
                                      && (ev.button.y > 590 ) && (ev.button.y < 590 + (OKH)) );
                        
                        if (ev.type == SDL_MOUSEMOTION)
                        {
                            if(condOK1)
                                OKbutton = OKbuttonHigh;
                            
                            else
                                OKbutton = OKbuttonLow;
                        }
                        if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condOK1))
                        {
                            Mode = 22;
                            //   break;
                        }
                    }
                    
                    if (Mode == 22)
                    {
                        int condTeam4 = ((ev.button.x > (170 - 0)) && (ev.button.x < (170 + (TEAMW)))
                                         && (ev.button.y > 245 ) && (ev.button.y < 245 + (TEAMH)) );
                        
                        if (ev.type == SDL_MOUSEMOTION)
                        {
                            if(condTeam4)
                                Team4 = Team4High;
                            
                            else
                                Team4 = Team4Low;
                        }
                        
                        if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condTeam4))
                        {
                            Mode = 23;
                            NbPoules = 1;
                            //   break;
                        }
                        
                        int condTeam8 = ((ev.button.x > (310 - 0)) && (ev.button.x < (310 + (TEAMW)))
                                         && (ev.button.y > 305 ) && (ev.button.y < 305 + (TEAMH)) );
                        
                        if (ev.type == SDL_MOUSEMOTION)
                        {
                            if(condTeam8)
                                Team8 = Team8High;
                            
                            else
                                Team8 = Team8Low;
                        }
                        
                        if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condTeam8))
                        {
                            Mode = 23;
                            NbPoules = 2;
                            //   break;
                        }
                        
                        int condTeam16 = ((ev.button.x > (170 - 0)) && (ev.button.x < (170 + (TEAMW)))
                                         && (ev.button.y > 365 ) && (ev.button.y < 365 + (TEAMH)) );
                        
                        if (ev.type == SDL_MOUSEMOTION)
                        {
                            if(condTeam16)
                                Team16 = Team16High;
                            
                            else
                                Team16 = Team16Low;
                        }
                        
                        if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condTeam16))
                        {
                            Mode = 23;
                            NbPoules = 4;
                            //   break;
                        }
                        
                        int condTeam32 = ((ev.button.x > (310 - 0)) && (ev.button.x < (310 + (TEAMW)))
                                         && (ev.button.y > 425 ) && (ev.button.y < 425 + (TEAMH)) );
                        
                        if (ev.type == SDL_MOUSEMOTION)
                        {
                            if(condTeam32)
                                Team32 = Team32High;
                            
                            else
                                Team32 = Team32Low;
                        }
                        
                        if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condTeam32))
                        {
                            Mode = 23;
                            NbPoules = 8;
                            //   break;
                        }
                        
                        int condTeam64 = ((ev.button.x > (600 - 0)) && (ev.button.x < (635 + (TEAMW)))
                                         && (ev.button.y > 640 ) && (ev.button.y < 670 + (TEAMH)) );
                       
                        if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condTeam64))
                        {
                            Mode = 23;
                            NbPoules = 16;
                            //   break;
                        }
                        
                    }
                    if (Mode >= 23)
                    {
                        
                        if (Mode == 23)
                        {
                            sleep(1.8);
                        nombre_poul = NbPoules;
                        matches=malloc(sizeof(Resultats)*nombreMatch(nombre_poul));
                        creationTournoi(&tournment,nombre_poul,&nb_mai_allou,&nb_chain,&nb_mai_allou);
                        
                        
                        
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
                            int safesaver = nb_comp;
                            aff_tete(pool,head);
                            aff_queue(pool,tail);
                            pool=suivant(pool);
                        }
                        
                        
                        
                        
                        if(nombre_poul>=2)
                        {
                            /***** passage de la phase prelliminaire  au tournois *****/
                            prem_to_tournois(tournment , &nb_chain);
                            nombre_poul=nombre_poul/2;
                            
                            
                            
                            
                            
                            /*****    phase post_preleminaire   *****/
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
                        phase="Finale";
                        nombre_matche++;
                        matche_tournois++;
                        head=tournment->tete;
                        tail=tournment->queue;
                        winner=simulMatch_post_poule( &head, &tail ,matche_tournois,matches,nombre_matche,phase ,&nb_chain);
                        char momentText6 [100], momentText5[1500] = "Les equipes de depart sont:\n";
                            for( i = 0; i < cptTabEq; i++)
                            {
                                sprintf(momentText6,"%d- %s    ",i+1, TabEquipes[i].nom);
                                strcat(momentText5, momentText6);
                                if ((i + 1) % 4 == 0)
                                    strcat(momentText5, "\n");
                            }
                            textToRender3 = momentText5;
                            
                      
                        if (winner==1)
                        {
                            sprintf(momentText,"L'equipe gagnante du tournoi est: \n --------> %s \n",head->nom);
                            SDL_WaitEvent(&ev);
                            Mode = 25;
                        }
                        else
                        {
                            sprintf(momentText,"L'equipe gagnante du tournoi est: \n --------> %s \n",tail->nom);
                            SDL_WaitEvent(&ev);
                            Mode = 25;
                        }
                        textToRender = momentText;
                        textToRender2 = "---------------------------------- \nVoulez-Vous afficher les resultats \n            des matchs ?  ";
                        }
                      
                    if (Mode == 25)
                    {
                     
                        if (ev.type == SDL_MOUSEMOTION)
                        {
                            if(condOui)
                                Ouibutton = OuibuttonHigh;
                            
                            if(!condOui)
                                Ouibutton = OuibuttonLow;
                            
                            if(condNon)
                                Nonbutton = NonbuttonHigh;
                            
                            if(!condNon)
                                Nonbutton = NonbuttonLow;
                            
                        }
                        if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condOui) )
                        {
                            Mode = 251;
                        }
                        
                        if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condNon))
                        {

                            Mode = 26;
                        }
                    }
                        if (Mode == 251)
                        {
                            sleep(0.8);
                            char momentText2[75], momentText3[2500], momentText4[2500];
                       //     momentText = 0;
                            for( i = 1; i <= nombre_matche; i++)
                            {
                                sprintf(momentText2,"%s: %s %s %d-%d\n",matches[i].phase, matches[i].equipe1, matches[i].equipe2, matches[i].resu1 ,matches[i].resu2);
                                if (i == 1)
                                    strcpy(momentText3, momentText2);
                                
                                else
                                {
                                    if (NbPoules > 2)
                                    {
                                        if (i == 2)
                                            strcpy(momentText4, momentText2);
                                        else
                                        {
                                            if ((i % 2) == 1)
                                                strcat(momentText3, momentText2);
                                            else
                                                strcat(momentText4, momentText2);
                                        }
                                    }
                                    else
                                        strcat(momentText3, momentText2);
                                }
                            }
                            textToRender = momentText3;
                            textToRender2 = momentText4;
                            Mode = 252;
                        }
                        if (Mode == 252)
                        {
                            int condNext = ((ev.button.x > (260 - 0)) && (ev.button.x < (260 + (OKW)))
                                            && (ev.button.y > 610 ) && (ev.button.y < 610 + (OKH)) );
                            
                            if (ev.type == SDL_MOUSEMOTION)
                            {
                                if(condNext)
                                    Nextbutton = NextbuttonHigh;
                                
                                else
                                    Nextbutton = NextbuttonLow;
                            }
                            if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condNext))
                            {
                                Mode = 26;
                                //   break;
                            }
                        }
                    
                        if (Mode == 26)
                        {
                            
                            textToRender = "Voulez-Vous afficher les resultats \n            des Poules  ?  ";
                            if (ev.type == SDL_MOUSEMOTION)
                            {
                                if(condOui)
                                    Ouibutton = OuibuttonHigh;
                                
                                if(!condOui)
                                    Ouibutton = OuibuttonLow;
                                
                                if(condNon)
                                    Nonbutton = NonbuttonHigh;
                                
                                if(!condNon)
                                    Nonbutton = NonbuttonLow;
                                
                            }
                            if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condOui) )
                            {
                                Mode = 261;
                            }
                            
                            if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condNon) && (wentonce >= 1))
                            {
                                Mode = 27;
                            }
                            wentonce += 1;
                        }
                        if (Mode == 261)
                        {
                            sleep(0.8);
                            char momentText2[200], momentText3[7000];
                            for( i = 0; i < cptTabEq; i++)
                            {
                                sprintf(momentText2,"%s - Poule %d - Pts Poule = %d - Credit de Poule = %d\n", TabEquipes[i].nom, TabEquipes[i].numPoule,TabEquipes[i].points, TabEquipes[i].totMarq - TabEquipes[i].totEncais);
                                if (i == 0)
                                    strcpy(momentText3, momentText2);
                                else
                                    strcat(momentText3, momentText2);
                            }
                            textToRender = momentText3;
                            Mode = 262;
                        }
                        
                        if (Mode == 262)
                        {
                            int condNext = ((ev.button.x > (260 - 0)) && (ev.button.x < (260 + (OKW)))
                                            && (ev.button.y > 610 ) && (ev.button.y < 610 + (OKH)) );
                            
                            if (ev.type == SDL_MOUSEMOTION)
                            {
                                if(condNext)
                                    Nextbutton = NextbuttonHigh;
                                
                                else
                                    Nextbutton = NextbuttonLow;
                            }
                            if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condNext))
                            {
                                Mode = 27;
                                //   break;
                            }
                        }
                        
                        if (Mode == 27)
                        {
                            textToRender = "Voulez-Vous afficher les details \n           techniques ?  ";
                            if (ev.type == SDL_MOUSEMOTION)
                            {
                                if(condOui)
                                    Ouibutton = OuibuttonHigh;
                                
                                if(!condOui)
                                    Ouibutton = OuibuttonLow;
                                
                                if(condNon)
                                    Nonbutton = NonbuttonHigh;
                                
                                if(!condNon)
                                    Nonbutton = NonbuttonLow;
                                
                            }
                            if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condOui) )
                            {
                                Mode = 271;
                            }
                            
                            if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condNon) && (wentonce <= 1))
                            {
                                Mode = 1;
                            }
                            wentonce -= 100;
                        }
                        if (Mode == 271 )
                        {
                            sleep(0.8);
                            char momentText[1000];
                            
                            sprintf(momentText, "======================================= \nLe nombre de maillons alloues = %d \nLe nombre de chainages = %d \nLe nombre de comparaisons = %d \nLa taille en octet d'une liste ""Poule"" = %lu \nLa taille en octet de la liste totale = %lu \n======================================= \n",nb_mai_allou, nb_chain,nb_comp, (4 * sizeof(Equipe)), (NbPoules * 4 * sizeof(Equipe)));
                            textToRender = momentText;
                            Mode = 272;
                        }
                        if (Mode == 272)
                        {
                            int condNext = ((ev.button.x > (245 - 0)) && (ev.button.x < (245 + (OKW)))
                                            && (ev.button.y > 560) && (ev.button.y < 560 + (OKH)) );
                            
                            if (ev.type == SDL_MOUSEMOTION)
                            {
                                if(condNext)
                                    Returnbutton = ReturnbuttonHigh;
                                
                                else
                                    Returnbutton = ReturnbuttonLow;
                            }
                            if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condNext))
                            {
                                sleep(1.5);
                                Mode = 1;
                                //   break;
                            }
                        }
                    }
                    
                    // Bouton mode2
                    int condMode2 = ((Mode == 1) && (ev.button.x > (320 - (buttonW/2))) && (ev.button.x < (320 + (buttonW/2)))
                                     && (ev.button.y > 365 + YMode2 - (buttonH/2)) && (ev.button.y < 365 + YMode2 + (buttonH/2)) );
                    if (ev.type == SDL_MOUSEMOTION)
                    {
                        if (condMode2)
                        {
                            mode2 = mode2High;
                         
                        }
                        else
                            mode2 = mode2Low;
                    }
                    if ((ev.type == SDL_MOUSEBUTTONDOWN) && condMode2) // Mode Lecture
                    {
                           Mode = 3;
                    }
                    
                    
                        if (Mode == 3)
                        {
                          
                            int condOK = ((ev.button.x > (110 - 0)) && (ev.button.x < (110 + (OKW)))
                                      && (ev.button.y > 600 ) && (ev.button.y < 600 + (OKH)) );
                        
                            if (ev.type == SDL_MOUSEMOTION)
                            {
                                if(condOK)
                                    OKbutton = OKbuttonHigh;
                            
                            else
                                OKbutton = OKbuttonLow;
                            }
                            if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condOK))
                            {
                                Mode = 4;
                                sleep(1.8);
                            }
                        }
                        if (Mode == 4)
                        {
                       // void mainLecture(void)
                            char ligne[MAX_LENGTH];
                            int cptTabRes = 0;
                            char texterim[250];
                            Resultats tabResRead[MAX_MATCH];
                            Team_Data *DataHead = NULL ;
                            DataHead= initialisation();
                  
                            //======================
                            // File Call part
                            char fichier[15];
                            SDL_ShowSimpleMessageBox(0, "Fichier Source Lecture", "Veuillez introduire le chemin du fichier a lire.", window);
                            printf("Le chemin du fichier a lire : --> ");
                            scanf("%s",fichier);
                            sleep(1.8);
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
                              //  SDL_Delay(500);
                                //--------------------------
                                    Team_Data *P = DataHead, *Q = NULL, *R = NULL;
                                    int i = 0, j = 0, verif = 0, cptTeam = 0, condToProceed = 1;
                                    //------------- Enregistrement des equipes
                                    char pl = 0;
                                    for (i = 1; i < cptTabRes; i++)
                                    {
                                        Q = P -> Suivant;
                                        R = Q -> Suivant;
                                        verif = 0;
                                        while (R != NULL)
                                        {
                                            if (strcmp(R -> nom, tabResRead[i].equipe1) == 0)
                                            {
                                                verif = 1;
                                            }
                                            Q = R;
                                            R = R -> Suivant;
                                        }
                                        if (verif == 0)
                                        {
                                            pl = tabResRead[i].phase[6];
                                            R = creationData(atoi(&pl), tabResRead[i].equipe1);
                                            affAdrData(Q, R);
                                            cptTeam++;
                                        }
                                        
                                        // Reinitialisation pour la seconde equipe.
                                        Q = P -> Suivant;
                                        R = Q -> Suivant;
                                        verif = 0;
                                        
                                        while (R != NULL)
                                        {
                                            if (strcmp(R -> nom, tabResRead[i].equipe2) == 0)
                                            {
                                                verif = 1;
                                            }
                                            Q = R;
                                            R = R -> Suivant;
                                        }
                                        if (verif == 0)
                                        {
                                            pl = tabResRead[i].phase[6];
                                            R =  creationData(atoi(&pl), tabResRead[i].equipe2);
                                            affAdrData(Q, R);
                                            cptTeam++;
                                        }
                                    }
                                    //-------------------------- Controle du nombre de matchs/ Equipes:
                                    if (cptTeam != ((cptTabRes + 1)/2)) // Formule du nombre d'equipes (nombre de matchs connus)
                                    {
                                        sprintf(texterim, "Nombre d`equipes = %d \nNombre de matchs = %d \nERREUR! ---> Les nombres ne correspondent pas. ", cptTeam, cptTabRes);
                                        textToRender3 = texterim;
                                        Mode = 5;
                                        break;
                                    }
                                    else
                                    {
                                        //-------------------------- Prise en compte des matchs
                                        Team_Data *inter;
                                        
                                        //----------------------------------------- Phase de poule.
                                        int lim = ((cptTeam * 6)/4); // nombre de matchs de poule.
                                        
                                        for (i = 1; i <= lim; i++)
                                        {
                                            inter = rechData(DataHead, tabResRead[i].winner);
                                            inter -> ptsPoule += 2;
                                            if (tabResRead[i].resu1 > tabResRead[i].resu2)
                                                inter -> nbButsPoule += tabResRead[i].resu1 - tabResRead[i].resu2;
                                            else
                                                inter -> nbButsPoule += tabResRead[i].resu2 - tabResRead[i].resu1;
                                            
                                            
                                            inter = rechData(DataHead, tabResRead[i].loser);
                                            inter -> ptsPoule += 1;
                                            if (tabResRead[i].resu1 < tabResRead[i].resu2)
                                                inter -> nbButsPoule += tabResRead[i].resu1 - tabResRead[i].resu2;
                                            else
                                                inter -> nbButsPoule += tabResRead[i].resu2 - tabResRead[i].resu1;
                                        }
                                        
                                        //------------------ Le Tri
                                        j = 1;
                                        
                                        while (j <= (cptTeam - 3))
                                        {
                                            TriPoule(DataHead, j);
                                            j += 4;
                                        }
                                        
                                        //------------------ Disqualifiquation
                                        Q = (DataHead -> Suivant) -> Suivant; //Car Head est une Tete indirecte.
                                        while (Q != NULL)
                                        {
                                            Q -> disqualif = 1;
                                            strcpy (Q -> phasediscalif, "Poule");
                                            (Q -> Suivant) -> disqualif= 1;
                                            strcpy ((Q -> Suivant) -> phasediscalif, "Poule");
                                            Q = ((((Q -> Suivant) -> Suivant) -> Suivant) -> Suivant);
                                        }
                                        
                                        //----------------------------------------- Post-poule.
                                        Team_Data *interA, *interB;
                                        for (i = lim + 1; i <= cptTabRes; i++)
                                        {
                                            interA = rechData(DataHead,tabResRead[i].equipe1);
                                            interB = rechData(DataHead,tabResRead[i].equipe2);
                                            
                                            
                                            if (interA -> disqualif == 1)  // equipes disqualifiée participant ulterieurierement
                                            {
                                                sprintf(texterim,"ERREUR! ---> l'equipe %s participe invalidement au match N= %d au niveau de la Phase suivante: %s \n", interA -> nom, i, tabResRead[i].phase);
                                                textToRender3 = texterim;
                                                condToProceed = 0;
                                                Mode = 5;
                                                break;
                                            }
                                            else
                                            {
                                                if (interB -> disqualif == 1)
                                                {
                                                    sprintf(texterim, "ERREUR! ---> l'equipe %s participe invalidement au match N= %d au niveau de la Phase suivante: %s \n", interB -> nom, i, tabResRead[i].phase);
                                                    textToRender3 = texterim;
                                                    condToProceed = 0;
                                                    Mode = 5;
                                                    break;
                                                }
                                                else
                                                {
                                                    inter = rechData(DataHead,tabResRead[i].loser);
                                                    inter -> disqualif = 1;
                                                    strcpy(inter -> phasediscalif, tabResRead[i].phase);
                                                }
                                            }
                                        }
                                        if (condToProceed == 1)
                                        {
                                            textToRender2 = 0;
                                            momentText[0] = '\0';
                                            char momentText4[200];
                                            P = (DataHead -> Suivant) -> Suivant;
                                            while (P != NULL)
                                            {
                                                if (P -> disqualif == 0)
                                                sprintf(momentText4,"%s - Poule %d - Pts. P = %d - credit = %d ---> Vainquer \n", P -> nom, P -> poule,             P -> ptsPoule, P -> nbButsPoule);
                                                
                                                else
                                                sprintf(momentText4,"%s - Poule %d - Pts. P = %d - credit = %d - disqualif. en: %s \n", P -> nom, P -> poule,             P -> ptsPoule, P -> nbButsPoule, P -> phasediscalif);
                                                
                                                P = P -> Suivant;
                                                if (P == DataHead)
                                                    strcpy(momentText, momentText4);
                                                else
                                                    strcat(momentText, momentText4);
                                            }
                                            textToRender2 = momentText;
                                            int u = 0;
                                            inter = (DataHead -> Suivant) -> Suivant; //Car Head est une Tete indirecte.
                                            while (u == 0) // Recherche de l'equipe Gagnante
                                            {
                                                if (inter -> disqualif == 0)
                                                    u = 1;
                                                else
                                                inter = inter -> Suivant;
                                            }
                                            sprintf(texterim, " __________________________________ \nL'equipe : %s remporte le tournoi \n         --- TOURNOI VALIDE --- \n", inter -> nom);
                                            textToRender = texterim;
                                            Mode = 5;
                                        }
                                    }

                              //  break;
                            }
                            else
                            {
                                textToRender3 = "ERREUR DE LECTURE DU FICHIER (FICHIER ERRONE) \n";
                                Mode = 5;
                                //break;
                            }
                        
                            
                        }
                        if (Mode == 5)
                        {
                            int condOK = ((ev.button.x > (245 - 0)) && (ev.button.x < (245 + (OKW)))
                                          && (ev.button.y > 610 ) && (ev.button.y < 610 + (OKH)) );
                            
                            if (ev.type == SDL_MOUSEMOTION)
                            {
                                if(condOK)
                                    Returnbutton = ReturnbuttonHigh;
                                
                                else
                                    Returnbutton = ReturnbuttonLow;
                            }
                            if ((ev.type == SDL_MOUSEBUTTONDOWN) && (condOK) && (Mode == 5))
                            {
                                Mode = 1;
                                sleep(1.3);
                            }
                        }

                    
                    
                    
                
                    
                    /*    //KEYBOARD EVENTS
                     if (ev.type == SDL_KEYDOWN)
                     {
                     switch (ev.key.keysym.sym)
                     {
                     case (SDLK_f) :
                     image = image1;
                     break;
                     case (SDLK_g) :
                     image = image2;
                     break;
                     case (SDLK_h) :
                     image = image3;
                     break;
                     
                     }
                     }  */
                    
                }
            }
          /*
            int bH, bW;
            SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
           
           // renderTexture(background, render, bW, 0);
            //renderTexture(background, render, 0, bH);
            //renderTexture(background, render, bW, bH);
            
            int iW, iH;
            SDL_QueryTexture(foreground, NULL, NULL, &iW, &iH);
            renderTexture(foreground, render, 320 - (iW/2), 240 - (iH/2));
            renderTexture(another, render, 20, 20);
            */
            
            
             //SDL_Texture* tex = SDL_CreateTextureFromSurface(render, image);
             //First clear the renderer
            
             //Draw the texture
            SDL_RenderClear(render);
            
            // Background
            SDL_RenderCopy(render, background, NULL, NULL);
            renderTexture(background, render, 0, 0);
            
     
            switch (Mode)
            {
                case 0:
                {
                    renderTexture(backend, render, 0, 0);
                    Mode = 999;
                    break;
                }
                case 999:
                {
                    sleep(1.8);
                     exit = 1;
                    break;
                }
                case 1:
                    //Bouton quitter
                    renderTexture(backmenu, render, 0, 0);
                    quitterButton = SDL_CreateTextureFromSurface(render, quitter);
                    renderTexture(quitterButton, render, 320 - (buttonW/2), 240 + YQuit - (buttonH/2) + 200 );
                    
                    //Bouton Mode1
                    mode1Button = SDL_CreateTextureFromSurface(render, mode1);
                    renderTexture(mode1Button, render, 320 - (buttonW/2), 240 + YMode1 - (buttonH/2) + 50 );
                    
                    //Bouton Mode2
                    mode2Button = SDL_CreateTextureFromSurface(render, mode2);
                    renderTexture(mode2Button, render, 320 - (buttonW/2), 240 + YMode2 - (buttonH/2) + 125);
                    break;
                    
                case 21:
                {
                    
                    char *textintro2 = "Dans ce mode, un tournoi sera aleatoirement simule du debut jusqu`a la fin. Les scores des matchs couvrants meme d`eventuels cas de forfait. \nseul le nombre d`equipes de depart doit etre choisi (des noms leurs seront aleatoirement attribues a partir d`une liste de pays).";
                    Texty = TTF_RenderText_Blended_Wrapped(fontbig, textintro2, white, 580);
                    textimg = SDL_CreateTextureFromSurface(render, Texty);
                    
                    Texty2 = TTF_RenderText_Blended_Wrapped(fonttitle, "MODE SIMULATION", white, 700);
                    textimg2 = SDL_CreateTextureFromSurface(render, Texty2);
                    
                    renderTexture(titleboard, render, 18, 20);
                    renderTexture(largeboard1, render, 10, 180);
                    renderTexture(textimg, render, 40  , 215 );
                    renderTexture(textimg2, render, 42  , 30 );
                    renderTexture(OKbutton, render, 240, 590);
                    break;
                }
                case 22:
                {
                    char *textintro2 = "Veuillez selectionner le nombre d`equipes qui participeront au tournoi: ";
                    Texty = TTF_RenderText_Blended_Wrapped(font, textintro2, white, 300);
                    textimg = SDL_CreateTextureFromSurface(render, Texty);
                    
                    Nota = TTF_RenderText_Blended_Wrapped(font, "*Nota: les nombres plus grands ont ete evites par souci d`affichage.", black, 500);
                    textimgnota = SDL_CreateTextureFromSurface(render, Nota);
                    
                 
                    renderTexture(board, render, 147, 100);
                    renderTexture(textimg, render, 185, 130 );
                    renderTexture(textimgnota, render, 95, 510);
                    renderTexture(Team4, render, 170, 245);
                    renderTexture(Team8, render, 310, 305);
                    renderTexture(Team16, render, 170, 365);
                    renderTexture(Team32, render, 310, 425);
                    break;
                }
  
                case 25 :
                {
                    SDL_FreeSurface(Texty);
                    Texty = TTF_RenderText_Blended_Wrapped(fontbig, textToRender, white, 550);
                    textimg = SDL_CreateTextureFromSurface(render, Texty);
                    
                    Texty2 = TTF_RenderText_Blended_Wrapped(fontbig, textToRender2, white, 550);
                    textimg2 = SDL_CreateTextureFromSurface(render, Texty2);
                    
                    if (NbPoules < 8)
                        Nota = TTF_RenderText_Blended_Wrapped(fontspec, textToRender3, black, 600);
                    else
                        Nota = TTF_RenderText_Blended_Wrapped(fontsmall, textToRender3, black, 600);
                    textimgnota = SDL_CreateTextureFromSurface(render, Nota);
                    
                    renderTexture(largeboard1, render, 10, 180);
                    renderTexture(textimgnota, render, 15, 10);
                    renderTexture(textimg, render, 70, 230 );
                    renderTexture(textimg2, render, 75, 335 );
                    renderTexture(Ouibutton, render, 150, 450);
                    renderTexture(Nonbutton, render, 350, 450);
                    
                    break;
                }
                    
                case 252:
                {
                    SDL_FreeSurface(Texty);
                    Texty = TTF_RenderText_Blended_Wrapped(fontsmall, textToRender, white, 300);
                    textimg = SDL_CreateTextureFromSurface(render, Texty);
                    Texty2 = TTF_RenderText_Blended_Wrapped(fontsmall, textToRender2, white, 600);
                    textimg2 = SDL_CreateTextureFromSurface(render, Texty2);
                    SDL_Surface* Resultats = TTF_RenderText_Blended_Wrapped(fontbig, "Les Resultats des Matchs", black, 500);
                    SDL_Texture* TitleRes = SDL_CreateTextureFromSurface(render, Resultats);
                    renderTexture(largeboard, render, 10, 50);
                    renderTexture(textimg, render, 20, 55 );
                    renderTexture(textimg2, render, 340, 55 );
                    renderTexture(TitleRes, render, 150, 10);
                    renderTexture(Nextbutton, render, 260, 610);
                    break;
                }
                    
                case 26 :
                {
                    SDL_FreeSurface(Texty);
                    Texty = TTF_RenderText_Blended_Wrapped(fontbig, textToRender, white, 550);
                    textimg = SDL_CreateTextureFromSurface(render, Texty);
                    renderTexture(largeboard1, render, 10, 180);
                    renderTexture(textimg, render, 70, 300 );
                    renderTexture(Ouibutton, render, 150, 450);
                    renderTexture(Nonbutton, render, 350, 450);
                    
                    
                    break;
                }
                    
                case 262:
                {
                    SDL_FreeSurface(Texty);
                    Texty = TTF_RenderText_Blended_Wrapped(fontsmall, textToRender, white, 600);
                    textimg = SDL_CreateTextureFromSurface(render, Texty);
                    SDL_Surface* Resultats = TTF_RenderText_Blended_Wrapped(fontbig, "Les Resultats de Poule", black, 500);
                    SDL_Texture* TitleRes = SDL_CreateTextureFromSurface(render, Resultats);
                    
                    renderTexture(largeboard, render, 10, 50);
                    renderTexture(textimg, render, 20, 55 );
                    renderTexture(TitleRes, render, 150, 10);
                    renderTexture(Nextbutton, render, 260, 610);
                    break;
                }
                    
                case 27 :
                {
                    SDL_FreeSurface(Texty);
                    Texty = TTF_RenderText_Blended_Wrapped(fontbig, textToRender, white, 550);
                    textimg = SDL_CreateTextureFromSurface(render, Texty);
                    renderTexture(largeboard1, render, 10, 180);
                    renderTexture(textimg, render, 70, 300 );
                    renderTexture(Ouibutton, render, 150, 450);
                    renderTexture(Nonbutton, render, 350, 450);
                    break;
                }
                    
                case 272:
                {
                    SDL_FreeSurface(Texty);
                    Texty = TTF_RenderText_Blended_Wrapped(font, textToRender, white, 600);
                    textimg = SDL_CreateTextureFromSurface(render, Texty);
                    SDL_Surface* Resultats = TTF_RenderText_Blended_Wrapped(fonttitle, "Details Techniques", white, 600);
                    SDL_Texture* TitleRes = SDL_CreateTextureFromSurface(render, Resultats);
                    renderTexture(titleboard, render, 17, 10);
                    renderTexture(TitleRes, render, 30, 15);
                    renderTexture(largeboard1, render, 10, 180);
                    renderTexture(textimg, render, 50, 230 );
                    renderTexture(Returnbutton, render, 245, 560);
                    break;
                }
                case 3:
                    {
                        char *textintro2 = "Dans ce mode, donnees et resultats du tournoi seront lus a partir d`un fichier texte se trouvant dans le dossier source du programme et respectant le formalisme tel que montre l`image ci-contre:";
                        Texty = TTF_RenderText_Blended_Wrapped(fontbig, textintro2, white, 330);
                        textimg = SDL_CreateTextureFromSurface(render, Texty);
                        
                        Texty2 = TTF_RenderText_Blended_Wrapped(fonttitle, "MODE LECTURE", white, 580);
                        textimg2 = SDL_CreateTextureFromSurface(render, Texty2);
                        
                        renderTexture(titleboard, render, 17, 10);
                        renderTexture(board, render, 10, 170);
                        renderTexture(textimg2, render, 87, 20 );
                        
                        renderTexture(textimg, render, 23, 180 );
                        
                        renderTexture(fileSample, render, 358, 170);
                        renderTexture(OKbutton, render, 110, 600);
                        break;
                    }
                      //  SDL_Delay(10000);
                       // introMode2 = 0;
                        
                    
                case 5:
                {
                    SDL_FreeSurface(Texty);
                    Texty = TTF_RenderText_Blended_Wrapped(font, textToRender, white, 600);
                    textimg = SDL_CreateTextureFromSurface(render, Texty);
                    Texty2 = TTF_RenderText_Blended_Wrapped(fontsmall, textToRender2, white, 600);
                    textimg2 = SDL_CreateTextureFromSurface(render, Texty2);
                    Nota = TTF_RenderText_Blended_Wrapped(fontbig, textToRender3, white, 600);
                    textimgnota = SDL_CreateTextureFromSurface(render, Nota);
                    int textH, textW;
                    SDL_QueryTexture(textimg, NULL, NULL, &textW, &textH);
                    renderTexture(largeboard, render, 10, 50);
                    renderTexture(textimg, render, 80, 470 );
                    renderTexture(textimg2, render, 25, 60 );
                    renderTexture(textimgnota, render, 25, 270 );
                    renderTexture(Returnbutton, render, 245, 610);
                    break;
                }
                default:
                    break;
            }
            
        
           
            
            
             //Update the screen
             SDL_RenderPresent(render);
            
        }
        
        
    }
    
    SDL_FreeSurface(surface);
    SDL_FreeSurface(quitter);
    SDL_FreeSurface(mode1);
    
    TTF_CloseFont(font);
    
    SDL_DestroyWindow(window);
    
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}