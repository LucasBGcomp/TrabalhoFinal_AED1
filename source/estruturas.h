#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct modalidades Modalidades;
typedef struct noModalidades NoModalidades;
typedef struct noEquipes NoEquipes;

struct modalidades
{
    NoModalidades *inicio;
    int quantidade;
};

struct noModalidades
{
    char nome[50];
    NoModalidades *prox;
    NoModalidades *ant;
    NoEquipes *inicio;
    int quantidade;
};

struct noEquipes
{
    char nome[50], cidade[50];
    int ano, titulos;
    NoEquipes *prox;
    NoEquipes *ant;
};

#endif