#include "hex.h"
#include <stdio.h>
#include <ctype.h>

static const char HEX_CHAR[] = "0123456789abcdef";

void hex_print_line(const uint8_t *buffer, size_t length, size_t offset)
{
    char line[80];
    int p = 0;

    p += snprintf(line + p, 11, "%08zx", offset);

    /* Bytes em Hexadecimal */
    for (size_t i = 0; i < BYTES_PER_LINE; i++)
    {
        if (i < length)
        {
            uint8_t b = buffer[i];
            line[p++] = HEX_CHAR[(b >> 4) & 0x0F];
            line[p++] = HEX_CHAR[b & 0x0F];
            line[p++] = ' ';
        }
        else
        {
            line[p++] = ' ';
            line[p++] = ' ';
            line[p++] = ' ';
        }
    }

    line[p++] = ' ';
    line[p++] = ' ';

    /* Representação ASCII */
    for (size_t i = 0; i < length; i++)
    {
        unsigned char c = buffer[i];
        line[p++] = isprint(c) ? c : '.';
    }

    line[p++] = '\n';

    fwrite(line, 1, p, stdout);
}
