#include "sauvegarde.h"

void init_sauvegarde(sauvegarde * s){
    *s = (sauvegarde)malloc(sizeof(t_sauvegarde));

    INIT_PILE(&((*s)->historique));

    strcpy ((*s)->file,"save.txt");
}

void ajout_historique(jeu_s j,sauvegarde s){
    jeu_s tmp;

    tmp = (jeu_s)malloc(sizeof(t_jeu));

    //Copie de la partie
    tmp->g = (partie)malloc(sizeof(t_partie));

    memcpy(tmp->g,j->g,sizeof(t_partie));

    tmp->g->t = (tigres)malloc(sizeof(t_tigre)*NB_MAX_TIGRE);

    for(int i=0;i<NB_MAX_TIGRE;i++)
        memcpy(tmp->g->t,j->g->t,sizeof(t_tigre)*NB_MAX_TIGRE);


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

    free(tmp);
}

jeu_s revenir_arriere(jeu_s * j,sauvegarde s){
    jeu_s tmp;

    tmp = DEPILER(&(s->historique));

    free(*j);

    return(tmp);
}

void sauvegarde_fichier(jeu_s j,sauvegarde s){

    FILE * f;

    f = fopen("save.txt","a");

    if( f==NULL ){
        printf("Erreur dans l'ouverture du fichier de sauvegarde!\n");
        return;
    }

    //Ecriture du plateau

    fprintf(f,"/board");

    for(int i=0;i<PLATEAU_HAUTEUR;i++){
        fprintf(f,"\n");
        for(int k=0;j<PLATEAU_LARGEUR;j++){
            if( j->p->grille[i][k].pion == -1 )
                fprintf(f,".");

            if( j->p->grille[i][k].pion == 0 )
                fprintf(f,"G");

            if( j->p->grille[i][k].pion == 1 )
                fprintf(f,"T");
        }
    }

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
}

int chargement_fichier(jeu_s j,sauvegarde s){
    char  buffer[100];
    char player[] = "/player ", phase[] = "/phase ",capture[] = "/captured ";
    bool trouve = false;
    int h=0;
    FILE * f;

    f = fopen(s->file,"r");

    if( f==NULL ){
        printf("Erreur dans l'ouverture du fichier de sauvegarde!\n");
        return;
    }

    //Ecriture du plateau
    fread(buffer,sizeof(char),strlen("/board\n"),f);

    if( strcpy(buffer,"/board\n" ) != 0){
        return(-1);
    }

    for(int i=0;i<PLATEAU_HAUTEUR;i++){
        fread(buffer,sizeof(char),PLATEAU_LARGEUR,f);
        for(int k=0;j<PLATEAU_LARGEUR;j++){
            trouve = false;

            if( buffer[h] == '.' ){
                 j->p->grille[i][k].pion = VIDE;
                 trouve=true;
            }

            if( buffer[h] == 'T' ){
                j->p->grille[i][k].pion = TIGRE;
                trouve=true;
            }


            if( buffer[h] == 'G' )
                j->p->grille[i][k].pion = CHEVRE;
                trouve=true;

            if( !trouve )
                return(-1);
        }
    }

    //Chargement du joueur
    fread(buffer,sizeof(char),player,f);

    if( strcmp(buffer,player) != 0 ){
        return(-1);
    }

    fread(buffer,sizeof(char),strlen("g\n"),f);

    if( buffer[0] != 'G' && buffer[0] != 'T')
        return(-1);

    if(  'G' == buffer[0] )
        j->g->joueur = CHEVRE;

    if(  'T' == buffer[0] )
        j->g->joueur = CHEVRE;

    //Chargement de la phase

    fread(buffer,sizeof(char),phase,f);

    if( strcmp(buffer,phase) != 0 ){
        return(-1);
    }

    fread(buffer,sizeof(char),strlen("g\n"),f);

    if( buffer[0] != 0 && buffer[0] != 1)
        return(-1);

    j->g->phase = buffer[0];

    //Chargement du nombre de chèvre capturée

    fread(buffer,sizeof(char),phase,f);

    if( strcmp(buffer,capture) != 0 ){
        return(-1);
    }

    fread(buffer,sizeof(char),2,f);

    if( !isdigit(buffer[0]) )
        return(-1);

    j->participant[TIGRE].score = 0;

    for(int i=0;i<2;i++){
        if( !isdigit(buffer[i]) )
            j->participant[TIGRE].score = j->participant[TIGRE].score * 10 + buffer[i];
    }

    fclose(f);

}

