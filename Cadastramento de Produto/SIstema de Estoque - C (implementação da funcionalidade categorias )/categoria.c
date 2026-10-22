#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "util.h"

#define ARQUIVO_CATEGORIAS "categorias.txt"

int buscarCategoriaPorCodigo(Categoria lista[], int total, int codigo) {
    int i;

    for (i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }

    return -1;
}

/* Codigo deve ser um numero inteiro positivo */
int lerCodigoCategoria() {
    char entrada[100];
    int codigo;
    int valido = 0;

    do {
        printf("Codigo da categoria: ");
        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%d", &codigo) == 1 && validarInteiroPositivo(codigo)) {
            valido = 1;
        } else {
            printf("Erro: o codigo deve ser um numero inteiro positivo.\n");
        }
    } while (!valido);

    return codigo;
}

/* Nome nao pode ficar em branco */
static void lerNomeCategoria(char *nome) {
    int valido = 0;

    do {
        printf("Nome da categoria: ");
        lerLinha(nome, 30);

        if (!validarTextoPreenchido(nome)) {
            printf("Erro: o nome nao pode ficar em branco.\n");
        } else {
            valido = 1;
        }

    } while (!valido);
}

/* =========================================================
   CADASTRO DE CATEGORIA
   ========================================================= */

void cadastrarCategoria(Categoria lista[], int *total) {
    Categoria c;

    printf("\n=== Cadastro de Categoria ===\n");

    if (*total >= MAX_CATEGORIAS) {
        printf("Erro: limite maximo de categorias atingido.\n\n");
        return;
    }

    c.codigo = lerCodigoCategoria();

    if (buscarCategoriaPorCodigo(lista, *total, c.codigo) != -1) {
        printf("Erro: ja existe uma categoria cadastrada com esse codigo.\n\n");
        return;
    }

    lerNomeCategoria(c.nome);

    lista[*total] = c;
    (*total)++;

    printf("\nCategoria cadastrada com sucesso.\n\n");
}

/* =========================================================
   LISTAGEM DE CATEGORIAS
   ========================================================= */

void listarCategorias(Categoria lista[], int total) {
    int i;

    printf("\n=== Lista de Categorias ===\n");

    if (total == 0) {
        printf("Nenhuma categoria cadastrada.\n\n");
        return;
    }

    printf("%-6s %-30s\n", "Cod", "Nome");

    printf("---------------------------------------\n");

    for (i = 0; i < total; i++) {
        printf("%-6d %-30s\n", lista[i].codigo, lista[i].nome);
    }

    printf("\nTotal de categorias cadastradas: %d\n\n", total);
}

/* =========================================================
   PERSISTENCIA EM ARQUIVO
   Formato: uma categoria por linha -> codigo;nome
   ========================================================= */

void carregarCategorias(Categoria lista[], int *total) {
    FILE *arq = fopen(ARQUIVO_CATEGORIAS, "r");
    char linha[200];
    Categoria c;

    *total = 0;

    /* Primeira execucao: arquivo ainda nao existe, lista comeca vazia */
    if (arq == NULL) {
        return;
    }

    while (*total < MAX_CATEGORIAS && fgets(linha, sizeof(linha), arq) != NULL) {
        if (sscanf(linha, "%d;%29[^\n]", &c.codigo, c.nome) == 2) {
            lista[*total] = c;
            (*total)++;
        }
    }

    fclose(arq);
}

void salvarCategorias(Categoria lista[], int total) {
    FILE *arq = fopen(ARQUIVO_CATEGORIAS, "w");
    int i;

    if (arq == NULL) {
        printf("Erro: nao foi possivel salvar o arquivo de categorias.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        fprintf(arq, "%d;%s\n", lista[i].codigo, lista[i].nome);
    }

    fclose(arq);
}
