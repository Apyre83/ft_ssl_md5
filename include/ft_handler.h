#ifndef FT_SSL_MD5_FT_HANDLER_H
#define FT_SSL_MD5_FT_HANDLER_H

#include <stdint.h> /* uint32_t */

int handler_des(void);
int handler_base64(void);
int handler_mdc(void);

uint8_t    *base64_encode(const char *input, uint32_t *len);
uint8_t    *base64_decode(const char *input, uint32_t *len);

#endif /* FT_SSL_MD5_FT_HANDLER_H */
