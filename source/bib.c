#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib.h"
#include <locale.h>

struct modalidades
{
    struct noModalidades *inicio;
    int quantidade;
};

struct noModalidades
{
    char nome[50];
    struct noModalidades *prox;
    struct noModalidades *ant;
    struct NoEquipes *inicio;
    int quantidade;
};

struct noEquipes
{
    char nome[50], cidade[50];
    int ano, titulos;
    struct noEquipes *prox;
    struct noEquipes *ant;
};

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
    (*novo)->inicio = NULL; // Já inicializa a lista vazia das equipes desta modalidade
    return 0;               // Sucesso
}

int inserirModalidade(Modalidades *d, char *nome)
{
    NoModalidades *novo;
    if (criarNoModalidades(&novo))
        return 1; // falha

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
    return 0; // sucesso
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
        printf("\n%s\n", atual->nome);
        atual = atual->prox;
    }
    printf("\n===================\n");
}

int removerModalidade(Modalidades *d, char *nome)
{
    if (d == NULL || d->inicio == NULL)
    {
        return 1; // lista vazia
    }

    NoModalidades *atual = d->inicio;

    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        return -1; // modalidade inexistente
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

    free(atual);
    d->quantidade--;

    return 0; // removido com sucesso
}

void altNomeModalidade(Modalidades *d, char *nomeAnt, char *nomeNovo)
{
    if (d->quantidade == 0)
    {
        printf("\nLista vazia.\n");
    }
    NoModalidades *atual = d->inicio;
    int k = 0;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nomeAnt) == 0)
        {
            k = 1;
            break;
        }
        else
        {
            atual = atual->prox;
        }
    }

    if (k)
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
            printf("\nModalidade encontrada!\n");
            return;
        }
        atual = atual->prox;
    }
    printf("\nModalidade inexistente.\n");
}

int criarNoEquipes(NoEquipes **novo)
{
    *novo = (NoEquipes *)malloc(sizeof(NoEquipes));
    if (*novo == NULL)
        return 1; // falha na alocacao

    (*novo)->prox = NULL;
    (*novo)->ant = NULL;
    return 0; // Sucesso
}

int inserirEquipe(NoEquipes *no, char *modal, Modalidades *d)
{
    NoEquipes *novo;
    if (criarNoEquipes(&novo))
        return 1; // falha

    novo->ano = no->ano;
    novo->titulos = no->titulos;
    strcpy(novo->nome, no->nome);
    strcpy(novo->cidade, no->cidade);

    NoModalidades *atual = d->inicio;
    if (d->quantidade != 0)
    {
        while (atual != NULL)
        {
            if (strcmp(modal, atual->nome) == 0)
            {
                if (atual->quantidade == 0)
                {
                    atual->inicio = novo;
                }
                else
                {
                    novo->prox = atual->inicio;
                    novo->prox->ant = novo;
                    atual->inicio = novo;
                }
            }
            else
            {
                atual = atual->prox;
            }
        }
    }
    else
    {
        return -1; // lista vazia
    }
    atual->quantidade++;
    return 0; // sucesso
}

int carregarModalidadesArquivo(Modalidades *d, char *nomeArquivo)
{
    FILE *arquivo;
    char nome[50];

    if (d == NULL)
    {
        return 1; // lista invalida
    }

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        return 2; // erro ao abrir arquivo
    }

    while (fgets(nome, 50, arquivo) != NULL)
    {
        nome[strcspn(nome, "\n")] = '\0';

        if (strlen(nome) > 0)
        {
            inserirModalidade(d, nome);
        }
    }

    fclose(arquivo);

    return 0; // sucesso
}

int quantEquipes(Modalidades *d, char *nomeMod)
{
    if (d->quantidade == 0)
        return 1; // Lista vazia

    NoModalidades *atual = d->inicio;
    int k = 0;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nomeMod) == 0)
        {
            k = 1;
            break;
        }
        else
        {
            atual = atual->prox;
        }
    }

    if (k)
    {
        return atual->quantidade;
    }
    else
    {
        return -1; // Modalidade inexistente
    }
}

void removerEquipe(Modalidades *d, char *nomeEq, char *nomeMod)
{
    if (d->quantidade == 0)
        printf("\nLista vazia.\n");

    NoModalidades *atual = d->inicio;
    while (atual != NULL && strcmp(atual->nome, nomeMod) != 0)
    {
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("Modalidade inexistente.");
    }
    else
    {
        if (atual->quantidade == 0)
            printf("\nSem equipes nessa modalidade.\n");
        NoEquipes *atualEQ = atual->inicio;
        while (atualEQ != NULL && strcmp(atualEQ->nome, nomeEq) != 0)
        {
            atualEQ = atualEQ->prox;
        }
        if (atualEQ == NULL)
            printf("\nEquipe inexistente.\n");

        if (atualEQ->ant == NULL)
        {
            atual->inicio = atualEQ->prox;
        }
        else
        {
            atualEQ->ant->prox = atualEQ->prox;
        }

        if (atualEQ->prox != NULL)
        {
            atualEQ->prox->ant = atualEQ->ant;
        }

        free(atualEQ);
        atual->quantidade--;

        printf("\nEquipe removida com sucesso.\n");
    }
}

void listarEquipes(Modalidades *d, char *nome)
{
    setlocale(LC_ALL, "");
    NoModalidades *atual = d->inicio;
    int i = 1;

    if (d->quantidade != 0)
    {
        while (atual != NULL)
        {
            if (strcmp(atual->nome, nome))
            {
                if (atual->quantidade != 0)
                {
                    NoEquipes *atual2 = atual->inicio;
                    while (atual2 != NULL)
                    {
                        printf("\nEquipe %d: %s.", i, atual2->nome);
                        i++;
                        atual2 = atual2->prox;
                    }
                }
                else
                    printf("\nNão há equipes nesta modalidade.\n");
            }
            else
                printf("\nEsta modalidade não existe.\n");
            atual = atual->prox;
        }
    }
    else
        printf("\nAinda não há nenhuma modalidade.\n");
}