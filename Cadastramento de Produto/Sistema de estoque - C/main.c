#include <stdio.h>
#include "produto.h"
#include "categoria.h"
#include "util.h"   /* usado apenas para lerLinha (leitura da opcao do menu) */

/* =========================================================
   MENU DE LISTAGEM
   ========================================================= */

void menuListagem() {
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
                listarProdutos();
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

void menuPesquisa() {
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
                pesquisarProdutoPorCodigo();
                break;

            case 2:
                pesquisarProdutoPorNome();
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
        printf("3 - Voltar ao menu principal\n");
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
                salvarCategorias(categorias, *totalCategorias);
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
    printf("4 - Alterar Estoque de um Produto\n");
    printf("5 - Remover Produto\n");
    printf("6 - Categorias\n");
    printf("7 - Sair\n");
    printf("===========================\n");
    printf("Escolha uma opcao: ");
}

int main(void) {

    char entrada[100];
    int opcao;
    int continuar = 1;

    Categoria categorias[MAX_CATEGORIAS];
    int totalCategorias = 0;

    carregarCategorias(categorias, &totalCategorias);

    while (continuar) {

        exibirMenu();

        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%d", &opcao) != 1) {
            printf("Opcao invalida. Tente novamente.\n\n");
            continue;
        }

        switch (opcao) {

            case 1:
                cadastrarProduto();
                break;

            case 2:
                menuListagem();
                break;

            case 3:
                menuPesquisa();
                break;

            case 4:
                alterarEstoque();
                break;

            case 5:
                removerProduto();
                break;

            case 6:
                menuCategorias(categorias, &totalCategorias);
                break;

            case 7:
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
