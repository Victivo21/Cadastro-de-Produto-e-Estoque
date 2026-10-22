#ifndef PRODUTO_H
#define PRODUTO_H

#include "categoria.h"

typedef struct {
    int codigo;
    char nome[50];
    char prateleira;
    float precoUnitario;
    int quantidadeEstoque;
    int disponivelVenda;
    int categoriaCodigo;  /* so o codigo; o nome fica na lista de categorias */
} Produto;

/* Procura um produto pelo codigo.
   Retorna o indice no array ou -1 se nao achar */
int localizarPorCodigo(int codigo);

/* Imprime os dados completos de um unico produto,
   buscando o nome da categoria na lista de categorias */
void imprimirProdutoDetalhado(Produto p, Categoria categorias[], int totalCategorias);

void cadastrarProduto(Categoria categorias[], int totalCategorias);
void listarProdutos(Categoria categorias[], int totalCategorias);
void pesquisarProdutoPorCodigo(Categoria categorias[], int totalCategorias);
void pesquisarProdutoPorNome(Categoria categorias[], int totalCategorias);

/* Persistencia em arquivo de texto */
void carregarProdutos();
void salvarProdutos();

#endif
