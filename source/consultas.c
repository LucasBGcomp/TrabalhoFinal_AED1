#include <stdio.h>
#include <string.h>
#include "consultas.h"
#include "equipes.h"

void contabilizarEquipesPorModalidade(Modalidades *d)
{
    if (d == NULL || d->inicio == NULL)
    {
        printf("\nNao existem modalidades cadastradas.\n");
        return;
    }

    NoModalidades *atual = d->inicio;

    printf("\n==== QUANTIDADE DE EQUIPES POR MODALIDADE ====\n");

    while (atual != NULL)
    {
        printf("\nModalidade: %s", atual->nome);
        printf("\nQuantidade de equipes: %d\n", atual->quantidade);

        atual = atual->prox;
    }

    printf("\n==============================================\n");
}

int ehPrimeiraOcorrencia(Modalidades *d, NoModalidades *modLimite, NoEquipes *eqLimite, char *nome, int op)
{
    NoModalidades *atual = d->inicio;
    while (atual != NULL)
    {
        NoEquipes *atualEq = atual->inicio;
        while (atualEq != NULL)
        {
            if (atual == modLimite && atualEq == eqLimite) // Se chegou no limite atualEq nao encontrou nenhuma eh porque eh a primeira ocorrencia dessa equipe
            {
                return 1;
            }
            if (op)
            {
                if (strcmp(atualEq->nome, nome) == 0)
                {
                    return 0;
                }
            }
            else
            {
                if (strcmp(atualEq->cidade, nome) == 0)
                {
                    return 0;
                }
            }
            atualEq = atualEq->prox;
        }
        atual = atual->prox;
    }
    return 1;
}

void identificarEquipesMultiModalidade(Modalidades *d)
{
    if (d == NULL || d->quantidade == 0)
    {
        printf("\nAinda nao ha nenhuma modalidade cadastrada.\n");
        return;
    }

    int encontrouAlguma = 0;
    NoModalidades *atual = d->inicio;

    while (atual != NULL)
    {
        NoEquipes *atualEq = atual->inicio;

        while (atualEq != NULL)
        {
            if (ehPrimeiraOcorrencia(d, atual, atualEq, atualEq->nome, 1))
            {
                int contModalidades = 0;
                NoModalidades *modBusca = d->inicio;

                while (modBusca != NULL)
                {
                    NoEquipes *eqBusca = modBusca->inicio;
                    while (eqBusca != NULL)
                    {
                        if (strcmp(eqBusca->nome, atualEq->nome) == 0)
                        {
                            contModalidades++; // Conta quantas vezes a equipe apareceS
                            break;
                        }
                        eqBusca = eqBusca->prox;
                    }
                    modBusca = modBusca->prox;
                }

                if (contModalidades > 1) // Se a equipe aparece mais de uma vez
                {
                    printf("\nEquipe \"%s\" esta associada a %d modalidades diferentes.\n", atualEq->nome, contModalidades);
                    encontrouAlguma = 1;
                }
            }

            atualEq = atualEq->prox;
        }
        atual = atual->prox;
    }

    if (!encontrouAlguma) // Se nenhuma equipe se repete
    {
        printf("\nNenhuma equipe esta associada a mais de uma modalidade.\n");
    }
}

void gerarRelatorio(Modalidades *d)
{
    if (d == NULL || d->quantidade == 0)
    {
        printf("\nNao ha modalidades cadastradas ainda.\n");
        return;
    }

    printf("\n=========== RELATORIO GERAL ===========\n");

    // Numero de modalidades
    printf("\nModalidades cadastradas: %d", d->quantidade);

    // Numero total de equipes (soma de todas as modalidades)
    printf("\nEquipes cadastradas: %d\n", quantEquipes(d));

    NoEquipes *equipeMaisVelha = NULL;
    NoEquipes *equipeMaisNova = NULL;
    NoEquipes *equipeMaisTitulos = NULL;
    NoModalidades *modalidadeMaisEquipes = NULL;
    NoModalidades *modalidadeMenosEquipes = NULL;

    // guarda a modalidade correspondente de cada equipe extrema
    NoModalidades *modDaMaisVelha = NULL;
    NoModalidades *modDaMaisNova = NULL;
    NoModalidades *modDaMaisTitulos = NULL;

    NoModalidades *atual = d->inicio;
    while (atual != NULL)
    {
        if (modalidadeMaisEquipes == NULL || atual->quantidade > modalidadeMaisEquipes->quantidade)
            modalidadeMaisEquipes = atual;

        if (modalidadeMenosEquipes == NULL || atual->quantidade < modalidadeMenosEquipes->quantidade)
            modalidadeMenosEquipes = atual;

        NoEquipes *atualEq = atual->inicio;
        while (atualEq != NULL)
        {
            if (equipeMaisVelha == NULL || atualEq->ano < equipeMaisVelha->ano)
            {
                equipeMaisVelha = atualEq;
                modDaMaisVelha = atual;
            }

            if (equipeMaisNova == NULL || atualEq->ano > equipeMaisNova->ano)
            {
                equipeMaisNova = atualEq;
                modDaMaisNova = atual;
            }

            if (equipeMaisTitulos == NULL || atualEq->titulos > equipeMaisTitulos->titulos)
            {
                equipeMaisTitulos = atualEq;
                modDaMaisTitulos = atual;
            }

            atualEq = atualEq->prox;
        }
        atual = atual->prox;
    }

    if (equipeMaisVelha != NULL)
        printf("\nEquipe mais antiga: %s (fundada em %d, modalidade: %s)", equipeMaisVelha->nome, equipeMaisVelha->ano, modDaMaisVelha->nome);

    if (equipeMaisNova != NULL)
        printf("\nEquipe mais nova: %s (fundada em %d, modalidade: %s)", equipeMaisNova->nome, equipeMaisNova->ano, modDaMaisNova->nome);

    if (equipeMaisTitulos != NULL)
        printf("\nEquipe com mais titulos: %s (%d titulos, modalidade: %s)", equipeMaisTitulos->nome, equipeMaisTitulos->titulos, modDaMaisTitulos->nome);

    if (modalidadeMaisEquipes != NULL)
        printf("\nModalidade com mais equipes: %s (%d equipes)", modalidadeMaisEquipes->nome, modalidadeMaisEquipes->quantidade);

    if (modalidadeMenosEquipes != NULL)
        printf("\nModalidade com menos equipes: %s (%d equipes)", modalidadeMenosEquipes->nome, modalidadeMenosEquipes->quantidade);

    // Equipe com mais aparicoes em modalidades diferentes
    NoEquipes *equipeMaisFrequente = NULL;
    int maiorContagem = 0;

    atual = d->inicio;
    while (atual != NULL)
    {
        NoEquipes *atualEq = atual->inicio;
        while (atualEq != NULL)
        {
            if (ehPrimeiraOcorrencia(d, atual, atualEq, atualEq->nome, 1))
            {
                int contModalidades = 0;
                NoModalidades *modBusca = d->inicio;
                while (modBusca != NULL)
                {
                    NoEquipes *eqBusca = modBusca->inicio;
                    while (eqBusca != NULL)
                    {
                        if (strcmp(eqBusca->nome, atualEq->nome) == 0)
                        {
                            contModalidades++;
                            break;
                        }
                        eqBusca = eqBusca->prox;
                    }
                    modBusca = modBusca->prox;
                }

                if (contModalidades > maiorContagem)
                {
                    maiorContagem = contModalidades;
                    equipeMaisFrequente = atualEq;
                }
            }
            atualEq = atualEq->prox;
        }
        atual = atual->prox;
    }

    if (equipeMaisFrequente != NULL && maiorContagem > 1)
        printf("\nEquipe com mais aparicoes em modalidades diferentes: %s (%d modalidades)", equipeMaisFrequente->nome, maiorContagem);
    else
        printf("\nNenhuma equipe aparece em mais de uma modalidade.");

    // Listar modalidades cadastradas
    printf("\n\nModalidades cadastradas:");
    atual = d->inicio;
    while (atual != NULL)
    {
        printf("\n  - %s", atual->nome);
        atual = atual->prox;
    }

    // Listar cidades das equipes, sem repeticao
    printf("\n\nCidades de origem das equipes:");
    atual = d->inicio;
    while (atual != NULL)
    {
        NoEquipes *atualEq = atual->inicio;
        while (atualEq != NULL)
        {
            if (ehPrimeiraOcorrencia(d, atual, atualEq, atualEq->cidade, 0))
            {
                printf("\n  - %s", atualEq->cidade);
            }
            atualEq = atualEq->prox;
        }
        atual = atual->prox;
    }

    printf("\n\n========================================\n");
}

void filtarEquipesPorTitulo(Modalidades *d, int titulos)
{
    if (d == NULL || d->quantidade == 0)
    {
        printf("\nNao ha modalidades cadastradas ainda.\n");
        return;
    }

    NoModalidades *atual = d->inicio;
    NoEquipes *atualEq;
    int acc = 0;

    printf("\nEquipe(s) com %d titulos:\n", titulos);
    while (atual != NULL)
    {
        atualEq = atual->inicio;
        while (atualEq != NULL)
        {
            if (atualEq->titulos == titulos)
            {
                acc++;
                printf("\n-  %s (%s)", atualEq->nome, atual->nome);
            }
            atualEq = atualEq->prox;
        }
        atual = atual->prox;
    }
    if (acc == 0)
    {
        printf("\nNao encontrada!");
    }
    printf("\n");
}