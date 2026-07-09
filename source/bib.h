#ifndef BIB_H
#define BIB_H
typedef struct modalidades Modalidades;
typedef struct equipes Equipes;
typedef struct noModalidades NoModalidades;
typedef struct noEquipes NoEquipes;
void inicializarListaP(Modalidades **d);
int inserirModalidade(Modalidades *d, char *nome);
int quantModalidades(Modalidades *d);
void listarModalidades(Modalidades *d);
#endif