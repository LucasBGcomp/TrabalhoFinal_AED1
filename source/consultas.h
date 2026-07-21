#ifndef CONSULTAS_H
#define CONSULTAS_H

#include "estruturas.h"

void contabilizarEquipesPorModalidade(Modalidades *d);
void identificarEquipesMultiModalidade(Modalidades *d);
void gerarRelatorio(Modalidades *d);
void filtarEquipesPorTitulo(Modalidades *d, int titulos);

#endif