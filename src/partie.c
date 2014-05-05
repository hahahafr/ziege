#include "partie.h"

void init_partie(partie * g){
    *g = (partie)malloc(sizeof(t_partie));

    (*g)->phase = PHASE_PLACEMENT;
    (*g)->nb_tigre = NB_MAX_TIGRE;
    (*g)->nb_chevre = 0;
}
