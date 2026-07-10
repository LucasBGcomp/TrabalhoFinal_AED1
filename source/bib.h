#ifndef BIB_H
#define BIB_H
typedef struct modalidades Modalidades;
typedef struct noModalidades NoModalidades;
typedef struct noEquipes NoEquipes;
void inicializarListaP(Modalidades **d);
int inserirModalidade(Modalidades *d, char *nome);
int quantModalidades(Modalidades *d);
void listarModalidades(Modalidades *d);
int removerModalidade(Modalidades *d, char *nome);
void altNomeModalidade(Modalidades *d, char *nomeAnt, char *nomeNovo);
void buscarModalidade(Modalidades *d, char *nome);
int inserirEquipe(NoEquipes *no, char *modal, Modalidades *d);
int carregarModalidadesArquivo(Modalidades *d, char *nomeArquivo);
void removerEquipe(Modalidades *d, char *nomeEq, char *nomeMod);
int quantEquipes(Modalidades *d, char *nomeMod);
int inserirEquipe(NoEquipes *no, char *modal, Modalidades *d);
void listarEquipes(Modalidades *d, char *nome);
#endif