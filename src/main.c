#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define BUFFER_SIZE 4096
#define BYTES_PER_LINE 16

/**
 * Imprimi uma linha formatada.
 */
void print_hex_line(const uint8_t *buffer, size_t length, size_t offset)
{
    printf("%08zx: ", offset);

    /* Bytes em Hexadecimal */
    for (size_t i = 0; i < BYTES_PER_LINE; i++)
    {
        if (i < length)
        {
            printf("%02x ", buffer[i]);
        }
        else
        {
            printf("    ");
        }
    }

    printf(" ");

    /* Representação ASCII */
    for (size_t i = 0; i < BYTES_PER_LINE; i++)
    {
        if (i < length)
        {
            unsigned char c = buffer[i];
            printf("%c", isprint((int)c) ? c : '.');
        }
    }

    printf("\n");
}

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
    size_t bytes_read, global_offset = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0)
    {
        for (size_t i = 0; i < bytes_read; i += BYTES_PER_LINE)
        {
            size_t line_length = BYTES_PER_LINE;
            if (i + line_length > bytes_read)
            {
                line_length = bytes_read - i;
            }

            print_hex_line(buffer + i, line_length, global_offset + i);
        }

        global_offset += bytes_read;
    }

    if (ferror(fp))
    {
        fprintf(stderr, "hexview: erro de leitura \n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_FAILURE;
}