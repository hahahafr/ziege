#include "jeu.h"
#include "test_u_ia.h"
#include "sauvegarde.h"


int main(){

    jeu_s j;
    sauvegarde s;

    init_jeu(&j);
    init_sauvegarde(&s);

    test_ia_tigre(j,s);



}
