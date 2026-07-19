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
        case 1: {
            char nomeMod[50];
            printf("\nDigite o nome da modalidade: ");
            scanf(" %49[^\n]", nomeMod);
            setbuf(stdin, NULL);
            inserirModalidade(lista, nomeMod);
            break;
        }
        case 2: {
            char nomeMod[50], nomeEq[50], cidade[50];
            int ano, titulos;
            printf("\nDigite o nome da modalidade da equipe: ");
            scanf(" %49[^\n]", nomeMod);
            setbuf(stdin, NULL);
            printf("\nDigite o nome da equipe: ");
            scanf(" %49[^\n]", nomeEq);
            setbuf(stdin, NULL);
            printf("\nDigite o nome da cidade de fundação da equipe: ");
            scanf(" %49[^\n]", cidade);
            setbuf(stdin, NULL);
            printf("\nDigite o ano de fundação da equipe: ");
            scanf("%d", &ano);
            printf("\nDigite o número de títulos da equipe: ");
            scanf("%d", &titulos);
            inserirEquipe(lista, nomeMod, nomeEq, cidade, ano, titulos);
            break;
        }
        case 3:
            listarModalidades(lista);
            break;
        case 4: {
            char nomeMod[50];
            printf("\nDigite o nome da modalidade: ");
            scanf(" %49[^\n]", nomeMod);
            setbuf(stdin, NULL);
            listarEquipes(lista, nomeMod);
            break;
        }
        case 5: {
            char nomeMod[50];
            printf("\nDigite o nome da modalidade a ser removida: ");
            scanf(" %49[^\n]", nomeMod);
            setbuf(stdin, NULL);
            removerModalidade(lista, nomeMod);
            break;
        }
        case 6: {
            char nomeMod[50], nomeEq[50];
            printf("\nDigite o nome da modalidade da equipe a ser removida: ");
            scanf(" %49[^\n]", nomeMod);
            setbuf(stdin, NULL);
            printf("\nDigite o nome da equipe a ser removida: ");
            scanf(" %49[^\n]", nomeEq);
            setbuf(stdin, NULL);
            removerEquipe(lista, nomeEq, nomeMod);
            break;
        }
        case 7: {
            char nomeMod[50];
            printf("\nDigite o nome da modalidade: ");
            scanf(" %49[^\n]", nomeMod);
            setbuf(stdin, NULL);
            buscarModalidade(lista, nomeMod);
            break;
        }
        case 8: {
            char nomeMod[50], nomeEq[50];
            printf("\nDigite o nome da modalidade: ");
            scanf(" %49[^\n]", nomeMod);
            setbuf(stdin, NULL);
            printf("\nDigite o nome da equipe: ");
            scanf(" %49[^\n]", nomeEq);
            setbuf(stdin, NULL);
            buscaEquipe(lista, nomeMod, nomeEq);
            break;
        }
        case 9: {
            char nomeAnt[50], nomeNovo[50];
            printf("\nDigite o nome da modalidade: ");
            scanf(" %49[^\n]", nomeAnt);
            setbuf(stdin, NULL);
            printf("\nDigite o novo nome da modalidade: ");
            scanf(" %49[^\n]", nomeNovo);
            setbuf(stdin, NULL);
            altNomeModalidade(lista, nomeAnt, nomeNovo);
            break;
        }
        case 10: {
            char nomeMod[50], nomeEq[50];
            printf("\nDigite o nome da modalidade: ");
            scanf(" %49[^\n]", nomeMod);
            setbuf(stdin, NULL);
            printf("\nDigite o nome da equipe: ");
            scanf(" %49[^\n]", nomeEq);
            setbuf(stdin, NULL);
            altDadoEquipe(lista, nomeMod, nomeEq);
            break;
        }
        case 11:
            printf("\nNúmero de modalidades cadastradas: %d\n", quantModalidades(lista));
            break;
        case 12:
            printf("\nNúmero de equipes cadastradas: %d\n", quantEquipes(lista));
            break;
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