#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib.h"

typedef struct noEquipesfunc
{ // Usado na ordEquipesAno
    char nome[65];
    int ano;
} NoEquipesfunc;
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
    struct noEquipes *inicio;
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
                printf("\n-  %s %s", atualEq->nome, atual->nome);
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