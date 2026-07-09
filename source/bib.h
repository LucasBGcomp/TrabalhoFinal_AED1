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
<<<<<<< HEAD
int removerModalidade(Modalidades *d, char *nome);
=======
void antNomeModalidade(Modalidades *d, char *nomeAnt, char *nomeNovo);
>>>>>>> 6ec2b5aac9d9aa58f982d0fb0c292ce10d8e4084
#endif