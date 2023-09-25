
#include "ft_ssl.h"


args	g_args = {0};


int	parse(int argc, char **argv) {
	if (argc < 2) {
		ft_printf("usage: ft_ssl command [flags] [file/string]\n");
		return (1);
	}

	char	*command = argv[1];
	if (ft_strcmp(command, "md5") != 0 && ft_strcmp(command, "sha256") != 0) { /* Get command */
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", command);
		ft_printf("Commands:\nmd5\nsha256\n\n");
		ft_printf("Flags:\n-p -q -r -s\n");
		return (1);
	}
	g_args.command = command;

	int	i = 2;
	while (i < argc) { /* Get flags */
		if (argv[i][0] != '-') break;

		if (ft_strcmp(argv[i], "-p") == 0) g_args.flag_p = 1;
		else if (ft_strcmp(argv[i], "-q") == 0) g_args.flag_q = 1;
		else if (ft_strcmp(argv[i], "-r") == 0) g_args.flag_r = 1;
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
	for (size_t i = 0; i < cs.len; i++) {
		ft_printf("%02x", cs.hash[i]);
	}
	if (nl == true) ft_printf("\n");
}


void	handle_crypted(char	*message, char *from, FROMS from_type) { /* from_type: FROM_STDIN, FROM_STRING, FROM_FILE */
	crypted_string	cs = {0};
	cs.string = message;

	char	*crypt_method = NULL;


	if (ft_strcmp(g_args.command, "md5") == 0) { cs.len = 16; md5((const uint8_t *)message, ft_strlen(message), cs.hash); crypt_method = "MD5"; }
	else { cs.len = 32; sha256((const uint8_t *)message, ft_strlen(message), cs.hash); crypt_method = "SHA256";}

	if (cs.string[ft_strlen(cs.string) - 1] == '\n') { cs.string[ft_strlen(cs.string) - 1] = '\0'; }

	/* Handle Flags */
	if (g_args.flag_q == 1) { print_crypted(cs, 1); return ; } /* Quiet mode */
	if (g_args.flag_p == 1 && from_type == FROM_STDIN) { ft_printf("(\"%s\")= ", message); print_crypted(cs, 1); return ;} /* Echo stdin */
	if (g_args.flag_r == 1) { print_crypted(cs, 0); ft_printf(" %s\n", from); return ;}
	if (g_args.flag_s == 1 && from_type == FROM_STRING) {
		if (ft_strcmp(g_args.command, "md5") == 0) { ft_printf("MD5 (\"%s\") = ", from); }
		else { ft_printf("SHA256 (\"%s\") = ", from); }
		print_crypted(cs, 1);
		return ;
	}
	if (from_type == FROM_STDIN) { ft_printf("(stdin)= ");}
	else if (from_type == FROM_STRING) { ft_printf("%s (\"%s\") = ", crypt_method, from); }
	else { ft_printf("%s (%s) = ", crypt_method, from); }
	print_crypted(cs, 1);
}


int	main( int argc, char **argv) {
	
	if (parse(argc, argv) == 1)
		return (1);

	/* Print everything */
	/*ft_printf("command: %s\n", argv[1]);
	ft_printf("flag_p: %d\n", g_args.flag_p);
	ft_printf("flag_q: %d\n", g_args.flag_q);
	ft_printf("flag_r: %d\n", g_args.flag_r);
	ft_printf("flag_s: %d\n", g_args.flag_s);
	ft_printf("nb_strings: %d\n", g_args.nb_strings);
	ft_printf("nb_files: %d\n", g_args.nb_files);

	if (g_args.nb_strings > 0) {
		ft_printf("strings:\n");
		for (int i = 0; i < g_args.nb_strings; i++)
			ft_printf("\t%s\n", g_args.strings[i]);
	}

	if (g_args.nb_files > 0) {
		ft_printf("\nfiles:\n");
		for (int i = 0; i < g_args.nb_files; i++)
			ft_printf("\t%s\n", g_args.files[i]);
	}*/



	/* Do the stuff */
	/*
	 * First if the -p flag is set, read from stdin and print it OR if there are no files / strings to read from
	 */
	if (g_args.flag_p == 1 || (g_args.nb_files == 0 && g_args.nb_strings == 0)) {
		char	*line = NULL;
		char	*result = NULL;
		char	*tmp = NULL;

		while ((line = get_next_line(0)) != NULL) {
			if (result == NULL) { result = ft_strdup(line); free(line); continue ; }
			else { tmp = ft_strjoin(result, line); free(result); result = tmp; free(line); }
		}

		free(line);

		handle_crypted(result, "stdin", FROM_STDIN);
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

		free(line);

		handle_crypted(result, file, FROM_FILE);
	}

	

	return (0);
}
