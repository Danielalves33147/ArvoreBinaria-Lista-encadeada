#include <stdio.h>
#include <stdlib.h>
/*
Autores: Daniel Alves , Joao Vitor Menezes 20/07/2022
*/

// -------------------FILA----------------------------- //
struct Fila
{
    int capacidade;
    float *dados;
    int primeiro;
    int ultimo;
    int nItens;
};
typedef struct Fila *f;

void CriandoFila(struct Fila *f)
{ // Funçao que vai criar a lista
    int c;
    f->capacidade = c;
    f->dados = (float *)malloc(f->capacidade * sizeof(float));
    f->primeiro = 0;
    f->ultimo = -1;
    f->nItens = 0;
}

void InserindoFIla(struct Fila *f, int v)
{ // Funcao que recebe os valores da lista
    if (f->ultimo == f->capacidade - 1)
        f->ultimo = -1;
    f->ultimo++;
    f->dados[f->ultimo] = v; // incrementa ultimo e insere
    f->nItens++;             // mais um item inserido
}

void MostrandoFila(struct Fila *f)
{
    int cont, i;
    for (cont = 0, i = f->primeiro; cont < f->nItens; cont++)
    {
        printf("[%.0f] -> ", f->dados[i++]);
        if (i == f->capacidade)
            i = 0;
    }
}

int RemovendoFila(struct Fila *f)
{ // Pega o item do começo da fila

    int temp = f->dados[f->primeiro++]; // Pega o valor e incrementa o primeiro

    if (f->primeiro == f->capacidade)
        f->primeiro = 0;

    f->nItens--; // Retira um item
    return temp;
}

// ---------------------- PILHA ------------------------------- //
struct tipo_no
{
    int num;
    struct tipo_no *elo;
};

typedef struct tipo_no *no;

no CriandoPilha(int n)
{ // Funçao que cria a pilha
    no p;
    p = (no)malloc(sizeof(struct tipo_no));
    p->num = n;
    p->elo = NULL;
    return p;
}

no InserindoPilha(int n, no p)
{ // Funcao que vai receber os valores da Pilha
    no l;
    l = (no)malloc(sizeof(struct tipo_no));
    l->num = n;
    l->elo = p;
    return l;
}

void MostrandoPilha(no p)
{
    int cont, dados;
    no el = p;
    printf("\n");
    for (cont = 0; el != NULL; cont++)
    {
        dados = el->num;
        printf(" [%i] -> ", dados);
        el = el->elo;
    }
}

// -------------------------- MAIN ------------------------------- //
int main()
{
    int cont = 0;

    float valor;
    struct Fila umaFila;
    int resp, num;
    no p;

    printf("\t    Menu Principal\n\n\tSelecione o tipo de lista: \n\n[1]->Pilha\t[2]->Fila\t[3]->Sair\n\n=> ");
    scanf("%i", &resp);

    switch (resp)
    {

    case 1: // PILHA

        do
        {
            int escolha, elementos;

            printf("\t\tSelecione: \n\n[1]->Inserir\t[2]->Deletar\t[3]->Retornar ao Menu\n\n=> ");
            scanf("%i", &escolha);

            switch (escolha)
            {
            case 1: // Se escolhido Inserir

                printf("\nDigite o elemento: ");
                scanf("%i", &num);

                cont++;

                if (cont == 1)
                {
                    p = CriandoPilha(num);
                }
                else
                {
                    p = InserindoPilha(num, p);
                }
                MostrandoPilha(p);
                printf("\n");
                break;
            case 2: // Se escolhido Deletar
                break;
            case 3:
                return main();
                break;
            default:
                printf("[ERRO] Opçao invalida");
                break;
            }

            printf("\nDeseja Terminar? [1-sim/0-nao]: ");
            scanf("%i", &resp);
        } while (resp == 0);

        MostrandoPilha(p);
        printf(" [NULL]\n\n\t==>>Saindo da Pilha<<==\n\n");

        return main();
        break;

    case 2: // FILA

        CriandoFila(&umaFila);
        int escolha;

        do
        {

            printf("\t\tSelecione: \n\n[1]->Inserir\t[2]->Deletar\t[3]->Retornar ao Menu\n\n=> ");
            scanf("%i", &escolha);

            switch (escolha)
            {
            case 1:                              // Se escolhido Inserir
                printf("\nDigite o elemento: "); // Recebe os numeros
                scanf("%f", &valor);

                InserindoFIla(&umaFila, valor);
                printf("\n");

                MostrandoFila(&umaFila); // Mostra a fila ja inserida
                printf("\n");

                break;
            case 2: // Se escolhido Deletar
                valor = RemovendoFila(&umaFila);
                printf("\n%0.f removido com sucesso\n\n", valor);
                MostrandoFila(&umaFila); // Mostra a fila após deleção
                printf("\n");

                break;
            case 3:
                return main();
                break;
            default:
                printf("[ERRO] Opçao invalida");
                break;
            }

            printf("\nDeseja Terminar? [1-sim/0-nao]: "); // Menu do while, se repete ou finaliza
            scanf("%i", &resp);

        } while (resp == 0);

        printf("\n");
        MostrandoFila(&umaFila);
        printf(" [NULL]\n\n\t==>>Saindo da Fila<<==\n\n"); // Terminou tudo com o NULL
        printf("\n\n\n\n\n\n\n\n\n\n\n");

        return main();
        break;

    case 3: // FINALIZA TUDO
        printf("\n\t==>>Programa Encerrado<<==\n");
        break;

    default: // NUMERO INVALIDO
        printf("\n=> [ERRO]  ==>>Selecione uma Opcao valida<<==\n\n\n");

        return main();
        break;
    }
    return 0;
}