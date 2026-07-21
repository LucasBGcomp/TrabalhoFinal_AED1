#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modalidades.h"
#include "equipes.h"

void inicializarListaP(Modalidades **d)
{
    *d = (Modalidades *)malloc(sizeof(Modalidades));
    if (*d == NULL)
        return;
    (*d)->inicio = NULL;
    (*d)->quantidade = 0;
}

int criarNoModalidades(NoModalidades **novo)
{
    *novo = (NoModalidades *)malloc(sizeof(NoModalidades));
    if (*novo == NULL)
        return 1; // falha na alocacao

    (*novo)->prox = NULL;
    (*novo)->ant = NULL;
    (*novo)->inicio = NULL;
    (*novo)->quantidade = 0;
    return 0; // Sucesso
}

void inserirModalidade(Modalidades *d, char *nome)
{
    NoModalidades *novo;
    if (criarNoModalidades(&novo))
    {
        printf("\nErro!\n");
        return;
    }

    strcpy(novo->nome, nome);

    if (d->quantidade == 0)
    {
        d->inicio = novo;
    }
    else
    {
        novo->prox = d->inicio;
        d->inicio->ant = novo;
        d->inicio = novo;
    }
    d->quantidade++;
}

int quantModalidades(Modalidades *d)
{
    return d->quantidade;
}

void listarModalidades(Modalidades *d)
{
    if (d->quantidade == 0)
    {
        printf("\nLista vazia\n");
    }

    NoModalidades *atual = d->inicio;

    printf("\n====MODALIDADES====\n");
    while (atual != NULL)
    {
        printf("\n%s", atual->nome);
        atual = atual->prox;
    }
    printf("\n\n===================\n");
}

void removerModalidade(Modalidades *d, char *nome)
{
    if (d == NULL || d->inicio == NULL)
    {
        printf("\nLista vazia!\n");
        return;
    }

    NoModalidades *atual = d->inicio;

    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("\nModalidade inexistente!\n");
        return;
    }

    if (atual->ant == NULL)
    {
        d->inicio = atual->prox;
    }
    else
    {
        atual->ant->prox = atual->prox;
    }

    if (atual->prox != NULL)
    {
        atual->prox->ant = atual->ant;
    }

    liberarEquipes(atual->inicio);
    free(atual);
    d->quantidade--;

    printf("\nModalidade removida!\n");
}

void altNomeModalidade(Modalidades *d, char *nomeAnt, char *nomeNovo)
{
    if (d->quantidade == 0)
    {
        printf("\nLista vazia.\n");
    }
    NoModalidades *atual = d->inicio;
    int achou = 0;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nomeAnt) == 0)
        {
            achou = 1;
            break;
        }
        else
        {
            atual = atual->prox;
        }
    }

    if (achou)
    {
        strcpy(atual->nome, nomeNovo);
        printf("\nNome alterado!\n");
    }
    else
    {
        printf("\nModalidade inexistente.\n");
    }
}

void buscarModalidade(Modalidades *d, char *nome)
{
    if (d->quantidade == 0)
        printf("\nLista vazia.\n");

    NoModalidades *atual = d->inicio;
    while (atual != NULL)
    {
        if (strcmp(nome, atual->nome) == 0)
        {
            printf("\nModalidade cadastrada!\n");
            return;
        }
        atual = atual->prox;
    }
    printf("\nModalidade nao cadastrada!\n");
}

void liberarLista(Modalidades **d)
{
    if (d == NULL || *d == NULL)
    {
        return;
    }

    NoModalidades *atual = (*d)->inicio;
    NoModalidades *proximo;

    while (atual != NULL)
    {
        proximo = atual->prox;
        liberarEquipes(atual->inicio);
        free(atual);
        atual = proximo;
    }

    free(*d);
    *d = NULL;
}