#include <stdio.h>

#define TAM 10
#define SH 7
#define HC (SH / 2)

int tabuleiro[TAM][TAM] = {0};

int cone[SH][SH] = {0};
int cruz[SH][SH] = {0};
int octaedro[SH][SH] = {0};

void construirCone(void)
{
    for (int i = 0; i < SH; i++)
    {
        int distancia = i - HC;
        int largura = distancia + 1;
        if (distancia < 0)
            largura = 0;

        int colInicio = HC - largura;
        int colFim = HC + largura;

        for (int j = 0; j < SH; j++)
        {
            cone[i][j] = (j >= colInicio && j <= colFim) ? 1 : 0;
        }
    }
}

void construirCruz(void)
{
    for (int i = 0; i < SH; i++)
        for (int j = 0; j < SH; j++)
            cruz[i][j] = (i == HC || j == HC) ? 1 : 0;
}

void construirOctaedro(void)
{
    for (int i = 0; i < SH; i++)
    {
        int di = (i < HC) ? i : SH - 1 - i;
        for (int j = 0; j < SH; j++)
        {
            int dj = (j < HC) ? j : SH - 1 - j;
            octaedro[i][j] = (di + dj <= HC) ? 1 : 0;
        }
    }
}

int podePosicionar(int li, int ci, int di, int dj)
{
    int i = li, j = ci;
    for (int k = 0; k < 3; k++)
    {
        if (i < 0 || i >= TAM || j < 0 || j >= TAM)
            return 0;
        if (tabuleiro[i][j] != 0)
            return 0;
        i += di;
        j += dj;
    }
    return 1;
}
void posicionarNavio(int li, int ci, int di, int dj)
{
    int i = li, j = ci;
    for (int k = 0; k < 3; k++)
    {
        tabuleiro[i][j] = 3;
        i += di;
        j += dj;
    }
}

void aplicarHabilidade(int hab[SH][SH], int lc, int cc)
{
    int di0 = lc - HC;
    int dj0 = cc - HC;

    for (int hi = 0; hi < SH; hi++)
    {
        int ti = di0 + hi;
        if (ti < 0 || ti >= TAM)
            continue;

        for (int hj = 0; hj < SH; hj++)
        {
            int tj = dj0 + hj;
            if (tj < 0 || tj >= TAM)
                continue;

            if (hab[hi][hj] == 1)
            {
                if (tabuleiro[ti][tj] != 3)
                    tabuleiro[ti][tj] = 5;
            }
        }
    }
}

void exibirTabuleiro(void)
{
    printf("   ");
    for (int c = 0; c < TAM; c++)
        printf("%2d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++)
    {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++)
        {
            switch (tabuleiro[i][j])
            {
            case 0:
                printf(" 0 ");
                break;
            case 3:
                printf(" 3 ");
                break;
            case 5:
                printf(" 5 ");
                break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    if (podePosicionar(1, 2, 0, 1))
        posicionarNavio(1, 2, 0, 1);
    if (podePosicionar(6, 7, 1, 0))
        posicionarNavio(6, 7, 1, 0);
    if (podePosicionar(3, 1, 1, 1))
        posicionarNavio(3, 1, 1, 1);
    if (podePosicionar(8, 5, 1, -1))
        posicionarNavio(8, 5, 1, -1);

    construirCone();
    construirCruz();
    construirOctaedro();

    aplicarHabilidade(cone, 4, 4);
    aplicarHabilidade(cruz, 2, 7);
    aplicarHabilidade(octaedro, 7, 2);

    printf("=== BATALHA NAVAL – HABILIDADES ESPECIAIS ===\n");
    printf("Legenda:\n");
    printf("  0  = Água\n");
    printf("  3  = Navio\n");
    printf("  5  = Área afetada por habilidade\n\n");

    exibirTabuleiro();

    printf("Habilidades aplicadas:\n");
    printf("  • Cone     centrado em (4,4)\n");
    printf("  • Cruz     centrada em (2,7)\n");
    printf("  • Octaedro centrado em (7,2)\n");

    return 0;
}