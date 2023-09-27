
#include "ft_ssl.h"


#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
#define F(b, c, d) (((b) & (c)) | (~(b) & (d)))
#define G(b, c, d) (((b) & (d)) | ((c) & ~(d)))
#define H(b, c, d) ((b) ^ (c) ^ (d))
#define I(b, c, d) ((c) ^ ((b) | ~(d)))


static const uint32_t	rotations[] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

static const uint32_t	constants_K[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};


void padding(const uint8_t *message, uint32_t original_byte_len, uint8_t **padded_message, uint32_t *padded_message_len) {
    uint64_t original_bit_len = (uint64_t)original_byte_len * 8;

    *padded_message_len = original_byte_len + 1;
    while (*padded_message_len % 64 != 56) {
        (*padded_message_len)++;
    }
    *padded_message_len += 8;

    *padded_message = (uint8_t *)malloc(*padded_message_len);
    if (*padded_message == NULL) {
        exit(1);
    }

    ft_memcpy(*padded_message, message, original_byte_len);
    (*padded_message)[original_byte_len] = 0x80;
    for (uint32_t i = original_byte_len + 1; i < *padded_message_len - 8; i++) {
        (*padded_message)[i] = 0x00;
    }
    for (int i = 0; i < 8; i++) {
        (*padded_message)[*padded_message_len - 8 + i] = (uint8_t)(original_bit_len >> (8 * i));
    }
}



void md5(const uint8_t *message, uint32_t len, uint8_t *digest) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;

    uint8_t *padded_message;
    uint32_t padded_message_len;
    padding(message, len, &padded_message, &padded_message_len);

    for (uint32_t i = 0; i < padded_message_len / 64; i++) {
        uint32_t w[16];
        ft_memcpy(w, padded_message + i * 64, 64);

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t f, g;

        for (uint32_t j = 0; j < 64; j++) {
            if (j <= 15) {
                f = F(b, c, d);
                g = j;
            } else if (j <= 31) {
                f = G(b, c, d);
                g = (5 * j + 1) % 16;
            } else if (j <= 47) {
                f = H(b, c, d);
                g = (3 * j + 5) % 16;
            } else {
                f = I(b, c, d);
                g = (7 * j) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + constants_K[j] + w[g]), rotations[j]);
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }

    free(padded_message);

    for (int i = 0; i < 4; i++) {
        digest[i] = (uint8_t)(h0 >> (8 * i));
        digest[i + 4] = (uint8_t)(h1 >> (8 * i));
        digest[i + 8] = (uint8_t)(h2 >> (8 * i));
        digest[i + 12] = (uint8_t)(h3 >> (8 * i));
    }
}

