#include "hex.h"
#include <stdio.h>
#include <ctype.h>

void hex_print_line(const uint8_t *buffer, size_t length, size_t offset)
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
