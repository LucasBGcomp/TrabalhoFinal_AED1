#ifndef EQUIPES_H
#define EQUIPES_H

#include "estruturas.h"

void inserirEquipe(Modalidades *d, char *modal, char *nome, char *cidade, int ano, int titulos);
void removerEquipe(Modalidades *d, char *nomeEq, char *nomeMod);
int quantEquipes(Modalidades *d);
void listarEquipes(Modalidades *d, char *nome);
void altDadoEquipe(Modalidades *d, char *nome, char *nome2);
void buscaEquipe(Modalidades *d, char *nome, char *nome2);
void ordEquipesAno(Modalidades *d, int ord);
void liberarEquipes(NoEquipes *inicio);

#endif