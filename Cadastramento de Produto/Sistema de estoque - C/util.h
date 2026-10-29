#ifndef UTIL_H
#define UTIL_H

/* Le uma linha inteira do teclado, remove o '\n' e limpa o buffer se sobrar algo */
void lerLinha(char *buffer, int tamanho);

/* Retorna 1 se o numero for maior que zero (ex.: codigo) */
int validarInteiroPositivo(int numero);

/* Retorna 1 se o numero for maior ou igual a zero (ex.: quantidade) */
int validarInteiroNaoNegativo(int numero);

/* Retorna 1 se o numero for maior que zero (ex.: preco) */
int validarFloatPositivo(float numero);

/* Retorna 1 se o texto tiver pelo menos um caractere diferente de espaco */
int validarTextoPreenchido(const char *texto);

/* Retorna 1 se o caractere estiver entre 'minimo' e 'maximo' (inclusive) */
int validarLetraNoIntervalo(char letra, char minimo, char maximo);

/* Verifica se 'busca' esta contido em 'texto', ignorando maiusculas/minusculas */
int contemIgnorandoCase(const char *texto, const char *busca);

#endif
