

#ifndef FT_SSL_H
# define FT_SSL_H



#include "ft_printf.h"
#include "get_next_line.h"

#include <stddef.h> /* size_t */
#include <stdbool.h> /* bool */
#include <stdint.h> /* uint32_t */
#include <fcntl.h> /* open */
#include <stdio.h> /* File */


typedef enum {
	FROM_STDIN,
	FROM_STRING,
	FROM_FILE
} FROMS;


typedef struct s_crypted_string {
	char		*string;
	uint8_t		hash[1024];
	int			len;
}	crypted_string;


typedef struct s_args {
	char		*command;
	
	char		*files[1024];

	bool		flag_p;
	bool		flag_q;
	bool		flag_r;
	bool		flag_s;
	char		*strings[1024];

	bool		flag_i; /* Bonus */

	int			nb_files;
	int			nb_strings;
}	args;



void	md5(const uint8_t *message, uint32_t len, uint8_t *digest);
void	sha256(const uint8_t *data, uint32_t len, uint8_t *hash);
void	whirlpool(uint8_t *message, uint8_t *array, uint32_t linelen);


int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	print_crypted(crypted_string cs, bool nl);


char	*read_from_stdin(uint32_t *len);
char	*read_from_file(FILE *f, uint32_t *filelen);
int		parse(int argc, char **argv);






extern args	g_args;



#endif /* FT_SSL_H */
