#include <stdio.h>
#include <string.h>
#include "arquivo.h"
#include "modalidades.h"
#include "equipes.h"

void carregarArquivo(Modalidades *d, char *nomeArquivo)
{
    FILE *arquivo;
    char linha[150];
    char nome[50], cidade[50];
    char modalidadeAtual[50];
    int ano, titulos;

    if (d == NULL)
    {
        printf("\nLista inexistente!\n");
        return;
    }

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    while (fgets(linha, 150, arquivo) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha) == 0)
            continue;

        // Linha de modalidade: formato [Nome]
        if (linha[0] == '[')
        {
            strncpy(modalidadeAtual, linha + 1, strlen(linha) - 2);
            modalidadeAtual[strlen(linha) - 2] = '\0';

            inserirModalidade(d, modalidadeAtual);
            continue;
        }

        // Linha de equipe: formato nome;cidade;ano;titulos
        sscanf(linha, "%49[^;];%49[^;];%d;%d", nome, cidade, &ano, &titulos);

        inserirEquipe(d, modalidadeAtual, nome, cidade, ano, titulos);
    }

    fclose(arquivo);
}