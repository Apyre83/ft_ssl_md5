
#include "ft_ssl.h"



int parse_mdc(int argc, char **argv) {
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