#ifndef PARTIE_H
#define PARTIE_H

typedef struct et_partie {
    int phase;
    int nb_tigre;
    int nb_chevre;
}t_partie;

typedef t_partie * partie;

void init_partie(partie * g);

#endif

