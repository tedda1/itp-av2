#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_ESTUDANTES 10
#define NUM_NOTAS 3
#define TAM_NOME 50
#define META 6.0


static void ler_linha(char *buf, size_t tam) {
    if (fgets(buf, (int)tam, stdin) == NULL) {
        printf("\nEntrada encerrada.\n");
        exit(1);
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
}


static double ler_numero(const char *msg, double min, double max) {
    char linha[64];
    for (;;) {
        printf("%s", msg);
        ler_linha(linha, sizeof linha);
        for (char *p = linha; *p; p++) {
            if (*p == ',') *p = '.';          
        }
        char *fim;
        double v = strtod(linha, &fim);
        while (*fim != '\0' && isspace((unsigned char)*fim)) fim++;
        if (fim == linha || *fim != '\0') {
            printf("  Entrada invalida. Digite um numero.\n");
        } else if (v < min || v > max) {
            printf("  Valor fora do intervalo [%.0f, %.0f]. Tente novamente.\n", min, max);
        } else {
            return v;
        }
    }
}


static void ler_nome(char *nome, size_t tam, int numero) {
    for (;;) {
        printf("Nome do estudante %d: ", numero);
        ler_linha(nome, tam);
        int vazio = 1;
        for (char *p = nome; *p; p++) {
            if (!isspace((unsigned char)*p)) { vazio = 0; break; }
        }
        if (!vazio) return;
        printf("  O nome nao pode ser vazio.\n");
    }
}


static void calcular_medias(float notas[][NUM_NOTAS], int n, double *medias) {
    for (int i = 0; i < n; i++) {
        double soma = 0.0;
        for (int j = 0; j < NUM_NOTAS; j++) {
            soma += notas[i][j];
        }
        medias[i] = soma / NUM_NOTAS;         
    }
}

static void exibir_tabela(char nomes[][TAM_NOME], float notas[][NUM_NOTAS],
                          const double *medias, int n) {
    printf("\n%-20s %6s %6s %6s %8s  %s\n", "Nome", "Nota1", "Nota2", "Nota3", "Media", "Situacao");
    for (int i = 0; i < n; i++) {
        printf("%-20.20s", nomes[i]);
        for (int j = 0; j < NUM_NOTAS; j++) {
            printf(" %6.1f", notas[i][j]);
        }
        printf(" %8.2f  %s\n", medias[i],
               medias[i] >= META ? "atingiu a meta" : "abaixo da meta");
    }
}

static void exibir_resumo(char nomes[][TAM_NOME], const double *medias, int n) {
    double soma = 0.0, maior = medias[0];
    for (int i = 0; i < n; i++) {
        soma += medias[i];
        if (medias[i] > maior) maior = medias[i];
    }
    printf("\nMedia geral da turma: %.2f\n", soma / n);
    printf("Maior media (%.2f): ", maior);
    int primeiro = 1;
    for (int i = 0; i < n; i++) {
        if (fabs(medias[i] - maior) < 1e-9) {
            printf("%s%s", primeiro ? "" : ", ", nomes[i]);
            primeiro = 0;
        }
    }
    printf("\n");
}

int main(void) {
    char nomes[MAX_ESTUDANTES][TAM_NOME];
    float notas[MAX_ESTUDANTES][NUM_NOTAS];

    double qtd;
    for (;;) {
        qtd = ler_numero("Quantidade de estudantes (1 a 10): ", 1, MAX_ESTUDANTES);
        if (qtd == floor(qtd)) break;
        printf("  A quantidade deve ser um numero inteiro.\n");
    }
    int n = (int)qtd;

    for (int i = 0; i < n; i++) {
        ler_nome(nomes[i], TAM_NOME, i + 1);
        for (int j = 0; j < NUM_NOTAS; j++) {
            char msg[40];
            snprintf(msg, sizeof msg, "  Nota %d (0 a 10): ", j + 1);
            notas[i][j] = (float)ler_numero(msg, 0.0, 10.0);
        }
    }

    double *medias = calloc((size_t)n, sizeof *medias);   /* heap, zerado */
    if (medias == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
        return 1;
    }

    calcular_medias(notas, n, medias);
    exibir_tabela(nomes, notas, medias, n);
    exibir_resumo(nomes, medias, n);

    free(medias);
    medias = NULL;
    return 0;
}
