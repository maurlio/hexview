#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Tamanho do buffer de leitura.
 * 4096 bytes (4KB) alinhado com o tamanho de página de memória.
 */
#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "uso: %s <ficheiro>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_name = argv[1];

    /* Modo binário para garantir leitura byte-a-byte */
    FILE *fp = fopen(file_name, "rb");
    if (!fp)
    {
        printf("hexview: arquivo ou diretório não existe\n");
        return EXIT_FAILURE;
    }

    uint8_t buffer[BUFFER_SIZE];
    size_t bytes_read, total_bytes = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0)
    {
        total_bytes += bytes_read;
    }

    if (ferror(fp))
    {
        fprintf(stderr, "hexview: erro de leitura \n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    printf("hexview: %zu bytes lidos de '%s' \n", total_bytes, file_name);

    fclose(fp);
    return EXIT_FAILURE;
}