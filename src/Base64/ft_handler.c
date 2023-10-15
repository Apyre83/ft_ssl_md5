
#include "ft_ssl.h"

int handler_base64(void) {

    ft_printf("Handling base64 with the following arguments:\n");
    ft_printf("Flag d: %d\n", g_args.flag_d);
    ft_printf("Flag e: %d\n", g_args.flag_e);
    ft_printf("Flag i: %d\n", g_args.flag_i);
    if (g_args.flag_i) for (int i = 0; i < g_args.nb_files; i++) ft_printf("\tFile %d: %s\n", i, g_args.files[i]);
    ft_printf("Flag o: %d\n", g_args.flag_o);
    if (g_args.flag_o) ft_printf("\tFile: %s\n", g_args.file_o);
    return (0);
}