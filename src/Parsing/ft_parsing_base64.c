#include "ft_ssl.h"

/*
 * @brief Parses the base64 command.
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return 0 if no error, 1 otherwise.
 * @note The arguments for base64 are:
 *   -e (default) = encode
 *   -d = decode
 *   -i = input file
 *   -o = output file
 */
int parse_base64(int argc, char **argv) {
    int	i = 1;
    g_args.flag_e = 1;

    while (++i < argc) {
        if (argv[i][0] != '-') { ft_printf("ft_ssl: Error: '%s', you must provide the -i flag before the input file.\n", argv[i]); return (1); }

        if (ft_strcmp(argv[i], "-d") == 0) { g_args.flag_d = 1; g_args.flag_e = 0; }
        else if (ft_strcmp(argv[i], "-e") == 0) { g_args.flag_e = 1; g_args.flag_d = 0; }
        else if (ft_strcmp(argv[i], "-i") == 0) {
            g_args.flag_i = 1;
            if (i + 1 >= argc) { ft_printf("ft_ssl: Error: -i flag requires an argument.\n"); return (1); }
            if (g_args.nb_files > 1023) { ft_printf("ft_ssl: Error: too many files.\n"); return (1); }
            g_args.files[g_args.nb_files] = argv[i + 1];
            g_args.nb_files++;
            i++;
        }
        else if (ft_strcmp(argv[i], "-o") == 0) {
            g_args.flag_o = 1;
            if (i + 1 >= argc) { ft_printf("ft_ssl: Error: -o flag requires an argument.\n"); return (1); }
            g_args.file_o = argv[i + 1];
            i++;
        }
        else {
            ft_printf("ft_ssl: Error: '%s' is an invalid flag.\n\n", argv[i]);
            ft_printf("Flags:\n-d -e -i -o\n");
            return (1);
        }
    }
    return (0);
}