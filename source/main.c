#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "bib.h"

int main()
{
    setlocale(LC_ALL, "");

    Modalidades *lista = NULL;
    inicializarListaP(&lista);
    if (lista == NULL) {
        return 1;
    }
    carregarArquivo(lista, "arq.txt");



    return 0;
}