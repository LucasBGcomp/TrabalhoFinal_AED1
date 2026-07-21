#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipes.h"

typedef struct noEquipesfunc
{
    char nome[65];
    int ano;
} NoEquipesfunc;

void liberarEquipes(NoEquipes *inicio)
{
    NoEquipes *atual = inicio;
    NoEquipes *proximo;

    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
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

void inserirEquipe(Modalidades *d, char *modal, char *nome, char *cidade, int ano, int titulos)
{
    NoEquipes *novo;
    if (criarNoEquipes(&novo))
    {
        printf("\nErro!\n");
        return;
    }

    novo->ano = ano;
    novo->titulos = titulos;
    strcpy(novo->nome, nome);
    strcpy(novo->cidade, cidade);

    int achou = 0;
    NoModalidades *atual = d->inicio;
    if (d->quantidade != 0)
    {
        while (atual != NULL)
        {
            if (strcmp(modal, atual->nome) == 0)
            {
                achou = 1;
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
                break;
            }
            else
            {
                atual = atual->prox;
            }
        }
    }
    else
    {
        printf("\nLista vazia!\n");
        return;
    }
    if (achou == 1)
    {
        atual->quantidade++;
        return;
    }
    else
    {
        printf("\nModalidade inexistente!\n");
        return;
    }
}

int quantEquipes(Modalidades *d)
{
    if (d->quantidade == 0)
        return 1; // Lista vazia

    NoModalidades *atual = d->inicio;
    int acc = 0;
    while (atual != NULL)
    {
        acc += atual->quantidade;
        atual = atual->prox;
    }
    return acc;
}

void removerEquipe(Modalidades *d, char *nomeEq, char *nomeMod)
{
    if (d->quantidade == 0)
    {
        printf("\nLista vazia.\n");
        return;
    }

    NoModalidades *atual = d->inicio;
    while (atual != NULL && strcmp(atual->nome, nomeMod) != 0)
    {
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("\nModalidade inexistente.\n");
        return;
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
        {
            printf("\nEquipe inexistente.\n");
            return;
        }

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
    if (d->quantidade == 0)
    {
        printf("\nLista vazia.\n");
        return;
    }

    NoModalidades *atual = d->inicio;
    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("\nEssa modalidade nao existe.\n");
        return;
    }

    if (atual->quantidade == 0)
    {
        printf("\nNao ha equipes nesta modalidade.\n");
        return;
    }

    int i = 1;
    NoEquipes *atual2 = atual->inicio;
    while (atual2 != NULL)
    {
        printf("\nEquipe %d: %s", i, atual2->nome);
        printf("\n  - Cidade de origem: %s", atual2->cidade);
        printf("\n  - Ano de fundacao: %d", atual2->ano);
        printf("\n  - Titulos: %d", atual2->titulos);
        i++;
        atual2 = atual2->prox;
    }
    printf("\n");
}

void altDadoEquipe(Modalidades *d, char *nome, char *nome2)
{
    NoModalidades *atual = d->inicio;

    if (d->quantidade != 0)
    {
        while (atual != NULL && (strcmp(atual->nome, nome)))
        {
            atual = atual->prox;
        }
    }
    if (atual == NULL)
    {
        printf("\nEssa modalidade nao esta registrada.\n");
        return;
    }

    if (atual->quantidade == 0)
        return;

    NoEquipes *atual2 = atual->inicio;
    while (atual2 != NULL && (strcmp(atual2->nome, nome2)))
    {
        atual2 = atual2->prox;
    }
    if (atual2 == NULL)
    {
        printf("\nEssa equipe nao esta registrada nesta modalidade.\n");
        return;
    }

    int opcao;
    do
    {
        printf("\nQual dado desta equipe voce deseja alterar?\n");
        printf("\n1: Nome");
        printf("\n2: Cidade de origem");
        printf("\n3: Ano de fundacao");
        printf("\n4: Quantidade de titulos");
        printf("\n0: Encerrar\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
        {
            char novoNome[50];
            printf("\nDigite o novo nome da equipe: ");
            scanf(" %49[^\n]", novoNome);
            strcpy(atual2->nome, novoNome);
            break;
        }
        case 2:
        {
            char novaCidade[50];
            printf("\nDigite a nova cidade de origem da equipe: ");
            scanf(" %49[^\n]", novaCidade);
            strcpy(atual2->cidade, novaCidade);
            break;
        }
        case 3:
        {
            int novoAno;
            printf("\nDigite o novo ano de fundacao da equipe: ");
            scanf("%d", &novoAno);
            atual2->ano = novoAno;
            break;
        }
        case 4:
        {
            int novaQuant;
            printf("\nAltere a quantidade de titulos da equipe: ");
            scanf("%d", &novaQuant);
            atual2->titulos = novaQuant;
            break;
        }
        case 0:
            break;
        default:
            printf("\nOpcao invalida!\n");
            break;
        }
    } while (opcao != 0);
}

void buscaEquipe(Modalidades *d, char *nome, char *nome2)
{
    NoModalidades *atual = d->inicio;

    if (d->quantidade != 0)
    {
        while (atual != NULL && (strcmp(atual->nome, nome) != 0))
        {
            atual = atual->prox;
        }
    }
    if (atual == NULL)
    {
        printf("\nModalidade nao cadastrada!\n");
        return;
    }

    if (atual->quantidade == 0)
        return;

    NoEquipes *atual2 = atual->inicio;
    while (atual2 != NULL && (strcmp(atual2->nome, nome2) != 0))
    {
        atual2 = atual2->prox;
    }
    if (atual2 == NULL)
    {
        printf("\nEssa equipe nao esta registrada nesta modalidade.\n");
        return;
    }

    printf("\nInformacoes da equipe: ");
    printf("\n  Nome: %s", atual2->nome);
    printf("\n  Cidade de origem: %s", atual2->cidade);
    printf("\n  Ano de fundacao: %d", atual2->ano);
    printf("\n  Quantidade de titulos: %d\n", atual2->titulos);
}

void bubbleSort(NoEquipesfunc eqs[], int tam) // Ordena as equipes das mais velhas para as mais novas
{
    for (int i = 0; i < tam - 1; i++)
    {
        for (int j = 0; j < tam - 1 - i; j++)
        {
            if (eqs[j].ano > eqs[j + 1].ano)
            {
                // Troca as structs inteiras (nome + ano)
                NoEquipesfunc temp = eqs[j];
                eqs[j] = eqs[j + 1];
                eqs[j + 1] = temp;
            }
        }
    }
}

void inverterArray(NoEquipesfunc eqs[], int tam) // Para ordenacao decrescente
{
    for (int i = 0; i < tam / 2; i++)
    {
        NoEquipesfunc temp = eqs[i];
        eqs[i] = eqs[tam - 1 - i];
        eqs[tam - 1 - i] = temp;
    }
}

void ordEquipesAno(Modalidades *d, int ord) // ord = 1 -> Crescente   ord = 2 -> Decrescente
{
    int tam = quantEquipes(d);
    int i = 0;

    if (d->quantidade == 0)
    {
        printf("\nLista vazia!\n");
        return;
    }

    if (tam == 0)
    {
        printf("\nSem equipes cadastradas!\n");
        return;
    }

    NoEquipesfunc eqs[tam];
    NoModalidades *atual = d->inicio;
    while (atual != NULL)
    {
        NoEquipes *atualEq = atual->inicio;
        while (atualEq != NULL)
        {
            NoEquipesfunc equipe;
            strcpy(equipe.nome, atualEq->nome);
            strcat(equipe.nome, " ");
            strcat(equipe.nome, atual->nome);
            equipe.ano = atualEq->ano;
            eqs[i] = equipe;
            i++;
            atualEq = atualEq->prox;
        }
        atual = atual->prox;
    }

    bubbleSort(eqs, tam);

    if (ord == 2)
    {
        inverterArray(eqs, tam);
    }

    for (int j = 0; j < tam; j++)
    {
        printf("\n%d. %s (%d)", j + 1, eqs[j].nome, eqs[j].ano);
    }
    printf("\n");
}