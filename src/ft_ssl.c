
#include "ft_ssl.h"


args	g_args = {0};


int	parse(int argc, char **argv) {
	if (argc < 2) {
		ft_printf("usage: ft_ssl command [flags] [file/string]\n");
		return (1);
	}

	char	*command = argv[1];
	if (ft_strcmp(command, "md5") != 0 && ft_strcmp(command, "sha256") != 0 && ft_strcmp(command, "whirlpool") != 0) { /* Get command */
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", command);
		ft_printf("Commands:\nmd5\nsha256\nwhirlpool\n\n");
		ft_printf("Flags:\n-p -q -r -s -i\n");
		return (1);
	}
	g_args.command = command;

	int	i = 2;
	while (i < argc) { /* Get flags */
		if (argv[i][0] != '-') break;

		if (ft_strcmp(argv[i], "-p") == 0) g_args.flag_p = 1;
		else if (ft_strcmp(argv[i], "-q") == 0) g_args.flag_q = 1;
		else if (ft_strcmp(argv[i], "-r") == 0) g_args.flag_r = 1;
		else if (ft_strcmp(argv[i], "-i") == 0) g_args.flag_i = 1;
		else if (ft_strcmp(argv[i], "-s") == 0) {
			g_args.flag_s = 1;
			if (i + 1 < argc) {
				g_args.nb_strings++;
				if (g_args.nb_strings > 1023) { ft_printf("ft_ssl: Error: too many strings.\n"); return (1); }
				g_args.strings[g_args.nb_strings - 1] = argv[i + 1];
				i++;
			}
			else {
				ft_printf("ft_ssl: Error: -s flag requires an argument.\n");
				return (1);
			}
		}
		else {
			ft_printf("ft_ssl: Error: '%s' is an invalid flag.\n\n", argv[i]);
			ft_printf("Flags:\n-p -q -r -s\n");
			return (1);
		}
		i++;
	}

	int	nb_files = argc - i;
	if (nb_files > 1023) { ft_printf("ft_ssl: Error: too many files.\n"); return (1); }
	while (i < argc) { /* Get files */
		g_args.files[g_args.nb_files] = argv[i];
		g_args.nb_files++;
		i++;
	}
	return (0);
}


void	print_crypted(crypted_string cs, bool nl) {
	for (int i = 0; i < cs.len; i++) {
		ft_printf("%02x", cs.hash[i]);
	}
	if (nl == true) ft_printf("\n");
}

int	ft_toupper(int c)
{
	if (c <= 'z' && c >= 'a')
		return (c - 32);
	return (c);
}
char	*ft_str_to_upper(char *str) {
	for (int i = 0; str[i]; i++) {
		str[i] = ft_toupper(str[i]);
	}
	return (str);
}


void	handle_crypted(char	*message, char *from, FROMS from_type) { /* from_type: FROM_STDIN, FROM_STRING, FROM_FILE */
	

	crypted_string	cs = {0};
	cs.string = message;

	char	*crypt_method = NULL;


	if (ft_strcmp(g_args.command, "md5") == 0) { cs.len = 16; md5((const uint8_t *)message, ft_strlen(message), cs.hash); crypt_method = "MD5"; }
	else if (ft_strcmp(g_args.command, "sha256") == 0) { cs.len = 32; sha256((const uint8_t *)message, ft_strlen(message), cs.hash); crypt_method = "SHA256";}
	else { whirlpool((uint8_t *)message, cs.hash); cs.len = 64; crypt_method = "Whirlpool"; }

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
		char	*line = NULL;
		char	*result = NULL;
		char	*tmp = NULL;

		while ((line = get_next_line(0)) != NULL) {
			if (result == NULL) { result = ft_strdup(line); free(line); continue ; }
			else { tmp = ft_strjoin(result, line); free(result); result = tmp; free(line); }
		}

		if (line) free(line);
		handle_crypted(result, "stdin", FROM_STDIN);
		if (result) free(result);
	}

	/* Now do all the s strings */
	for (int i = 0; i < g_args.nb_strings; i++) {
		handle_crypted(g_args.strings[i], g_args.strings[i], FROM_STRING);
	}

	/* Now do all the files */
	for (int i = 0; i < g_args.nb_files; i++) {
		char	*file = g_args.files[i];
		int		fd = open(file, O_RDONLY);
		if (fd == -1) {
			ft_printf("ft_ssl: %s: %s: No such file or directory\n", g_args.command, file);
			continue ;
		}

		char	*line = NULL;
		char	*result = NULL;
		char	*tmp = NULL;

		while ((line = get_next_line(fd)) != NULL) {
			if (result == NULL) { result = ft_strdup(line); free(line); continue ; }
			else { tmp = ft_strjoin(result, line); free(result); result = tmp; free(line); }
		}

		if (line) free(line);
		handle_crypted(result, file, FROM_FILE);
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
			handle_crypted(message, message, FROM_STRING);

			free(line);
		}

	}

	

	return (0);
}
