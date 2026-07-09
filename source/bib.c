#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib.h"

struct modalidades {
    struct noModalidades *inicio;
    struct noModalidades *fim;
    int quantidade;
};

struct equipes {
    struct noEquipes *inicio;
    struct noEquipes *fim;
    int quantidade;
};

struct noModalidades {
    char nome[50];
    struct noModalidades *prox;
    struct noModalidades *ant;
    struct equipes *eq;
};

struct noEquipes {
    char nome[50], cidade[50];
    int ano, titulos;
    struct noEquipes *prox;
    struct noEquipes *ant;
};