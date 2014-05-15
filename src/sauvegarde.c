#include "sauvegarde.h"
#include "ui.h"

void init_sauvegarde(sauvegarde * s){

    *s = (sauvegarde)malloc(sizeof(t_sauvegarde));

    strcpy ((*s)->file,"save.txt");

    INIT_PILE(&((*s)->historique));
}

void ajout_historique(jeu_s j,sauvegarde s){
    jeu_s tmp;

    if( j->participant[j->g->joueur].is_ai )
        return;

    tmp = (jeu_s)malloc(sizeof(t_jeu));

    //Copie de la partie
    tmp->g = (partie)malloc(sizeof(t_partie));

    memcpy(tmp->g,j->g,sizeof(t_partie));

    tmp->g->t = (tigres)malloc(sizeof(t_pion)*NB_MAX_TIGRE);

    for(int i=0;i<NB_MAX_TIGRE;i++)
        memcpy(tmp->g->t,j->g->t,sizeof(t_pion)*NB_MAX_TIGRE);


    //Copie du plateau
    tmp->p = (plateau)malloc(sizeof(t_plateau));

    memcpy(tmp->p,j->p,sizeof(t_plateau));

    for(int i=0;i<PLATEAU_HAUTEUR;i++)
        memcpy(tmp->p->grille[i],j->p->grille[i],sizeof(t_case)*PLATEAU_LARGEUR);

    //Copie des participants
    tmp->participant = (joueur)malloc(sizeof(t_joueur)*2);

    memcpy(tmp->participant,j->participant,sizeof(t_joueur)*2);

    for(int i=0;i<2;i++)
        memcpy(tmp->participant[i].nom,j->participant[i].nom,sizeof(char)*TAILLE_NOM);


    EMPILER(&(s->historique),tmp);
}

jeu_s revenir_arriere(jeu_s j,sauvegarde s){
    jeu_s tmp;

    tmp = DEPILER(&(s->historique));

    if( tmp = -1 ){
        return(j);
    }

    free(j);

    return(tmp);
}

int sauvegarde_fichier(jeu_s j,sauvegarde s){

    FILE * f;

    f = fopen(s->file,"w+");

    if( f==NULL ){
        printf("Erreur dans l'ouverture du fichier de sauvegarde!\n");
        return 1;
    }

    //Ecriture du plateau

    fprintf(f,"/board\n");

    for(int i=0;i<PLATEAU_HAUTEUR;i++){
        for(int k=0;k<PLATEAU_LARGEUR;k++){
            if( j->p->grille[i][k].pion == -1 )
                fprintf(f,".");

            if( j->p->grille[i][k].pion == 0 )
                fprintf(f,"G");

            if( j->p->grille[i][k].pion == 1 )
                fprintf(f,"T");
        }
        fprintf(f,"\n");
    }
    fprintf(f,"/endboard\n");

    //Ecriture du joueur
    if( j->g->joueur == 1 )
        fprintf(f,"/player T\n");
    else
        fprintf(f,"/player G\n");

    //Ecriture de la phase
    fprintf(f,"/phase %d\n",j->g->phase);


    //Ecriture du nombre de chèvre capturée
    fprintf(f,"/captured %d\n",j->participant[TIGRE].score);

    fclose(f);
    return 0;
}

int chargement_fichier(jeu_s j, sauvegarde s){
    char  buffer[100],*capture;
    bool trouve = false;    
    int h=0;
    FILE * f;

    f = fopen(s->file,"r");

    if( f==NULL ){
        printf("Erreur dans l'ouverture du fichier de sauvegarde!\n");
        return 1;
    }

    //Ecriture du plateau
    fgets(buffer,100,f);

    if( strcmp(buffer,"/board\n" ) != 0){
        return(-1);
    }

    for(int i=0;i<PLATEAU_HAUTEUR;i++){
        fgets(buffer,100,f);
        for(int k=0;k<PLATEAU_LARGEUR;k++){
            trouve = false;

            if( buffer[k] == '.' ){
                 j->p->grille[i][k].pion = VIDE;
                 trouve=true;
            }

            if( buffer[k] == 'T' ){
                j->p->grille[i][k].pion = TIGRE;
                trouve=true;
            }


            if( buffer[k] == 'G' )
                j->p->grille[i][k].pion = CHEVRE;
                trouve=true;

            if( !trouve )
                return(-1);
        }
    }

    fgets(buffer,100,f);
    if( strcmp(buffer,"/endboard\n\0") != 0 ){
        return(-1);
    }

    //Chargement du joueur
    fgets(buffer,100,f);

    if( strcmp(buffer,"/player G\n\0") != 0 || strcmp(buffer,"/player T\n\0") != 0 ){
        return(-1);
    }
    if (buffer[strlen(buffer)-3] == 'T')
        j->g->joueur = TIGRE;
    else
        j->g->joueur = CHEVRE;

    //Chargement de la phase

    fgets(buffer,100,f);

    if( strcmp(buffer,"/phase 0\n\0") != 0 || strcmp(buffer,"/phase 1\n\0") != 0){
        return(-1);
    }
    if (buffer[strlen(buffer)-3] == '0')
        j->g->phase = PHASE_PLACEMENT;
    else
        j->g->phase = PHASE_DEPLACEMENT;

    //Chargement du nombre de chèvre capturée

    fgets(buffer,100,f);

    capture = &(buffer[strlen("/captured ")]);

    if( (j->participant[TIGRE].score = atoi(capture)) == -1){
        return(-1);
    }

    fclose(f);

    return(0);

}

/*int sauvegarder(jeu_s j)
{
    sauvegarde s;
    init_sauvegarde(&s);
    ajout_historique(j,s);
    return(sauvegarde_fichier(j,s));
}

int charger(jeu_s j)
{
    sauvegarde s;
    init_sauvegarde(&s);
    return(chargement_fichier(j,s));
}*/
