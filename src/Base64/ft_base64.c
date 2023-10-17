
#include "ft_ssl.h"

static const char base64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int is_base64(unsigned char c) { return (ft_isalnum(c) || (c == '+') || (c == '/')); }
int ft_isspace(int c) { return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'); }


uint8_t *base64_decode(const char *encoded_string, uint32_t *output_length) {
    int in_len = ft_strlen(encoded_string);
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    uint8_t *ret = (uint8_t *)ft_calloc(in_len * 3 / 4, sizeof(uint8_t));  // Allocated size might need adjustment.
    uint8_t *output_ptr = ret;

    if (ret == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    while (in_len-- && (encoded_string[in_] != '=')) {
        if (!is_base64(encoded_string[in_])) { if (!ft_isspace(encoded_string[in_])) { ft_printf("Error, invalid character at position %d.\n", in_); free(ret); return(NULL); } in_++; continue; }
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = ft_strchr(base64_table, char_array_4[i]) - base64_table;

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                *output_ptr++ = char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = ft_strchr(base64_table, char_array_4[j]) - base64_table;

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++)
            *output_ptr++ = char_array_3[j];
    }

    *output_length = output_ptr - ret;  // Calculate the actual output length.
    return ret;
}



uint8_t *base64_encode(const char *input, uint32_t *len) {
#ifdef DEBUG
	ft_printf("decode base64, input: {%s}\n", input);
#endif
    if (input == NULL || len == NULL) {
        return NULL;
    }
    uint32_t	olen = 4 * ((*len + 2) / 3);

    if (olen < *len) {
        return NULL;
    }

    uint8_t *output = (uint8_t *)ft_calloc(olen + 1, sizeof(uint8_t));
    if (output == NULL) {
        return NULL;
    }

    const unsigned char *end = (const unsigned char *)input + *len;
    const unsigned char *in = (const unsigned char *)input;
    uint8_t *pos = output;

    while (end - in >= 3) {
        *pos++ = base64_table[in[0] >> 2];
        *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
        *pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
        *pos++ = base64_table[in[2] & 0x3f];
        in += 3;
		
    }

    if (end - in) {
        *pos++ = base64_table[in[0] >> 2];
        if (end - in == 1) {
            *pos++ = base64_table[(in[0] & 0x03) << 4];
            *pos++ = '=';
        } else {
            *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
            *pos++ = base64_table[(in[1] & 0x0f) << 2];
        }
        *pos++ = '=';
    }

    *pos = '\0';

    return output;
}
