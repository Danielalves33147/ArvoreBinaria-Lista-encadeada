#include <stdio.h>
#include <stdlib.h>
/*
Trabalho Lista Duplamente Encadeada, IFBA.    Data: 19/08/2022
Autores: João Vitor Menezes e Daniel Alves
*/

// Pilha
typedef struct NoPilha
{
    int DadosDaPilha;
    struct NoPilha *ProximoDaPilha;
    struct NoPilha *AnteriorDaPilha;
} NoPilha;

void InserindoPilha(NoPilha **Pilha, int ElementoRecebidoPilha)
{
    NoPilha *NovaPilha = malloc(sizeof(NoPilha));

    if (NovaPilha)
    {
        NovaPilha->DadosDaPilha = ElementoRecebidoPilha;
        NovaPilha->ProximoDaPilha = *Pilha;
        NovaPilha->AnteriorDaPilha = NULL;
        if (*Pilha)
        {
            (*Pilha)->AnteriorDaPilha = NovaPilha;
        }
        *Pilha = NovaPilha;
    }
}

NoPilha *RemovendoPilha(NoPilha **Pilha, int ElementoRecebidoPilha)
{
    NoPilha *AuxiliarPilha, *RemovendoPilha = NULL;

    if (*Pilha)
    {
        if ((*Pilha)->DadosDaPilha == ElementoRecebidoPilha)
        {
            RemovendoPilha = *Pilha;
            *Pilha = RemovendoPilha->ProximoDaPilha;
            if (*Pilha)
            {
                (*Pilha)->AnteriorDaPilha = NULL;
            }
        }
        else
        {
            AuxiliarPilha = *Pilha;
            while (AuxiliarPilha->ProximoDaPilha && AuxiliarPilha->ProximoDaPilha->DadosDaPilha != ElementoRecebidoPilha)
                AuxiliarPilha = AuxiliarPilha->ProximoDaPilha;
            if (AuxiliarPilha->ProximoDaPilha)
            {
                RemovendoPilha = AuxiliarPilha->ProximoDaPilha;
                AuxiliarPilha->ProximoDaPilha = RemovendoPilha->ProximoDaPilha;
                if (AuxiliarPilha->ProximoDaPilha)
                {
                    AuxiliarPilha->ProximoDaPilha->AnteriorDaPilha = AuxiliarPilha;
                }
            }
        }
    }
    return RemovendoPilha;
}
void ImprimindoPilha(NoPilha *NoPilha)
{
    printf("\n\tPilha: ");
    while (NoPilha)
    {
        printf("<-[%i]->", NoPilha->DadosDaPilha);
        NoPilha = NoPilha->ProximoDaPilha;
    }
    printf("->[NULL]");
    printf("\n\n");
}

// Fila
typedef struct NoFila
{
    int DadosDaFila;
    struct NoFila *ProximoDaFila;
    struct NoFila *AnteriorDaFila;
} NoFila;

void InserindoFila(NoFila **Fila, int ElementoRecebidoFila)
{
    NoFila *AuxiliarFila, *NovaFila = malloc(sizeof(NoFila));

    if (NovaFila)
    {
        NovaFila->DadosDaFila = ElementoRecebidoFila;
        NovaFila->ProximoDaFila = NULL;

        if (*Fila == NULL)
        {
            *Fila = NovaFila;
            NovaFila->AnteriorDaFila = NULL;
        }
        else
        {
            AuxiliarFila = *Fila;
            while (AuxiliarFila->ProximoDaFila)
            {
                AuxiliarFila = AuxiliarFila->ProximoDaFila;
            }
            AuxiliarFila->ProximoDaFila = NovaFila;
            NovaFila->AnteriorDaFila = AuxiliarFila;
        }
    }
}

NoFila *RemovendoFila(NoFila **Fila, int ElementoRecebidoFila)
{
    NoFila *AuxiliarFila, *RemovendoFila = NULL;

    if (*Fila)
    {
        if ((*Fila)->DadosDaFila == ElementoRecebidoFila)
        {
            RemovendoFila = *Fila;
            *Fila = RemovendoFila->ProximoDaFila;
            if (*Fila)
            {
                (*Fila)->AnteriorDaFila = NULL;
            }
        }
        else
        {
            AuxiliarFila = *Fila;
            while (AuxiliarFila->ProximoDaFila && AuxiliarFila->ProximoDaFila->DadosDaFila != ElementoRecebidoFila)
            {
                AuxiliarFila = AuxiliarFila->ProximoDaFila;
            }
            if (AuxiliarFila->ProximoDaFila)
            {
                RemovendoFila = AuxiliarFila->ProximoDaFila;
                AuxiliarFila->ProximoDaFila = RemovendoFila->ProximoDaFila;
                if (AuxiliarFila->ProximoDaFila)
                {
                    AuxiliarFila->ProximoDaFila->AnteriorDaFila = AuxiliarFila;
                }
            }
        }
    }
    return RemovendoFila;
}
void ImprimindoFila(NoFila *NoFila)
{
    printf("\n\tFila: ");
    while (NoFila)
    {
        printf("<-->[%i]", NoFila->DadosDaFila);
        NoFila = NoFila->ProximoDaFila;
    }
    printf("->[NULL]");
    printf("\n\n");
}

// Limpador de tela
void LimpadorDeTela()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

// Main
int main()
{

    int MenuPrincipal, Escolha, Contador, Remov;
    NoFila *RemovidoFila, *PassandoFila = NULL;
    NoPilha *RemovidoPilha, *PassandoPilha = NULL;
    int Fila, EscolhaFila;
    int Pilha, EscolhaPilha;
    
    do
    {
        printf("\n\t\tMenu Principal\t\n");
        printf("\n\t\tEscolha:\n\n1 - Pilha\t2 - Fila\t3 - Sair\n");
        scanf("%i", &MenuPrincipal);
        LimpadorDeTela();
        switch (MenuPrincipal)
        {
        case 1: // Pilha
            do
            {
                printf("\n\t\tEscolha:\n\n1 - Inserir\t2 - Remover\t3 - Sair\n");
                scanf("%i", &Pilha);
                LimpadorDeTela();
                switch (Pilha)
                {
                case 1:
                    printf("Deseja inserir quantos elementos? \n");
                    scanf("%i", &EscolhaPilha);
                    LimpadorDeTela();

                    for (Contador = 0; Contador < EscolhaPilha; Contador++)
                    {
                        printf("Digite um elemento: ");
                        scanf("%i", &Escolha);
                        InserindoPilha(&PassandoPilha, Escolha);
                        ImprimindoPilha(PassandoPilha);
                    }
                    break;
                case 2:
                    printf("Deseja remover quantos elementos? \n");
                    scanf("%i", &Remov);
                    LimpadorDeTela();

                    for (Contador = 0; Contador < Remov; Contador++)
                    {
                        ImprimindoPilha(PassandoPilha);
                        printf("Digite um elemento a ser removido: ");
                        scanf("%i", &Escolha);
                        RemovidoPilha = RemovendoPilha(&PassandoPilha, Escolha);
                        if (RemovidoPilha)
                        {
                            printf("Elemento a ser removido: %i\n", RemovidoPilha->DadosDaPilha);
                            free(RemovidoPilha);
                            ImprimindoPilha(PassandoPilha);
                        }
                        else
                            printf("Elemento inexistente!\n");
                    }
                    break;
                case 3:
                    return main();
                    break;
                default:
                    printf("\n\tOpçao invalida!!\n\n");
                    return main();
                    break;
                }
            } while (Pilha != 3);
            break;
        case 2: // Fila
            do
            {
                printf("\n\t\tEscolha:\n\n1 - Inserir\t2 - Remover\t3 - Sair\n");
                scanf("%i", &Fila);
                LimpadorDeTela();
                switch (Fila)
                {
                case 1:
                    printf("Deseja inserir quantos elementos? \n");
                    scanf("%i", &EscolhaFila);
                    LimpadorDeTela();

                    for (Contador = 0; Contador < EscolhaFila; Contador++)
                    {
                        printf("Digite um elemento: ");
                        scanf("%i", &Escolha);
                        InserindoFila(&PassandoFila, Escolha);
                        ImprimindoFila(PassandoFila);
                    }
                    break;
                case 2:
                    printf("Deseja remover quantos elementos? \n");
                    scanf("%i", &Remov);

                    for (Contador = 0; Contador < Remov; Contador++)
                    {
                        ImprimindoFila(PassandoFila);
                        printf("Digite um elemento a ser removido: ");
                        scanf("%i", &Escolha);
                        RemovidoFila = RemovendoFila(&PassandoFila, Escolha);
                        if (RemovidoFila)
                        {
                            printf("Elemento a ser removido: %i\n", RemovidoFila->DadosDaFila);
                            free(RemovidoFila);
                            ImprimindoFila(PassandoFila);
                        }
                        else
                            printf("Elemento inexistente!\n");
                    }
                    break;
                case 3:
                    return main();
                    break;
                default:
                    printf("\n\tOpçao invalida!!\n\n");
                    return main();
                    break;
                }
            } while (Fila != 3);
            break;

        default:
            if (MenuPrincipal != 3)
            {
                printf("Opcao invalida!\n\n");
            }
        }
        if(MenuPrincipal == 3)
        {
            printf("\n\t\tPrograma Encerrado!!\n\n");
        }
    } while (MenuPrincipal != 3);

    return 0;
}