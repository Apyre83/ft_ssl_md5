
#include "ft_ssl.h"


args	g_args = {0};

void	handle_crypted(char	*message, char *from, FROMS from_type, uint32_t len) { /* from_type: FROM_STDIN, FROM_STRING, FROM_FILE */
	

	crypted_string	cs = {0};
	cs.string = message;

	char	*crypt_method = NULL;


	if (ft_strcmp(g_args.command, "md5") == 0) { cs.len = 16; md5((const uint8_t *)message, len, cs.hash); crypt_method = "MD5"; }
	else if (ft_strcmp(g_args.command, "sha256") == 0) { cs.len = 32; sha256((const uint8_t *)message, len, cs.hash); crypt_method = "SHA256";}
	else { whirlpool((uint8_t *)message, cs.hash, len); cs.len = 64; crypt_method = "Whirlpool"; }

	if (cs.string[ft_strlen(cs.string) - 1] == '\n') { cs.string[ft_strlen(cs.string) - 1] = '\0'; }

	/* Handle Flags */
	if (g_args.flag_q == 1) { if (g_args.flag_p == 1 && from_type == FROM_STDIN) { ft_printf("%s\n", message); } print_crypted(cs, 1); return ; } /* Quiet mode */
	if (g_args.flag_p == 1 && from_type == FROM_STDIN) { ft_printf("(\"%s\")= ", message); print_crypted(cs, 1); return ;} /* Echo stdin */
	if (g_args.flag_r == 1) { print_crypted(cs, 0); ft_printf(" %s\n", from); return ;}
	if (g_args.flag_s == 1 && from_type == FROM_STRING) { ft_printf("%s (\"%s\") = ", crypt_method, from); print_crypted(cs, 1); return ; }
	if (from_type == FROM_STDIN) { ft_printf("(stdin)= ");}
	else if (from_type == FROM_STRING) { ft_printf("%s (\"%s\") = ", crypt_method, from); }
	else { ft_printf("%s (%s) = ", crypt_method, from); }
	print_crypted(cs, 1);
}




int	main( int argc, char **argv) {
	
	if (parse(argc, argv) == 1)
		return (1);

	/* First if the -p flag is set, read from stdin and print it OR if there are no files / strings to read from */
	if (g_args.flag_p == 1 || (g_args.nb_files == 0 && g_args.nb_strings == 0 && g_args.flag_i == 0)) {

		uint32_t	linelen = 0;
		char		*result = read_from_stdin(&linelen);
		if (!result) return (1); 

		handle_crypted(result, "stdin", FROM_STDIN, linelen);
		if (result) free(result);
	}

	/* Now do all the s strings */
	for (int i = 0; i < g_args.nb_strings; i++) {
		handle_crypted(g_args.strings[i], g_args.strings[i], FROM_STRING, ft_strlen(g_args.strings[i]));
	}

	/* Now do all the files */
	for (int i = 0; i < g_args.nb_files; i++) {

		uint32_t	filelen = 0;
		char		*file = g_args.files[i];
		FILE		*f = fopen(file, "rb");
		if (!f) { ft_printf("ft_ssl: Error: could not open file '%s'.\n", file); continue; }
		char		*result = read_from_file(f, &filelen);
		if (!result) continue;

		handle_crypted(result, file, FROM_FILE, filelen);
		if (result) free(result);
	}

	if (g_args.flag_i) { /* Interactive mode, inputs are: <command> <message> */
		char	*line = NULL;

		while ((line = get_next_line(0)) != NULL) {

			int	i = 0;
			while (line[i] && line[i] != ' ') i++;
			if (line[i] == '\0') { ft_printf("ft_ssl: Error: no message.\n"); free(line); return (1); }
			line[i] = '\0';

			if (ft_strcmp(line, "md5") != 0 && ft_strcmp(line, "sha256") != 0 && ft_strcmp(line, "whirlpool") != 0) { /* Get command */
				ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", line);
				ft_printf("Commands:\nmd5\nsha256\nwhirlpool\n\n");
				free(line);
				return (1);
			}

			g_args.command = line;

			char	*message = line + i + 1;
			handle_crypted(message, message, FROM_STRING, ft_strlen(message));

			free(line);
		}

	}

	

	return (0);
}
