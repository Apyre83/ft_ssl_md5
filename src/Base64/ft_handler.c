
#include "ft_ssl.h"

int handle_crypted_base64(char *message, uint32_t len, uint8_t *(*crypt_fun)(const char *, uint32_t*), int fd, const char *file) {
    uint8_t *result = crypt_fun(message, &len);
    if (!result) return (1);

    if (file) { write(fd, file, ft_strlen(file)); write(fd, ": ", 2); }
    write(fd, result, ft_strlen_u(result));
    write(fd, "\n\n", 2);

    if (result) free(result);
    return (0);
}



int handler_base64(void) {

#ifdef DEBUG
    ft_printf("Handling base64 with the following arguments:\n");
    ft_printf("Flag d: %d\n", g_args.flag_d);
    ft_printf("Flag e: %d\n", g_args.flag_e);
    ft_printf("Flag i: %d\n", g_args.flag_i);
    if (g_args.flag_i) for (int i = 0; i < g_args.nb_files; i++) ft_printf("\tFile %d: %s\n", i, g_args.files[i]);
    ft_printf("Flag o: %d\n", g_args.flag_o);
    if (g_args.flag_o) ft_printf("\tFile: %s\n", g_args.file_o);
#endif

    int fd = 0;
    if (g_args.flag_o) {
        fd = open(g_args.file_o, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) { ft_printf("ft_ssl: Error: could not open file '%s'.\n", g_args.file_o); return (1); }
    }

    uint8_t    *(*crypt_fun)(const char *, uint32_t *) = (g_args.flag_d == true) ? base64_decode : base64_encode;

    if (g_args.flag_i == false) { /* Read from stdin */
        uint32_t	linelen = 0;
        char		*result = read_from_stdin(&linelen);
        if (!result) return (1);

        handle_crypted_base64(result, linelen, crypt_fun, fd, NULL);
        if (result) free(result);
        if (fd) close(fd);
        return (0);
    }

    /* Now do all the files */
    for (int i = 0; i < g_args.nb_files; i++) {
        uint32_t	filelen = 0;
        char		*file = g_args.files[i];
        FILE		*f = fopen(file, "rb");
        if (!f) { ft_printf("ft_ssl: Error: could not open file '%s'.\n", file); continue; }
        char		*result = read_from_file(f, &filelen);
        if (!result) continue;

        handle_crypted_base64(result, filelen, crypt_fun, fd, file);
        if (result) free(result);
    }

    return (0);
}
