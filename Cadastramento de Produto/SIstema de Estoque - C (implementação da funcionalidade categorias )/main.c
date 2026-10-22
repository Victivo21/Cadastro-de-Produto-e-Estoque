#include <stdio.h>
#include "categoria.h"
#include "produto.h"
#include "util.h"   /* usado apenas para lerLinha (leitura da opcao do menu) */

/* =========================================================
   MENU DE LISTAGEM
   ========================================================= */

void menuListagem(Categoria categorias[], int totalCategorias) {
    char entrada[100];
    int opcao;
    int continuar = 1;

    while (continuar) {

        printf("\n");
        printf("===== MENU DE LISTAGEM =====\n");
        printf("1 - Listar todos os produtos\n");
        printf("2 - Voltar ao menu principal\n");
        printf("============================\n");
        printf("Escolha uma opcao: ");

        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%d", &opcao) != 1) {
            printf("Opcao invalida. Tente novamente.\n");
            continue;
        }

        switch (opcao) {

            case 1:
                listarProdutos(categorias, totalCategorias);
                break;

            case 2:
                continuar = 0;
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}

/* =========================================================
   MENU DE PESQUISA
   ========================================================= */

void menuPesquisa(Categoria categorias[], int totalCategorias) {
    char entrada[100];
    int opcao;
    int continuar = 1;

    while (continuar) {

        printf("\n");
        printf("===== MENU DE PESQUISA =====\n");
        printf("1 - Pesquisar por codigo\n");
        printf("2 - Pesquisar por nome\n");
        printf("3 - Voltar ao menu principal\n");
        printf("============================\n");
        printf("Escolha uma opcao: ");

        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%d", &opcao) != 1) {
            printf("Opcao invalida. Tente novamente.\n");
            continue;
        }

        switch (opcao) {

            case 1:
                pesquisarProdutoPorCodigo(categorias, totalCategorias);
                break;

            case 2:
                pesquisarProdutoPorNome(categorias, totalCategorias);
                break;

            case 3:
                continuar = 0;
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}

/* =========================================================
   MENU DE CATEGORIAS
   ========================================================= */

void menuCategorias(Categoria categorias[], int *totalCategorias) {
    char entrada[100];
    int opcao;
    int continuar = 1;

    while (continuar) {

        printf("\n");
        printf("===== MENU DE CATEGORIAS =====\n");
        printf("1 - Cadastrar Categoria\n");
        printf("2 - Listar Categorias\n");
        printf("3 - Voltar\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");

        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%d", &opcao) != 1) {
            printf("Opcao invalida. Tente novamente.\n");
            continue;
        }

        switch (opcao) {

            case 1:
                cadastrarCategoria(categorias, totalCategorias);
                break;

            case 2:
                listarCategorias(categorias, *totalCategorias);
                break;

            case 3:
                continuar = 0;
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}

/* =========================================================
   MENU PRINCIPAL
   ========================================================= */

void exibirMenu() {
    printf("\n");
    printf("===== MENU PRINCIPAL =====\n");
    printf("1 - Cadastrar Produto\n");
    printf("2 - Listar Produtos\n");
    printf("3 - Pesquisar Produto\n");
    printf("4 - Categorias\n");
    printf("5 - Sair\n");
    printf("===========================\n");
    printf("Escolha uma opcao: ");
}

int main(void) {

    char entrada[100];
    int opcao;
    int continuar = 1;

    /* Lista de categorias (separada da lista de produtos) */
    Categoria categorias[MAX_CATEGORIAS];
    int totalCategorias = 0;

    /* Carrega os dados dos arquivos para a memoria */
    carregarCategorias(categorias, &totalCategorias);
    carregarProdutos();

    while (continuar) {

        exibirMenu();

        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%d", &opcao) != 1) {
            printf("Opcao invalida. Tente novamente.\n\n");
            continue;
        }

        switch (opcao) {

            case 1:
                cadastrarProduto(categorias, totalCategorias);
                break;

            case 2:
                menuListagem(categorias, totalCategorias);
                break;

            case 3:
                menuPesquisa(categorias, totalCategorias);
                break;

            case 4:
                menuCategorias(categorias, &totalCategorias);
                break;

            case 5:
                /* Salva as duas listas antes de encerrar */
                salvarCategorias(categorias, totalCategorias);
                salvarProdutos();
                printf("Encerrando o sistema. Ate logo!\n");
                continuar = 0;
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n\n");
                break;
        }
    }

    return 0;
}
