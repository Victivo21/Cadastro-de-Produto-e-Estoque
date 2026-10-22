#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "produto.h"
#include "util.h"

#define ARQUIVO_PRODUTOS "produtos.txt"

/* "Banco de dados" em memoria dos produtos cadastrados */
static Produto estoque[100];
static int totalProdutos = 0;

/* Codigo deve ser um numero inteiro positivo */
static int lerCodigo() {
    char entrada[100];
    int codigo;
    int valido = 0;

    do {
        printf("Codigo do produto: ");
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
static void lerNome(char *nome) {
    int valido = 0;

    do {
        printf("Nome do produto: ");
        lerLinha(nome, 50);

        if (!validarTextoPreenchido(nome)) {
            printf("Erro: o nome nao pode ficar em branco.\n");
        } else {
            valido = 1;
        }

    } while (!valido);
}

/* Prateleira deve ser uma letra entre A e D */
static char lerPrateleira() {
    char entrada[100];
    char prateleira = '\0';
    int valido = 0;

    do {
        printf("Prateleira (A, B, C ou D): ");
        lerLinha(entrada, sizeof(entrada));

        valido = 0;

        if (strlen(entrada) == 1) {
            prateleira = (char)toupper((unsigned char)entrada[0]);

            if (validarLetraNoIntervalo(prateleira, 'A', 'D')) {
                valido = 1;
            }
        }

        if (!valido) {
            printf("Erro: prateleira invalida. Use apenas A, B, C ou D.\n");
        }

    } while (!valido);

    return prateleira;
}

/* Preco unitario deve ser maior que zero */
static float lerPreco() {
    char entrada[100];
    float preco;
    int valido = 0;

    do {
        printf("Preco unitario: ");
        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%f", &preco) == 1 && validarFloatPositivo(preco)) {
            valido = 1;
        } else {
            printf("Erro: o preco deve ser maior que zero.\n");
        }

    } while (!valido);

    return preco;
}

/* Quantidade em estoque deve ser maior ou igual a zero */
static int lerQuantidade() {
    char entrada[100];
    int quantidade;
    int valido = 0;

    do {
        printf("Quantidade em estoque: ");
        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%d", &quantidade) == 1 && validarInteiroNaoNegativo(quantidade)) {
            valido = 1;
        } else {
            printf("Erro: a quantidade nao pode ser negativa.\n");
        }

    } while (!valido);

    return quantidade;
}

/* Categoria deve existir na lista de categorias */
static int lerCategoriaExistente(Categoria categorias[], int totalCategorias) {
    int codigo;
    int valido = 0;

    do {
        codigo = lerCodigoCategoria();

        if (buscarCategoriaPorCodigo(categorias, totalCategorias, codigo) == -1) {
            printf("Erro: nao existe categoria com esse codigo. Tente novamente.\n");
        } else {
            valido = 1;
        }

    } while (!valido);

    return codigo;
}

int localizarPorCodigo(int codigo) {
    int i;

    for (i = 0; i < totalProdutos; i++) {
        if (estoque[i].codigo == codigo) {
            return i;
        }
    }

    return -1;
}

void imprimirProdutoDetalhado(Produto p, Categoria categorias[], int totalCategorias) {
    int pos = buscarCategoriaPorCodigo(categorias, totalCategorias, p.categoriaCodigo);

    printf("Codigo..................: %d\n", p.codigo);
    printf("Nome....................: %s\n", p.nome);
    printf("Prateleira..............: %c\n", p.prateleira);
    printf("Preco unitario..........: %.2f\n", p.precoUnitario);
    printf("Quantidade em estoque...: %d\n", p.quantidadeEstoque);

    if (pos != -1) {
        printf("Categoria...............: %s\n", categorias[pos].nome);
    } else {
        printf("Categoria...............: desconhecida\n");
    }

    printf("Disponivel para venda...: %s (%d)\n",
           p.disponivelVenda ? "Sim" : "Nao",
           p.disponivelVenda);

    printf("-------------------------------------\n");
}

/* =========================================================
   CADASTRO DE PRODUTO
   ========================================================= */

void cadastrarProduto(Categoria categorias[], int totalCategorias) {
    Produto p;

    printf("\n=== Cadastro de Produto ===\n");

    if (totalProdutos >= 100) {
        printf("Erro: limite maximo de produtos atingido.\n\n");
        return;
    }

    if (totalCategorias == 0) {
        printf("Erro: cadastre ao menos uma categoria antes de cadastrar um produto.\n\n");
        return;
    }

    p.codigo = lerCodigo();

    /* Regra do produto: depende da lista de produtos */
    if (localizarPorCodigo(p.codigo) != -1) {
        printf("Erro: ja existe um produto cadastrado com esse codigo.\n\n");
        return;
    }

    lerNome(p.nome);

    p.prateleira = lerPrateleira();

    p.precoUnitario = lerPreco();

    p.quantidadeEstoque = lerQuantidade();

    /* Mostra as categorias existentes e valida o codigo escolhido */
    listarCategorias(categorias, totalCategorias);

    p.categoriaCodigo = lerCategoriaExistente(categorias, totalCategorias);

    /* Disponivel para venda eh calculado pelo sistema */
    p.disponivelVenda = (p.quantidadeEstoque > 0) ? 1 : 0;

    /* Guarda o produto no "banco de dados" em memoria */
    estoque[totalProdutos] = p;
    totalProdutos++;

    printf("\n--- Resumo do Produto Cadastrado ---\n");

    imprimirProdutoDetalhado(p, categorias, totalCategorias);

    printf("\n");
}

/* =========================================================
   LISTAGEM DE PRODUTOS
   ========================================================= */

void listarProdutos(Categoria categorias[], int totalCategorias) {
    int i;

    printf("\n=== Lista de Produtos ===\n");

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n\n");
        return;
    }

    printf("%-6s %-20s %-6s %-10s %-6s %-8s %-30s\n",
           "Cod",
           "Nome",
           "Prat",
           "Preco",
           "Qtd",
           "Disp",
           "Categoria");

    printf("-----------------------------------------------------------------------------------------\n");

    for (i = 0; i < totalProdutos; i++) {
        Produto p = estoque[i];
        int pos = buscarCategoriaPorCodigo(categorias, totalCategorias, p.categoriaCodigo);

        printf("%-6d %-20s %-6c %-10.2f %-6d %-8s %-30s\n",
               p.codigo,
               p.nome,
               p.prateleira,
               p.precoUnitario,
               p.quantidadeEstoque,
               p.disponivelVenda ? "Sim" : "Nao",
               (pos != -1) ? categorias[pos].nome : "desconhecida");
    }

    printf("\nTotal de produtos cadastrados: %d\n\n", totalProdutos);
}

/* =========================================================
   PESQUISA POR CODIGO
   ========================================================= */

void pesquisarProdutoPorCodigo(Categoria categorias[], int totalCategorias) {
    int codigo;
    int indice;

    codigo = lerCodigo();

    indice = localizarPorCodigo(codigo);

    printf("\n");

    if (indice == -1) {
        printf("Nenhum produto encontrado com o codigo %d.\n\n",
               codigo);
    } else {
        printf("--- Produto Encontrado ---\n");

        imprimirProdutoDetalhado(estoque[indice], categorias, totalCategorias);

        printf("\n");
    }
}

/* =========================================================
   PESQUISA POR NOME
   ========================================================= */

void pesquisarProdutoPorNome(Categoria categorias[], int totalCategorias) {
    char busca[50];
    int i;
    int encontrados = 0;

    printf("Nome (ou parte do nome) a pesquisar: ");

    lerLinha(busca, sizeof(busca));

    printf("\n");

    for (i = 0; i < totalProdutos; i++) {

        if (contemIgnorandoCase(estoque[i].nome, busca)) {

            printf("--- Produto Encontrado ---\n");

            imprimirProdutoDetalhado(estoque[i], categorias, totalCategorias);

            encontrados++;
        }
    }

    if (encontrados == 0) {

        printf("Nenhum produto encontrado com o nome \"%s\".\n",
               busca);

    } else {

        printf("Total encontrado: %d\n",
               encontrados);
    }

    printf("\n");
}

/* =========================================================
   PERSISTENCIA EM ARQUIVO
   Formato: um produto por linha ->
   codigo;prateleira;preco;quantidade;disponivel;categoria;nome
   ========================================================= */

void carregarProdutos() {
    FILE *arq = fopen(ARQUIVO_PRODUTOS, "r");
    char linha[200];
    Produto p;

    totalProdutos = 0;

    /* Primeira execucao: arquivo ainda nao existe, lista comeca vazia */
    if (arq == NULL) {
        return;
    }

    while (totalProdutos < 100 && fgets(linha, sizeof(linha), arq) != NULL) {
        if (sscanf(linha, "%d;%c;%f;%d;%d;%d;%49[^\n]",
                   &p.codigo,
                   &p.prateleira,
                   &p.precoUnitario,
                   &p.quantidadeEstoque,
                   &p.disponivelVenda,
                   &p.categoriaCodigo,
                   p.nome) == 7) {
            estoque[totalProdutos] = p;
            totalProdutos++;
        }
    }

    fclose(arq);
}

void salvarProdutos() {
    FILE *arq = fopen(ARQUIVO_PRODUTOS, "w");
    int i;

    if (arq == NULL) {
        printf("Erro: nao foi possivel salvar o arquivo de produtos.\n");
        return;
    }

    for (i = 0; i < totalProdutos; i++) {
        fprintf(arq, "%d;%c;%.2f;%d;%d;%d;%s\n",
                estoque[i].codigo,
                estoque[i].prateleira,
                estoque[i].precoUnitario,
                estoque[i].quantidadeEstoque,
                estoque[i].disponivelVenda,
                estoque[i].categoriaCodigo,
                estoque[i].nome);
    }

    fclose(arq);
}
