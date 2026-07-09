#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib.h"
#include <locale.h>

struct modalidades {
    struct noModalidades *inicio;
    int quantidade;
};

struct equipes {
    struct noEquipes *inicio;
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

void inicializarListaP(Modalidades **d) {
    *d = (Modalidades *) malloc(sizeof(Modalidades));
    if (*d == NULL) return;
    (*d)->inicio = NULL;
    (*d)->quantidade = 0;
}

int criarNoModalidades(NoModalidades **novo) {
    *novo = (NoModalidades *) malloc(sizeof(NoModalidades));
    if (*novo == NULL) return 1; // falha na alocaï¿½ï¿½o

    (*novo)->prox = NULL;
    (*novo)->ant = NULL;
    return 0; // Sucesso
}

int inserirModalidade(Modalidades *d, char *nome) {
    NoModalidades *novo;
    if (criarNoModalidades(&novo)) return 1; //falha

    strcpy(novo->nome, nome);

    if (d->quantidade == 0) {
        d->inicio = novo;
    } else {
        novo->prox = d->inicio;
        d->inicio->ant = novo;
        d->inicio = novo;
    }
    d->quantidade++;
    return 0; //sucesso
}

int quantModalidades(Modalidades *d) {
    return d->quantidade;
}

void listarModalidades(Modalidades *d) {
    if (d->quantidade == 0) {
        printf("\nLista vazia\n");
    }

    NoModalidades *atual = d->inicio;

    printf("\n====MODALIDADES====\n");
    while (atual != NULL) {
        printf("\n%s\n", atual->nome);
        atual = atual->prox;
    }
    printf("\n===================\n");
}

int removerModalidade(Modalidades *d, char *nome) {
    if (d == NULL || d->inicio == NULL) {
        return 1; // lista vazia
    }

    NoModalidades *atual = d->inicio;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        return 1; // modalidade nao encontrada
    }

    if (atual->ant == NULL) {
        d->inicio = atual->prox;
    } else {
        atual->ant->prox = atual->prox;
    }

    if (atual->prox != NULL) {
        atual->prox->ant = atual->ant;
    }

    free(atual);
    d->quantidade--;

    return 0; // removido com sucesso
}


void altNomeModalidade(Modalidades *d, char *nomeAnt, char *nomeNovo) {
    if (d->quantidade == 0) {
        printf("\nLista vazia\n");
    }
    NoModalidades *atual = d->inicio;
    int k = 0;

    while (atual != NULL) {
        if (strcmp(atual->nome, nomeAnt) == 0) {
            k = 1;
            break;
        } else {
            atual = atual->prox;
        }
    }

    if (k) {
        strcpy(atual->nome, nomeNovo);
        printf("\nNome alterado!\n");
    } else {
        printf("\nModalidade nï¿½o encontrada!\n");
    }
}

void buscarModalidade(Modalidades *d, char *nome) {
    setlocale(LC_ALL, "");
    NoModalidades *atual = d->inicio;

    if (d->quantidade == 0) printf("Não há elementos na lista.\n");
    else {
        while (atual != NULL) {
            if(strcmp(nome, atual->nome)) {
                printf("Modalidade %s: ", nome);
                //LISTAR AQUI AS EQUIPES DESTA MODALIDADE!
            }
            atual = atual->prox;
        }
    }
}