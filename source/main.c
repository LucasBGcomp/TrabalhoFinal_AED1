#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "bib.h"

int main()
{
    setlocale(LC_ALL, "");

    Modalidades *lista = NULL;
    inicializarListaP(&lista);
    if (lista == NULL)
    {
        return 1;
    }
    carregarArquivo(lista, "arq.txt");
    int opcao;

    do
    {
        printf("\n========= MENU =========\n");
        printf("\n01. Inserir Modalidade");
        printf("\n02. Inserir Equipe");
        printf("\n03. Listar Modalidades");
        printf("\n04. Listar Equipes");
        printf("\n05. Remover Modalidade");
        printf("\n06. Remover Equipe");
        printf("\n07. Buscar Modalidade");
        printf("\n08. Buscar Equipe");
        printf("\n09. Alterar nome de Modalidade");
        printf("\n10. Alterar dados de Equipe");
        printf("\n11. Quantidade de Modalidades");
        printf("\n12. Quantidade de Equipes");
        printf("\n13. Operações de Consulta");
        printf("\n0. Sair");
        printf("\n\nOpção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        {
            int opcao2;
            do
            {
                printf("\n======== OPERAÇÕES DE CONSULTA ========\n");
                printf("\n1. Ordenar Equipes por Ano");
                printf("\n2. Número de Equipes por Modalidade");
                printf("\n3. Equipes Multimodalidade");
                printf("\n4. Filtrar Equipes por Títulos");
                printf("\n5. Gerar Relatório");
                printf("\n0. Voltar");
                printf("\n\nOpção: ");
                scanf("%d", &opcao2);

                switch (opcao2)
                {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 0:
                    break;
                default:
                    printf("\nOpção Inválida!\n");
                }
            } while (opcao2 != 0);
        }
        case 0:
            break;
        default:
            printf("\nOpção Inválida!\n");
        }
    } while (opcao != 0);

    liberarLista(&lista);
    system("pause");
    return 0;
}