
#ifndef FT_SSL_H
#define FT_SSL_H


#include "ft_printf.h"
#include "get_next_line.h"
#include "ft_parsing.h"
#include "ft_handler.h"

#include <stddef.h> /* size_t */
#include <stdbool.h> /* bool */
#include <stdint.h> /* uint32_t */
#include <fcntl.h> /* open */
#include <stdio.h> /* File */
#include <stdlib.h> /* malloc, free */


typedef enum {
	FROM_STDIN,
	FROM_STRING,
	FROM_FILE
} FROMS;

typedef struct {
    const char *command;
    int (*parse)(int argc, char **argv);
    int (*handler)(void);
}   command_flags;


typedef struct s_crypted_string {
	char		*string;
	uint8_t		hash[1024];
	int			len;
}	crypted_string;


typedef struct s_args {
	char	*command;
	
    char	*strings[1024];
    int		nb_files;
    int		nb_strings;

    /* MD5 */
	bool	flag_q;
	bool	flag_r;
    /* END MD5 */

    /* DES */
    bool   flag_a;
    bool   flag_d;
    bool   flag_e;
    bool   flag_i;
    bool   flag_k;
    bool   flag_o;
    bool   flag_v;
    char    *file_o;
    /* END DES */

    /* MD5 AND DES */
    bool	flag_p; /* read from stdin for md5, password in ascii for des */
    bool	flag_s; /* string for md5, salt for des */
    char	*files[1024]; /* represent the input files */
    /* END MD5 AND DES */

}	args;



void	md5(const uint8_t *message, uint32_t len, uint8_t *digest);
void	sha256(const uint8_t *data, uint32_t len, uint8_t *hash);
void	whirlpool(uint8_t *message, uint8_t *array, uint32_t linelen);
uint64_t	des(uint64_t input, uint64_t key, char mode);


int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	print_crypted(crypted_string cs, bool nl);
char	*ft_strchr(const char *s, int c);
int     ft_isalnum(int c);
int     ft_strlen_u(uint8_t *s);

char	*read_from_stdin(uint32_t *len);
char	*read_from_file(FILE *f, uint32_t *filelen);
int		parse(int argc, char **argv);




#define NB_COMMANDS 12

extern command_flags	g_commands[NB_COMMANDS];

extern args             g_args;



#endif /* FT_SSL_H */
