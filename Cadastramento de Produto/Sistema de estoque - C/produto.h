#ifndef PRODUTO_H
#define PRODUTO_H

#include "categoria.h"

#define MAX_PRODUTOS 50

typedef struct {
    int codigo;
    char nome[50];
    char prateleira;
    float precoUnitario;
    int quantidadeEstoque;
    int disponivelVenda;
    int categoria_codigo;   /* codigo da categoria do produto */
    int ativo;              /* 1 = produto normal, 0 = removido (exclusao logica) */
} Produto;

/* Procura um produto pelo codigo (inclui produtos removidos).
   Retorna o indice no array ou -1 se nao achar */
int localizarPorCodigo(int codigo);

/* Procura um produto ativo pelo nome, usando strcmp.
   Retorna o indice no array ou -1 se nao achar */
int buscarPorNome(const char *nome);

/* Imprime os dados completos de um unico produto,
   mostrando o nome da categoria (resolvido pela lista de categorias) */
void imprimirProdutoDetalhado(Produto p, Categoria categorias[], int totalCategorias);

void cadastrarProduto(Categoria categorias[], int totalCategorias);
void listarProdutos(Categoria categorias[], int totalCategorias);
void pesquisarProdutoPorCodigo(Categoria categorias[], int totalCategorias);
void pesquisarProdutoPorNome(Categoria categorias[], int totalCategorias);

/* Registra entrada ou saida de itens no estoque de um produto */
void alterarEstoque(Categoria categorias[], int totalCategorias);

/* Exclusao logica: marca o produto como inativo */
void removerProduto();

/* Persistencia em arquivo de texto */
void carregarProdutos();
void salvarProdutos();

#endif
