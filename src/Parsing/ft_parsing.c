#include "ft_ssl.h"
#include "../../include/ft_parsing.h"

char *read_from_stdin(uint32_t *len) {
    char buffer[1024];
    char *result = NULL;
    *len = 0;
    
    while (1) {
        size_t bytesRead = fread(buffer, 1, sizeof(buffer), stdin);
        if (bytesRead == 0) break;

        char *new_result = realloc(result, *len + bytesRead);
        if (new_result == NULL) {
            ft_printf("ft_ssl: Error: could not allocate memory.\n");
            free(result);
            return NULL;
        }

        result = new_result;
        ft_memcpy(result + *len, buffer, bytesRead);
        *len += bytesRead;
    }

    if (result) {
        char *new_result = realloc(result, *len + 1);
        if (new_result == NULL) {
            ft_printf("ft_ssl: Error: could not allocate memory.\n");
            free(result);
            return NULL;
        }
        result = new_result;
        result[*len] = '\0';
    } else {
        result = ft_strdup("");
    }

    return result;
}

char *read_from_file(FILE *f, uint32_t *filelen) {
    char *result = NULL;
    if (!f) {
        ft_printf("ft_ssl: Error: could not open file.\n");
        return (NULL);
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    if (len <= 0) {
        *filelen = 0;
        fclose(f);
        return (ft_strdup(""));
    }
    rewind(f);

    *filelen = (uint32_t)len;
    result = ft_calloc(*filelen + 1, sizeof(char));
    if (!result) {
        ft_printf("ft_ssl: Error: could not allocate memory.\n");
        fclose(f);
        return (NULL);
    }

    size_t items_read = fread(result, *filelen, 1, f);
    if (items_read != 1) {
        ft_printf("ft_ssl: Error: could not read file.\n");
        free(result);
        fclose(f);
        return (NULL);
    }

    fclose(f);
    return (result);
}

int	parse(int argc, char **argv) {
	if (argc < 2) {
		ft_printf("usage: ft_ssl command [flags] [file/string]\n");
		return (1);
	}

    for (int i = 0; i < NB_COMMANDS; i++) {
        if (ft_strcmp(argv[1], g_commands[i].command) == 0) {
            g_args.command = argv[1];
            return (g_commands[i].parse(argc, argv));
        }
    }
    ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", argv[1]);
    ft_printf("Commands:\n\nMessage Digest commands:\nmd5\nsha256\nwhirlpool\n\nCipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\ndes-ofb\ndes3\ndes3-ecb\ndes3-cbc\ndes3-ofb\n");
    return (1);
}
