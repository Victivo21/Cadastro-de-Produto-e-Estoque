#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "produto.h"
#include "categoria.h"
#include "util.h"

#define ARQUIVO_PRODUTOS "produtos.txt"

/* "Banco de dados" em memoria dos produtos cadastrados */
static Produto estoque[MAX_PRODUTOS];
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

/* Categoria do produto deve existir na lista de categorias */
static int lerCategoriaProduto(Categoria categorias[], int totalCategorias) {
    int codigo;
    int valido = 0;

    do {
        codigo = lerCodigoCategoria();

        if (buscarCategoriaPorCodigo(categorias, totalCategorias, codigo) != -1) {
            valido = 1;
        } else {
            printf("Erro: nao existe categoria cadastrada com esse codigo.\n");
        }

    } while (!valido);

    return codigo;
}

/* Tipo da movimentacao: 1 = entrada, 2 = saida */
static int lerTipoMovimentacao() {
    char entrada[100];
    int tipo;
    int valido = 0;

    do {
        printf("Tipo de movimentacao (1 - Entrada, 2 - Saida): ");
        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%d", &tipo) == 1 && (tipo == 1 || tipo == 2)) {
            valido = 1;
        } else {
            printf("Erro: digite 1 para entrada ou 2 para saida.\n");
        }

    } while (!valido);

    return tipo;
}

/* Quantidade da movimentacao deve ser um inteiro positivo */
static int lerQuantidadeMovimentacao() {
    char entrada[100];
    int quantidade;
    int valido = 0;

    do {
        printf("Quantidade: ");
        lerLinha(entrada, sizeof(entrada));

        if (sscanf(entrada, "%d", &quantidade) == 1 && validarInteiroPositivo(quantidade)) {
            valido = 1;
        } else {
            printf("Erro: a quantidade deve ser um numero inteiro positivo.\n");
        }

    } while (!valido);

    return quantidade;
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

int buscarPorNome(const char *nome) {
    int i;

    for (i = 0; i < totalProdutos; i++) {
        if (estoque[i].ativo && strcmp(estoque[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

void imprimirProdutoDetalhado(Produto p, Categoria categorias[], int totalCategorias) {
    int posCategoria = buscarCategoriaPorCodigo(categorias, totalCategorias, p.categoria_codigo);

    printf("Codigo..................: %d\n", p.codigo);
    printf("Nome....................: %s\n", p.nome);
    printf("Categoria...............: %s\n",
           posCategoria != -1 ? categorias[posCategoria].nome : "(categoria nao encontrada)");
    printf("Prateleira..............: %c\n", p.prateleira);
    printf("Preco unitario..........: %.2f\n", p.precoUnitario);
    printf("Quantidade em estoque...: %d\n", p.quantidadeEstoque);

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

    if (totalProdutos >= MAX_PRODUTOS) {
        printf("Erro: limite maximo de produtos atingido.\n\n");
        return;
    }

    if (totalCategorias == 0) {
        printf("Erro: nenhuma categoria cadastrada. Cadastre uma categoria antes de cadastrar produtos.\n\n");
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

    p.categoria_codigo = lerCategoriaProduto(categorias, totalCategorias);

    /* Disponivel para venda eh calculado pelo sistema */
    p.disponivelVenda = (p.quantidadeEstoque > 0) ? 1 : 0;

    /* Produto novo comeca ativo */
    p.ativo = 1;

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
    int exibidos = 0;

    printf("\n=== Lista de Produtos ===\n");

    for (i = 0; i < totalProdutos; i++) {
        if (estoque[i].ativo) {
            exibidos++;
        }
    }

    if (exibidos == 0) {
        printf("Nenhum produto cadastrado.\n\n");
        return;
    }

    printf("\n");

    for (i = 0; i < totalProdutos; i++) {
        if (estoque[i].ativo) {
            imprimirProdutoDetalhado(estoque[i], categorias, totalCategorias);
        }
    }

    printf("\nTotal de produtos cadastrados: %d\n\n", exibidos);
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

    if (indice == -1 || !estoque[indice].ativo) {
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
    int indice;

    printf("Nome do produto a pesquisar: ");

    lerLinha(busca, sizeof(busca));

    indice = buscarPorNome(busca);

    printf("\n");

    if (indice == -1) {
        printf("Nenhum produto encontrado com o nome \"%s\".\n\n",
               busca);
    } else {
        printf("--- Produto Encontrado ---\n");

        imprimirProdutoDetalhado(estoque[indice], categorias, totalCategorias);

        printf("\n");
    }
}

/* =========================================================
   ALTERAR ESTOQUE
   ========================================================= */

void alterarEstoque(Categoria categorias[], int totalCategorias) {
    int codigo;
    int indice;
    int tipo;
    int quantidade;

    printf("\n=== Alterar Estoque de um Produto ===\n");

    codigo = lerCodigo();

    indice = localizarPorCodigo(codigo);

    if (indice == -1 || !estoque[indice].ativo) {
        printf("Nenhum produto encontrado com o codigo %d.\n\n", codigo);
        return;
    }

    tipo = lerTipoMovimentacao();

    quantidade = lerQuantidadeMovimentacao();

    if (tipo == 1) {
        estoque[indice].quantidadeEstoque += quantidade;
    } else {
        if (quantidade > estoque[indice].quantidadeEstoque) {
            printf("Erro: a saida (%d) e maior que o estoque atual (%d). Operacao nao realizada.\n\n",
                   quantidade,
                   estoque[indice].quantidadeEstoque);
            return;
        }

        estoque[indice].quantidadeEstoque -= quantidade;
    }

    /* Disponivel para venda eh sempre calculado a partir da quantidade */
    estoque[indice].disponivelVenda = (estoque[indice].quantidadeEstoque > 0) ? 1 : 0;

    printf("\nEstoque atualizado com sucesso.\n");

    imprimirProdutoDetalhado(estoque[indice], categorias, totalCategorias);

    printf("\n");
}

/* =========================================================
   REMOVER PRODUTO (EXCLUSAO LOGICA)
   ========================================================= */

void removerProduto() {
    int codigo;
    int indice;

    printf("\n=== Remover Produto ===\n");

    codigo = lerCodigo();

    indice = localizarPorCodigo(codigo);

    if (indice == -1 || !estoque[indice].ativo) {
        printf("Nenhum produto encontrado com o codigo %d.\n\n", codigo);
        return;
    }

    estoque[indice].ativo = 0;

    printf("\nProduto removido com sucesso.\n\n");
}

/* =========================================================
   PERSISTENCIA EM ARQUIVO
   Formato: um produto por linha ->
   codigo;prateleira;preco;quantidade;disponivel;categoria_codigo;ativo;nome
   (o nome fica por ultimo para nao quebrar se tiver ';')
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

    while (totalProdutos < MAX_PRODUTOS && fgets(linha, sizeof(linha), arq) != NULL) {
        if (sscanf(linha, "%d;%c;%f;%d;%d;%d;%d;%49[^\n]",
                   &p.codigo,
                   &p.prateleira,
                   &p.precoUnitario,
                   &p.quantidadeEstoque,
                   &p.disponivelVenda,
                   &p.categoria_codigo,
                   &p.ativo,
                   p.nome) == 8) {
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

    /* Grava todos, inclusive os removidos (ativo = 0) */
    for (i = 0; i < totalProdutos; i++) {
        fprintf(arq, "%d;%c;%f;%d;%d;%d;%d;%s\n",
                estoque[i].codigo,
                estoque[i].prateleira,
                estoque[i].precoUnitario,
                estoque[i].quantidadeEstoque,
                estoque[i].disponivelVenda,
                estoque[i].categoria_codigo,
                estoque[i].ativo,
                estoque[i].nome);
    }

    fclose(arq);
}
