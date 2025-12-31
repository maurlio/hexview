#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hex.h"

#define BUFFER_SIZE 65536

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "uso: %s <ficheiro>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Modo binário para garantir leitura byte-a-byte */
    FILE *fp = fopen(argv[1], "rb");
    if (!fp)
    {
        printf("hexview: arquivo ou diretório não existe\n");
        return EXIT_FAILURE;
    }

    /* Buffer de saída de 64KB para reduzir syscalls de escrita */
    char out_buffer[BUFFER_SIZE];
    setvbuf(stdout, out_buffer, _IOFBF, sizeof(out_buffer));

    uint8_t buffer[BUFFER_SIZE];
    size_t bytes_read, global_offset = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0)
    {
        for (size_t i = 0; i < bytes_read; i += BYTES_PER_LINE)
        {
            size_t line_length = (i + BYTES_PER_LINE <= bytes_read)
                                     ? BYTES_PER_LINE
                                     : bytes_read - i;

            hex_print_line(buffer + i, line_length, global_offset + i);
        }

        global_offset += bytes_read;
    }

    if (ferror(fp))
    {
        fprintf(stderr, "hexview: erro ao ler o arquivo \n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_FAILURE;
}