#include <stdio.h>
#include <stdlib.h>

/* Trabalho Árvore Binária - Estrutura de Dados, IFBA, 2022.
Autores: Daniel Alves e João Vitor Menezes.    Data:07/09/2022.
Obs: Essa Árvore Binária é balanceada de forma dinâmica. */

// --------------------------------CRIANDO ARVORE----------------------------------------//
typedef struct NoDaArvore
{
    int DadosDaArvore;
    struct NoDaArvore *Esquerda, *Direita;
    int AlturaDaArvore;
} No;

No *CriandoArvore(int Dados)
{
    No *NovaArvore = malloc(sizeof(No));

    if (NovaArvore)
    {
        NovaArvore->DadosDaArvore = Dados;
        NovaArvore->Esquerda = NULL;
        NovaArvore->Direita = NULL;
        NovaArvore->AlturaDaArvore = 0;
    }
    else
    {
        printf("\n\tERRO em Criar a Arvore!\t\n");
    }
    return NovaArvore;
}

// ------------------------- CALCULOS PARA BALANCEAR ------------------------------------//
int MaiorEntreDoisValores(int Valor1, int Valor2)
{
    return (Valor1 > Valor2) ? Valor1 : Valor2;
}

int AlturaDeUmNo(No *NoDaArvore)
{
    if (NoDaArvore == NULL)
    {
        return -1;
    }
    else
    {
        return NoDaArvore->AlturaDaArvore;
    }
}

int FatorParaBalanceamento(No *NoDaArvore)
{
    if (NoDaArvore)
    {
        return (AlturaDeUmNo(NoDaArvore->Esquerda) - AlturaDeUmNo(NoDaArvore->Direita));
    }
    else
    {
        return 0;
    }
}

// ------------------------------ ROTAÇÕES PARA BALANCEAR ------------------------------//
No *RotacaoEsquerda(No *raiz)
{
    No *DireitaDaRaiz, *FilhoAEsquerda;

    DireitaDaRaiz = raiz->Direita;
    FilhoAEsquerda = DireitaDaRaiz->Esquerda;

    DireitaDaRaiz->Esquerda = raiz;
    raiz->Direita = FilhoAEsquerda;

    raiz->AlturaDaArvore = MaiorEntreDoisValores(AlturaDeUmNo(raiz->Esquerda), AlturaDeUmNo(raiz->Direita)) + 1;
    DireitaDaRaiz->AlturaDaArvore = MaiorEntreDoisValores(AlturaDeUmNo(DireitaDaRaiz->Esquerda), AlturaDeUmNo(DireitaDaRaiz->Direita)) + 1;

    return DireitaDaRaiz;
}

No *RotacaoDireita(No *raiz)
{
    No *EsquerdaDaRaiz, *FilhoADireita;

    EsquerdaDaRaiz = raiz->Esquerda;
    FilhoADireita = EsquerdaDaRaiz->Direita;

    EsquerdaDaRaiz->Direita = raiz;
    raiz->Esquerda = FilhoADireita;

    raiz->AlturaDaArvore = MaiorEntreDoisValores(AlturaDeUmNo(raiz->Esquerda), AlturaDeUmNo(raiz->Direita)) + 1;
    EsquerdaDaRaiz->AlturaDaArvore = MaiorEntreDoisValores(AlturaDeUmNo(EsquerdaDaRaiz->Esquerda), AlturaDeUmNo(EsquerdaDaRaiz->Direita)) + 1;

    return EsquerdaDaRaiz;
}

No *RotacaoDuplaEsquerdaDireita(No *raiz)
{
    raiz->Esquerda = RotacaoEsquerda(raiz->Esquerda);
    return RotacaoDireita(raiz);
}

No *RotacaoDuplaDireitaEsquerda(No *raiz)
{
    raiz->Direita = RotacaoDireita(raiz->Direita);
    return RotacaoEsquerda(raiz);
}

// ---------------------------BALANCEANDO------------------------------------------//
No *BalanceandoArvore(No *raiz)
{
    int FatorBalanceamento = FatorParaBalanceamento(raiz);

    // Rotação Esquerda
    if (FatorBalanceamento < -1 && FatorParaBalanceamento(raiz->Direita) <= 0)
    {
        raiz = RotacaoEsquerda(raiz);
    }
    // Rotação Direita
    else if (FatorBalanceamento > 1 && FatorParaBalanceamento(raiz->Esquerda) >= 0)
    {
        raiz = RotacaoDireita(raiz);
    }

    // Rotação Dupla Esquerda-Direita
    else if (FatorBalanceamento > 1 && FatorParaBalanceamento(raiz->Esquerda) < 0)
    {
        raiz = RotacaoDuplaEsquerdaDireita(raiz);
    }

    // Rotação Dupla Direita-Esquerda
    else if (FatorBalanceamento < -1 && FatorParaBalanceamento(raiz->Direita) > 0)
    {
        raiz = RotacaoDuplaDireitaEsquerda(raiz);
    }
    return raiz;
}

//-----------------------------------INSERINDO----------------------------------//
No *InserindoNaArvore(No *raiz, int Dados)
{
    if (raiz == NULL) 
    {
        return CriandoArvore(Dados);
    }
    else
    { 
        if (Dados < raiz->DadosDaArvore)
        {
            raiz->Esquerda = InserindoNaArvore(raiz->Esquerda, Dados);
        }
        else if (Dados > raiz->DadosDaArvore)
        {
            raiz->Direita = InserindoNaArvore(raiz->Direita, Dados);
        }
        else
        {
            printf("\nInsercao nao realizada!\n %i ja existe na arvore!\n", Dados);
        }
    }
    // Recalcula a altura dos nos entre a raiz e o novo no inserido
    raiz->AlturaDaArvore = MaiorEntreDoisValores(AlturaDeUmNo(raiz->Esquerda), AlturaDeUmNo(raiz->Direita)) + 1;
    
    // Verifica se sera necessario rebalancear a arvore
    raiz = BalanceandoArvore(raiz);
    return raiz;
}
// ----------------------------------- IMPRIMINDO --------------------------------------//
void ImprimindoGraficamente(No *raiz, int NivelParaImpressao)
{
    int i;
    if (raiz)
    {
        ImprimindoGraficamente(raiz->Direita, NivelParaImpressao + 1);
        printf("\n\n");

        for (i = 0; i < NivelParaImpressao; i++)
        {
            printf("\t");
        }
        printf(" /(%i)", raiz->DadosDaArvore);
        ImprimindoGraficamente(raiz->Esquerda, NivelParaImpressao + 1);
    }
}

void ImprimindoEmOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        ImprimindoEmOrdem(raiz->Esquerda);
        printf(" %i ", raiz->DadosDaArvore);
        ImprimindoEmOrdem(raiz->Direita);
    }
}
void ImprimindoPreOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        printf(" %i ", raiz->DadosDaArvore);
        ImprimindoPreOrdem(raiz->Esquerda);
        ImprimindoPreOrdem(raiz->Direita);
    }
}
void ImprimindoPosOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        ImprimindoPosOrdem(raiz->Esquerda);
        ImprimindoPosOrdem(raiz->Direita);
        printf(" %i ", raiz->DadosDaArvore);
    }
}
// ---------------------------------CONSULTANDO---------------------------------------//
int ConsultandoNaArvore(No *raiz, int DadoRecebido)
{
    if (raiz == 0)
    {
        return -999;
    }
    else
    {
        if (raiz->DadosDaArvore == DadoRecebido)
        {
            return raiz->DadosDaArvore;
        }
        else
        {
            if (DadoRecebido < raiz->DadosDaArvore)
            { 
                return ConsultandoNaArvore(raiz->Esquerda, DadoRecebido);
            }
            else
            {
                return ConsultandoNaArvore(raiz->Direita, DadoRecebido);
            }
        }
    }
}

// ------------------------------------MAIN-------------------------------------//
int main()
{
    int escolha, escolha2, valor;
    No *raiz = NULL;
    do
    {
        printf("\n\t\t==>>Menu Principal<<==");
        printf("\n\n[1]>Inserir\t[2]>Consultar\t[3]>Imprimir\t[4]>Sair\n\n==>");
        scanf("%i", &escolha);

        switch (escolha)
        {
        case 1: // Inserindo na arvore
            printf("\n\nValor a ser adicionado ==> ");
            scanf("%i", &valor);
            raiz = InserindoNaArvore(raiz, valor);
            printf("\n\n==>>Impressao da arvore Binaria<<==\n\n");
            ImprimindoGraficamente(raiz, 1);
            printf("\n\n\n");
            break;
        case 2: //Consultando na arvore
            printf("\nQual valor deseja consultar? \n");
            scanf("%i", &valor);
            if (ConsultandoNaArvore(raiz, valor) == -999)
            {
                printf("\nValor nao encontrado!\n");
            }
            else
            {
                printf("\nValor encontrado: %i\n", ConsultandoNaArvore(raiz, valor));
            }
            printf("\n\n\n");
            break;
        case 3: // Imprimindo em Pre-Ordem, Ordem ou Pos-Ordem
            do
            {
                printf("\nImprimir em\n\n\t[1]>Pre-Ordem\t[2]>Ordem\t[3]>Pos-Ordem\n\n==>");
                scanf("%i", &escolha2);
                switch (escolha2)
                {
                case 1:
                    printf("\n\t==>>Impressao em Pre-Ordem<<==\n\n");
                    ImprimindoPreOrdem(raiz);
                    printf("\n\n\n");
                    break;
                case 2:
                    printf("\n\t==>>Impressao em Ordem<<==\n\n");
                    ImprimindoEmOrdem(raiz);
                    printf("\n\n\n");
                    break;
                case 3:
                    printf("\n\t==>>Impressao em Pos-Ordem<<==\n\n");
                    ImprimindoPosOrdem(raiz);
                    printf("\n\n\n");
                    break;
                }
                if (escolha2 < 1 || escolha2 > 3)
                {
                    printf("\n\t   ==>>Opçao Invalida<<==\n\n"); 
                }
            } while (escolha2 < 1 || escolha2 > 3);
            break;
        case 4: // Finalizando o programa
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("\t==>>Finalizando Codigo<<==\n");
            break;
        default: // Mensagem de erro ao escolher opcao invalida
            printf("\n\n==>>Selecione uma Opcao Valida<<==\n\n");
            break;
        }
    } while (escolha != 4);
    return 0;
}