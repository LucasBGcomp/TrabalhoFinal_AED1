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
int removerModalidade(Modalidades *d, char *nome);
int altNomeModalidade(Modalidades *d, char *nomeAnt, char *nomeNovo);
void buscarModalidade(Modalidades *d, char *nome);
int carregarModalidadesArquivo(Modalidades *d, char *nomeArquivo);
#endif