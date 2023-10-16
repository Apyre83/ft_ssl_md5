
#include "ft_ssl.h"

static const char encoding_table_base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


uint8_t *base64_decode(const char *input, uint32_t *len) {

    (void) input;
    (void) len;
    return (NULL);
}


uint8_t *base64_encode(const char *input, uint32_t *len) {
    if (input == NULL || len == NULL) {
        return NULL;
    }

    uint32_t output_length = (((*len + 2) / 3) * 4);
    uint8_t *output = (uint8_t *)malloc(output_length + 1);  // +1 for the null terminator
    if (!output) return NULL;

    uint32_t i = 0, j = 0;
    while (i < *len) {
        uint32_t octet_a = i < *len ? (unsigned char) input[i++] : 0;
        uint32_t octet_b = i < *len ? (unsigned char) input[i++] : 0;
        uint32_t octet_c = i < *len ? (unsigned char) input[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        output[j++] = encoding_table_base64[(triple >> 3 * 6) & 0x3F];
        output[j++] = encoding_table_base64[(triple >> 2 * 6) & 0x3F];
        output[j++] = encoding_table_base64[(triple >> 1 * 6) & 0x3F];
        output[j++] = encoding_table_base64[(triple >> 0 * 6) & 0x3F];
    }

    /* Padding with '=' */
    for (uint32_t k = 0; k < (3 - (*len % 3)) % 3; k++) {
        output[j++] = '=';
    }

    output[j] = '\0';  // Terminating the string
    ft_printf("output: %s\n", output);

    return output;
}
