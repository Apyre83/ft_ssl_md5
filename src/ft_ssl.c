
#include "ft_ssl.h"


command_flags	g_commands[NB_COMMANDS] = {
    {"md5", parse_mdc, handler_mdc},
    {"sha256", parse_mdc, handler_mdc},
    {"whirlpool", parse_mdc, handler_mdc},
    {"base64", parse_base64, handler_base64},
    {"des", parse_des, handler_des},
    {"des-ecb", parse_des, handler_des},
    {"des-cbc", parse_des, handler_des},
    {"des-ofb", parse_des, handler_des},
    {"des3", parse_des, handler_des},
    {"des3-ecb", parse_des, handler_des},
    {"des3-cbc", parse_des, handler_des},
    {"des3-ofb", parse_des, handler_des}
};

args	g_args = {0};

int	main( int argc, char **argv) {
	
	if (parse(argc, argv) == 1) return (1);
    for (int i = 0; i < NB_COMMANDS; i++) { if (ft_strcmp(g_args.command, g_commands[i].command) == 0)  { return (g_commands[i].handler()); } }
    return (ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", g_args.command));
}
