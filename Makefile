UP = "\033[A"
CLEAR = "\033[K"

MY_SOURCES =	src/ft_ssl.c						\
				src/ft_utils.c						\
				src/md5.c							\
				src/sha256.c						\
				get_next_line/get_next_line.c		\
				get_next_line/get_next_line_utils.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

INCLUDES = include/
FT_PRINTF_DIR = ft_printf
GET_NEXT_LINE_DIR = get_next_line

NAME = ft_ssl

FLAGS = -Wall -Wextra -Werror -I $(INCLUDES) -I $(FT_PRINTF_DIR)/includes -I $(GET_NEXT_LINE_DIR)

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
