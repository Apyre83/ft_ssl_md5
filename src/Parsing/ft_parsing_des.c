#include "ft_ssl.h"

/*
 * @brief: parse comamnds for des
 * @param: argc The number of arguments
 * @param: argv The arguments
 * @return: 0 if success, 1 if error
 * @note: The arguments for des are:
 * 		-a decode/encode the input in base64, depending on the encrypt mode
 * 		-d decrypt mode
 * 		-e encrypt mode (default)
 * 		-i input file (default stdin)
 * 		-k key in hex is the next argument
 * 		-o output file (default stdout)
 * 		-p password in ascii is the next argument
 * 		-s salt in hex is the next argument
 * 		-v initialization vector in hex is the next argument
 */
int parse_des(int argc, char **argv) {
	int	i = 1;
	g_args.flag_e = 1;
	
	while (++i < argc) {
		if (argv[i][0] != '-') { ft_printf("ft_ssl: Error: '%s', you must provide a file to indiquate a non-flag parameter.\n", argv[i]); return (1); }

		if (ft_strcmp(argv[i], "-a") == 0) { g_args.flag_a = 1; }
		else if (ft_strcmp(argv[i], "-d") == 0) { g_args.flag_d = 1; g_args.flag_e = 0; }
		else if (ft_strcmp(argv[i], "-e") == 0) { g_args.flag_e = 1; g_args.flag_d = 0; }
		else if (ft_strcmp(argv[i], "-i") == 0) {
			g_args.flag_i = 1;
			if (i + 1 >= argc) { ft_printf("ft_ssl: Error: -i flag requires an argument.\n"); return (1); }
			if (g_args.nb_files > 1023) { ft_printf("ft_ssl: Error: too many files.\n"); return (1); }
			g_args.files[g_args.nb_files] = argv[i + 1];
			g_args.nb_files++;
			i++;
		}
		else if (ft_strcmp(argv[i], "-k") == 0) {
			g_args.flag_k = 1;
			if (i + 1 >= argc) { ft_printf("ft_ssl: Error: -k flag requires an argument.\n"); return (1); }
			g_args.key = strtoull(argv[i + 1], NULL, 16);
			i++;
		}
		else if (ft_strcmp(argv[i], "-o") == 0) {
			g_args.flag_o = 1;
			if (i + 1 >= argc) { ft_printf("ft_ssl: Error: -o flag requires an argument.\n"); return (1); }
			g_args.file_o = argv[i + 1];
			i++;
		}
		else if (ft_strcmp(argv[i], "-p") == 0) {
			g_args.flag_p = 1;
			if (i + 1 >= argc) { ft_printf("ft_ssl: Error: -p flag requires an argument.\n"); return (1); }
			g_args.password = argv[i + 1];
			i++;
		}
		else if (ft_strcmp(argv[i], "-s") == 0) {
			g_args.flag_s = 1;
			if (i + 1 >= argc) { ft_printf("ft_ssl: Error: -s flag requires an argument.\n"); return (1); }
			g_args.salt = argv[i + 1];
			i++;
		}
		else if (ft_strcmp(argv[i], "-v") == 0) {
			g_args.flag_v = 1;
			if (i + 1 >= argc) { ft_printf("ft_ssl: Error: -v flag requires an argument.\n"); return (1); }
			g_args.iv = strtoull(argv[i + 1], NULL, 16);
			i++;
		}
		else { ft_printf("ft_ssl: Error: '%s', invalid option.\n", argv[i]); return (1); }
	}


    return (0);
}
