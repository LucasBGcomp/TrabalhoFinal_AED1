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
int carregarModalidadesArquivo(Modalidades *d, char *nomeArquivo);
int inserirEquipe(NoEquipes *no, char *modal, Modalidades *d);
void removerEquipe(Modalidades *d, char *nomeEq, char *nomeMod);
int quantEquipes(Modalidades *d);
void listarEquipes(Modalidades *d, char *nome);
void altDadoEquipe(Modalidades *d, char *nome, char *nome2);
void buscaEquipe(Modalidades *d, char *nome, char *nome2);
void ordEquipesAno(Modalidades *d, int ord);
void contabilizarEquipesPorModalidade(Modalidades *d);
#endif