#ifndef HEX_H
#define HEX_H

#include <stdint.h>
#include <stddef.h>

/**
 * Número máximo de bytes exibidos/processados em cada linha
 */
#define BYTES_PER_LINE 16

/**
 * Imprimi uma linha formatada.
 */
void hex_print_line(const uint8_t *buffer, size_t length, size_t offset);

#endif