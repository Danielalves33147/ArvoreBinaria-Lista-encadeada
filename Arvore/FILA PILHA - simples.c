#include <stdio.h>
#include <stdlib.h>
/*
Trabalho Menu Lista Encadeada Simples - Estrutura de Dados, IFBA, 2022.
Autores: Daniel Alves, Joao Vitor Menezes.
Data: 24/07/2022.
*/

// -------------------FILA----------------------------- //
struct Fila // Cria o no da Fila.
{
    int CapacidadeDaFila;
    int *DadosDaFila;
    int PrimeiroDaFila;
    int UltimoDaFila;
    int NumeroDeItens;
};
typedef struct Fila *f;

void CriandoFila(struct Fila *f)
{
    int c;
    f->CapacidadeDaFila = c;
    f->DadosDaFila = (int *)malloc(f->CapacidadeDaFila * sizeof(int));
    f->PrimeiroDaFila = 0;
    f->UltimoDaFila = -1;
    f->NumeroDeItens = 0;
}

void InserindoFila(struct Fila *f, int v)
{
    if (f->UltimoDaFila == f->CapacidadeDaFila - 1)
    {
        f->UltimoDaFila = -1;
    }
    f->UltimoDaFila++;
    f->DadosDaFila[f->UltimoDaFila] = v; // Incrementa o ultimo item na Fila.
    f->NumeroDeItens++;                  // Insere mais um Item.
}

void MostrandoFila(struct Fila *f)
{
    int Contador, i;
    for (Contador = 0, i = f->PrimeiroDaFila; Contador < f->NumeroDeItens; Contador++)
    {
        printf("[%i] -> ", f->DadosDaFila[i++]);
        if (i == f->CapacidadeDaFila)
        {
            i = 0;
        }
    }
    printf(" NULL");
}

int RemovendoFila(struct Fila *f)
{ // Pega o item do começo da fila

    int Removedor = f->DadosDaFila[f->PrimeiroDaFila++]; // Pega o elemento e incrementa o primeiro.

    if (f->PrimeiroDaFila == f->CapacidadeDaFila)
    {
        f->PrimeiroDaFila = 0;
    }
    f->NumeroDeItens--; // Retira um item.
    return Removedor;
}

// ---------------------- PILHA ------------------------------- //
struct no // Cria o no da Pilha.
{
    int ElementoDaPilha;
    struct no *ProximoDaPilha;
};
typedef struct no No;

struct Pilha // Cria a Pilha.
{
    No *TopoDaPilha;
};
typedef struct Pilha Pilha;

void InserindoPilha(Pilha *p, int n)
{
    No *no = malloc(sizeof(No));
    no->ElementoDaPilha = n;
    no->ProximoDaPilha = p->TopoDaPilha; // Adiciona cada elemento inserido ao TopoDaPilha.
    p->TopoDaPilha = no;
}

No *RemovendoPilha(Pilha *p)
{
    No *no = NULL;
    if (p->TopoDaPilha)
    {
        no = p->TopoDaPilha;                 // Recebe o valor do TopoDaPilha.
        p->TopoDaPilha = no->ProximoDaPilha; // Transfere o TopoDaPilha para o proximo elemento.
    }
    return no; // Retorna o valor recebido.
}

void MostrandoPilha(No *no)
{
    if (no) // Detecta o no.
    {
        printf("[%i] -->", no->ElementoDaPilha); // Imprime o elemento inserido pelo usuario.
        MostrandoPilha(no->ProximoDaPilha);      // Transfere o proximo elemento a ser inserido.
    }
}
// ------------------------ CODIGO ANTI-ERRO ------------------------ //
void AntiErro(int Resposta)
{
    char RecebedorTemporario[20];
    if (!fgets(RecebedorTemporario, sizeof RecebedorTemporario, stdin))
        ; // Condicionais de erro para impedir o programa de "crashar" ->
    if (sscanf(RecebedorTemporario, "%i", &Resposta) != 1)
        ; // ao se digitar uma letra ou caractere especial.
}
// ------------------------ LIMPADOR DE TELA ------------------------ //
int LimpadorDeTela()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return 0;
}

// -------------------------- MAIN ------------------------------- //
int main()
{
    // ------------------------------ //
    int ElementoDaFila; // Declaraçoes relacionadas a Fila.
    struct Fila umaFila;
    // ------------------------------ //
    int RespostaMenu, ElementoDaPilha;
    No *no; // Declaraçoes relacionadas a Pilha.
    Pilha p;
    p.TopoDaPilha = NULL;
    // ---------------------------- ///

    // Menu principal.
    printf("\t    Menu Principal\n\n\tSelecione o tipo de lista: \n\n[1]->Pilha\t[2]->Fila\t[3]->Sair\n\n=> ");
    scanf("%i", &RespostaMenu);
    AntiErro(RespostaMenu);
    LimpadorDeTela();

    switch (RespostaMenu)
    {

    case 1: // ------------------ PILHA ----------------- //

        do
        {
            int EscolhaPilha, Contador = 0, QuantElementosPilha, QuantRemoverPilha;

            printf("\t\tSelecione: \n\n[1]->Inserir\t[2]->Deletar\t[3]->Retornar ao Menu\n\n=> ");
            scanf("%i", &EscolhaPilha); // Menu da Pilha.
            LimpadorDeTela();

            switch (EscolhaPilha)
            {
            case 1: // Se escolhido Inserir.
                printf("Deseja inserir quantos elementos? ");
                scanf("%i", &QuantElementosPilha);
                for (Contador = 0; Contador < QuantElementosPilha; Contador + 1)
                {
                    printf("\nDigite o elemento[%i]: ", Contador + 1);
                    scanf("%i", &ElementoDaPilha);

                    Contador++;

                    InserindoPilha(&p, ElementoDaPilha); // Insere os elementos na pilha.

                    MostrandoPilha(p.TopoDaPilha); // Mostra a pilha apos deleçao.
                    printf(" NULL");
                    printf("\n");
                }
                break;
            case 2: // Se escolhido Deletar.
                printf("Deseja remover quantos elementos? ");
                scanf("%i", &QuantRemoverPilha);
                for (Contador = 0; Contador < QuantRemoverPilha; Contador + 1)
                {
                    no = RemovendoPilha(&p);
                    if (no == NULL)
                    {
                        printf("\n\tPilha vazia!");
                        break;
                    }
                    else
                    {
                        if (no)
                        {
                            printf("\t\nRemovido: %i\n\n", no->ElementoDaPilha);
                            MostrandoPilha(p.TopoDaPilha); // Mostra a pilha após deleçao.
                            printf(" NULL");
                            Contador++;
                        }
                    }
                    printf("\n");
                }
                break;
            case 3: // Retorna ao Menu Principal.
                return main();
                break;
            default:
                printf("\n\t[ERRO] Opçao invalida\n\n"); // Mensagem de erro caso escolha de opçao invalida.
                return main();
                break;
            }
            printf("\n\nDeseja continuar na Pilha? [1-Sim/ 0-Nao]: "); // Sim - Leva ao Menu da Pilha.
            scanf("%i", &RespostaMenu);                                // Nao - Leva ao Menu Principal.
            AntiErro(RespostaMenu);
            LimpadorDeTela();
        } while (RespostaMenu == 1);

        printf("\n\t==>>Saindo da Pilha<<==\n\n"); // Mensagem de saida da Pilha.
        printf("\n");

        return main(); // Retorna ao Menu principal.
        break;

    case 2: // ------------------ FILA ------------------ //

        CriandoFila(&umaFila); // Inicia a Fila.
        int EscolhaFila, QuantElementosFila, Contador = 0, QuantRemoverFila;

        do
        {

            printf("\t\tSelecione: \n\n[1]->Inserir\t[2]->Deletar\t[3]->Retornar ao Menu\n\n=> ");
            scanf("%i", &EscolhaFila); // Menu da Fila.
            LimpadorDeTela();

            switch (EscolhaFila)
            {
            case 1: // Se escolhido Inserir.
                printf("Deseja inserir quantos elementos? ");
                scanf("%i", &QuantElementosFila);
                for (Contador = 0; Contador < QuantElementosFila; Contador + 1)
                {
                    printf("\nDigite o elemento[%i]: ", Contador + 1);
                    scanf("%i", &ElementoDaFila);

                    InserindoFila(&umaFila, ElementoDaFila);
                    printf("\n");

                    MostrandoFila(&umaFila); // Mostra a fila ja inserida.
                    printf("\n");

                    Contador++;
                }
                break;
            case 2: // Se escolhido Deletar.
                printf("Deseja remover quantos elementos? ");
                scanf("%i", &QuantRemoverFila);   
                for (Contador = 0; Contador < QuantRemoverFila; Contador + 1)
                {
                    ElementoDaFila = RemovendoFila(&umaFila);

                    if (ElementoDaFila == 0)
                    {
                        printf("\n\tFila vazia!\n");
                        break;
                    }
                    else
                    {
                        printf("\nRemovido: %i\n", ElementoDaFila);
                        MostrandoFila(&umaFila); // Mostra a fila após deleção.
                        printf("\n");
                        Contador++;
                    }
                }
                break;
            case 3: // Retorna ao Menu Principal.
                return main();
                break;
            default: // Mensagem de erro caso escolhido opçao invalida.
                printf("\n\t[ERRO] Opçao invalida\n\n");
                return main();
                break;
            }

            printf("\n\nDeseja continuar na Fila? [1-Sim/ 0-Nao]: "); // Sim - Leva ao Menu da Pilha.
            scanf("%i", &RespostaMenu);
            AntiErro(RespostaMenu);
            LimpadorDeTela();
        } while (RespostaMenu == 1);

        printf("\n");
        printf("\n\n\t==>>Saindo da Fila<<==\n\n"); // Mensagem de saida da Fila.
        printf("\n");
        return main(); // Retorna ao Menu Principal.
        break;

    case 3: // ---------------------- MENSAGEM DE FINALIZACAO --------------------- //
        printf("\n\t==>>Programa Encerrado<<==\n");
        break;

    default: // -------------------- ERRO DE OPÇAO INVALIDA DO MENU PRINCIPAL ---------------- //
        printf("\n=> [ERRO]  ==>>Selecione uma Opcao valida<<==\n\n\n");
        return main();
        break;
    }
    return 0;
}