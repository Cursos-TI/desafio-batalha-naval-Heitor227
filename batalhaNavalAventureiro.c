#include <stdio.h>

#define TAM 10
#define NAVIO 3

int tabuleiro[TAM][TAM];

void inicializarTabuleiro()
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            tabuleiro[i][j] = 0;
        }
    }
}

void exibirTabuleiro()
{
    printf("\n  ");
    for (int c = 0; c < TAM; c++)
        printf(" %d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++)
    {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++)
        {
            if (tabuleiro[i][j] == 0)
                printf(" 0 ");
            else
                printf(" 3 ");
        }
        printf("\n");
    }
    printf("\n");
}

int podePosicionar(int li, int ci, int di, int dj)
{
    int i = li, j = ci;
    for (int k = 0; k < NAVIO; k++)
    {
        if (i < 0 || i >= TAM || j < 0 || j >= TAM)
        {
            return 0;
        }
        if (tabuleiro[i][j] != 0)
        {
            return 0;
        }
        i += di;
        j += dj;
    }
    return 1;
}

void posicionarNavio(int li, int ci, int di, int dj)
{
    int i = li, j = ci;
    for (int k = 0; k < NAVIO; k++)
    {
        tabuleiro[i][j] = 3;
        i += di;
        j += dj;
    }
}

int tentarPosicionar(int li, int ci, int di, int dj, const char *tipo)
{
    if (podePosicionar(li, ci, di, dj))
    {
        posicionarNavio(li, ci, di, dj);
        printf("Navio %s posicionado em (%d,%d) com direção (%d,%d)\n",
               tipo, li, ci, di, dj);
        return 1;
    }
    else
    {
        printf("FALHA: Não foi possível posicionar navio %s em (%d,%d)\n", tipo, li, ci);
        return 0;
    }
}

int main()
{
    inicializarTabuleiro();

    printf("=== BATALHA NAVAL - NAVIOS DIAGONAIS ===\n");
    printf("Posicionando 4 navios de tamanho %d no tabuleiro %dx%d\n\n", NAVIO, TAM, TAM);

    int sucesso = 1;

    sucesso &= tentarPosicionar(1, 2, 0, 1, "HORIZONTAL");

    sucesso &= tentarPosicionar(5, 8, 1, 0, "VERTICAL  ");

    sucesso &= tentarPosicionar(3, 1, 1, 1, "DIAGONAL SE");

    sucesso &= tentarPosicionar(7, 6, 1, -1, "DIAGONAL SO");

    if (sucesso)
    {
        printf("\nTODOS OS NAVIOS FORAM POSICIONADOS COM SUCESSO!\n");
    }
    else
    {
        printf("\nERRO: Um ou mais navios não puderam ser posicionados.\n");
    }

    printf("\n=== TABULEIRO FINAL ===\n");
    exibirTabuleiro();

    printf("Legenda:\n");
    printf("  0  = Água\n");
    printf("  3  = Parte de um navio (valor 3)\n");
    printf("Total de navios: 4 (2 retos + 2 diagonais)\n");

    return 0;
}