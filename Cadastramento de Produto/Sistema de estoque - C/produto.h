#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int codigo;
    char nome[50];
    char prateleira;
    float precoUnitario;
    int quantidadeEstoque;
    int disponivelVenda;
    int ativo;              /* 1 = produto normal, 0 = removido (exclusao logica) */
} Produto;

/* Procura um produto pelo codigo.
   Retorna o indice no array ou -1 se nao achar */
int localizarPorCodigo(int codigo);

/* Imprime os dados completos de um unico produto */
void imprimirProdutoDetalhado(Produto p);

void cadastrarProduto();
void listarProdutos();
void pesquisarProdutoPorCodigo();
void pesquisarProdutoPorNome();

/* Registra entrada ou saida de itens no estoque de um produto */
void alterarEstoque();

/* Exclusao logica: marca o produto como inativo */
void removerProduto();

#endif
