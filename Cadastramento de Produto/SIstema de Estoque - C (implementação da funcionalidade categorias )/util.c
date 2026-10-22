#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

void lerLinha(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        size_t len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

int validarInteiroPositivo(int numero) {
    return numero > 0;
}

int validarInteiroNaoNegativo(int numero) {
    return numero >= 0;
}

int validarFloatPositivo(float numero) {
    return numero > 0;
}

int validarTextoPreenchido(const char *texto) {
    int i = 0;

    while (texto[i] == ' ')
        i++;

    return !(strlen(texto) == 0 || texto[i] == '\0');
}

int validarLetraNoIntervalo(char letra, char minimo, char maximo) {
    return letra >= minimo && letra <= maximo;
}

int contemIgnorandoCase(const char *texto, const char *busca) {
    char t[50], b[50];
    int i;

    for (i = 0; texto[i] != '\0' && i < 50 - 1; i++) {
        t[i] = (char)tolower((unsigned char)texto[i]);
    }

    t[i] = '\0';

    for (i = 0; busca[i] != '\0' && i < 50 - 1; i++) {
        b[i] = (char)tolower((unsigned char)busca[i]);
    }

    b[i] = '\0';

    return strstr(t, b) != NULL;
}
