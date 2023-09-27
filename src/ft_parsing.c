#include "ft_ssl.h"


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



