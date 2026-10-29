#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "produto.h"
#include "util.h"

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

void imprimirProdutoDetalhado(Produto p) {
    printf("Codigo..................: %d\n", p.codigo);
    printf("Nome....................: %s\n", p.nome);
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

void cadastrarProduto() {
    Produto p;

    printf("\n=== Cadastro de Produto ===\n");

    if (totalProdutos >= 100) {
        printf("Erro: limite maximo de produtos atingido.\n\n");
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

    /* Disponivel para venda eh calculado pelo sistema */
    p.disponivelVenda = (p.quantidadeEstoque > 0) ? 1 : 0;

    /* Produto novo comeca ativo */
    p.ativo = 1;

    /* Guarda o produto no "banco de dados" em memoria */
    estoque[totalProdutos] = p;
    totalProdutos++;

    printf("\n--- Resumo do Produto Cadastrado ---\n");

    imprimirProdutoDetalhado(p);

    printf("\n");
}

/* =========================================================
   LISTAGEM DE PRODUTOS
   ========================================================= */

void listarProdutos() {
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

    printf("%-6s %-20s %-6s %-10s %-6s %-8s\n",
           "Cod",
           "Nome",
           "Prat",
           "Preco",
           "Qtd",
           "Disp");

    printf("---------------------------------------------------------\n");

    for (i = 0; i < totalProdutos; i++) {
        Produto p = estoque[i];

        if (!p.ativo) {
            continue;
        }

        printf("%-6d %-20s %-6c %-10.2f %-6d %-8s\n",
               p.codigo,
               p.nome,
               p.prateleira,
               p.precoUnitario,
               p.quantidadeEstoque,
               p.disponivelVenda ? "Sim" : "Nao");
    }

    printf("\nTotal de produtos cadastrados: %d\n\n", exibidos);
}

/* =========================================================
   PESQUISA POR CODIGO
   ========================================================= */

void pesquisarProdutoPorCodigo() {
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

        imprimirProdutoDetalhado(estoque[indice]);

        printf("\n");
    }
}

/* =========================================================
   PESQUISA POR NOME
   ========================================================= */

void pesquisarProdutoPorNome() {
    char busca[50];
    int i;
    int encontrados = 0;

    printf("Nome (ou parte do nome) a pesquisar: ");

    lerLinha(busca, sizeof(busca));

    printf("\n");

    for (i = 0; i < totalProdutos; i++) {

        if (!estoque[i].ativo) {
            continue;
        }

        if (contemIgnorandoCase(estoque[i].nome, busca)) {

            printf("--- Produto Encontrado ---\n");

            imprimirProdutoDetalhado(estoque[i]);

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
   ALTERAR ESTOQUE
   ========================================================= */

void alterarEstoque() {
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

    imprimirProdutoDetalhado(estoque[indice]);

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
