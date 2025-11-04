#include <stdio.h>

#define TAM 10
#define NAVIO 3

void exibirTabuleiro(int tabuleiro[TAM][TAM])
{
    printf("  ");
    for (int c = 0; c < TAM; c++)
    {
        printf(" %d ", c);
    }
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

int posicionarHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna)
{
    if (linha < 0 || linha >= TAM || coluna < 0 || coluna + NAVIO > TAM)
    {
        printf("Erro: Navio horizontal fora dos limites!\n");
        return 0;
    }
    for (int j = coluna; j < coluna + NAVIO; j++)
    {
        if (tabuleiro[linha][j] != 0)
        {
            printf("Erro: Sobreposição no navio horizontal!\n");
            return 0;
        }
    }
    for (int j = coluna; j < coluna + NAVIO; j++)
    {
        tabuleiro[linha][j] = 3;
    }
    return 1;
}

int posicionarVertical(int tabuleiro[TAM][TAM], int linha, int coluna)
{
    if (linha < 0 || linha + NAVIO > TAM || coluna < 0 || coluna >= TAM)
    {
        printf("Erro: Navio vertical fora dos limites!\n");
        return 0;
    }
    for (int i = linha; i < linha + NAVIO; i++)
    {
        if (tabuleiro[i][coluna] != 0)
        {
            printf("Erro: Sobreposição no navio vertical!\n");
            return 0;
        }
    }
    for (int i = linha; i < linha + NAVIO; i++)
    {
        tabuleiro[i][coluna] = 3;
    }
    return 1;
}

int main()
{
    int tabuleiro[TAM][TAM];

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            tabuleiro[i][j] = 0;
        }
    }

    printf("=== BATALHA NAVAL - Posicionando Navios ===\n\n");

    int linhaH = 2, colunaH = 3;
    int linhaV = 5, colunaV = 7;

    printf("Posicionando navio HORIZONTAL em (%d, %d) -> (%d, %d)\n",
           linhaH, colunaH, linhaH, colunaH + NAVIO - 1);
    printf("Posicionando navio VERTICAL em (%d, %d) -> (%d, %d)\n\n",
           linhaV, colunaV, linhaV + NAVIO - 1, colunaV);

    int sucesso = 1;
    sucesso &= posicionarHorizontal(tabuleiro, linhaH, colunaH);
    sucesso &= posicionarVertical(tabuleiro, linhaV, colunaV);

    if (!sucesso)
    {
        printf("Falha ao posicionar os navios. Verifique as coordenadas.\n");
        return 1;
    }

    printf("Tabuleiro com os navios posicionados:\n");
    exibirTabuleiro(tabuleiro);

    printf("Dois navios de tamanho %d posicionados com sucesso!\n", NAVIO);
    printf("Legenda: 0 = agua, 3 = navio\n");

    return 0;
}