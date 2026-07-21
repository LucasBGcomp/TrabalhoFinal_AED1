#ifndef MODALIDADES_H
#define MODALIDADES_H

#include "estruturas.h"

void inicializarListaP(Modalidades **d);
void inserirModalidade(Modalidades *d, char *nome);
int quantModalidades(Modalidades *d);
void listarModalidades(Modalidades *d);
void removerModalidade(Modalidades *d, char *nome);
void altNomeModalidade(Modalidades *d, char *nomeAnt, char *nomeNovo);
void buscarModalidade(Modalidades *d, char *nome);
void liberarLista(Modalidades **d);

#endif