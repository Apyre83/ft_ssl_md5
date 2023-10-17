UP = "\033[A"
CLEAR = "\033[K"

MD = Message_Digest_Command
P = Parsing
B = Base64
DES = DES

MY_SOURCES =	src/ft_ssl.c						\
				src/ft_utils.c						\
													\
				src/$(P)/ft_parsing.c				\
				src/$(P)/ft_parsing_mdc.c			\
				src/$(P)/ft_parsing_base64.c		\
				src/$(P)/ft_parsing_des.c			\
													\
				src/$(MD)/ft_md5.c					\
				src/$(MD)/ft_sha256.c				\
				src/$(MD)/ft_whirlpool.c			\
				src/$(MD)/ft_handler.c				\
													\
				src/$(B)/ft_base64.c				\
				src/$(B)/ft_handler.c				\
													\
				src/$(DES)/ft_handler.c				\
				src/$(DES)/ft_des.c					\
													\
				get_next_line/get_next_line.c		\
				get_next_line/get_next_line_utils.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

INCLUDES = include/
FT_PRINTF_DIR = ft_printf
GET_NEXT_LINE_DIR = get_next_line

NAME = ft_ssl

FLAGS = -g -Wall -Wextra -Werror -I $(INCLUDES) -I $(FT_PRINTF_DIR)/includes -I $(GET_NEXT_LINE_DIR)

all: $(NAME)

.c.o:
	@gcc $(FLAGS) -c $< -o $(<:.c=.o)
	@echo $(UP)"\033[0;93mCompiling $(NAME) : $@ \033[0;39m                       "

$(NAME): $(MY_OBJECTS)
	@clear
	@make -C $(FT_PRINTF_DIR)
	@clear
	@echo "\033[0;92mLibftprintf.a compiled\033[0;39m"
	@gcc $(FLAGS) $(MY_OBJECTS) $(FT_PRINTF_DIR)/libftprintf.a -o $(NAME)
	@echo "\033[0;92m$(NAME) compiled\033[0;39m                                "

clean:
	@clear
	@rm -f $(MY_OBJECTS)
	@make -C $(FT_PRINTF_DIR) clean
	@echo "\033[0;92m$(NAME) .o files cleaned.\033[0;39m"

fclean: clean
	@clear
	@rm -f $(NAME) $(NAME_LINUX)
	@rm -f $(FT_PRINTF_DIR)/libftprintf.a
	@echo "\033[0;92m$(NAME) cleaned\033[0;39m"

re: fclean all

.PHONY: all clean fclean re
