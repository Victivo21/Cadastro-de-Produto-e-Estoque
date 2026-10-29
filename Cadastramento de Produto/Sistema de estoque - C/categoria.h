#ifndef CATEGORIA_H
#define CATEGORIA_H

#define MAX_CATEGORIAS 20

typedef struct {
    int codigo;
    char nome[30];
} Categoria;

/* Procura uma categoria pelo codigo na lista recebida.
   Retorna a posicao no array ou -1 se nao achar */
int buscarCategoriaPorCodigo(Categoria lista[], int total, int codigo);

/* Le do teclado um codigo de categoria (numero inteiro positivo) */
int lerCodigoCategoria();

void cadastrarCategoria(Categoria lista[], int *total);
void listarCategorias(Categoria lista[], int total);

/* Persistencia em arquivo de texto */
void carregarCategorias(Categoria lista[], int *total);
void salvarCategorias(Categoria lista[], int total);

#endif
