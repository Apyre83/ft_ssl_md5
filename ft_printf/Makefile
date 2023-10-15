UP = "\033[A"
CLEAR = "\033[K"



MY_SOURCES = 	srcs/main.c								\
				srcs/ft_utils.c srcs/ft_utils_2.c		\
				srcs/ft_options.c srcs/ft_options_2.c	\
				srcs/ft_int.c srcs/ft_int_2.c			\
				srcs/ft_char.c							\
				srcs/ft_str.c							\
				srcs/ft_ptr.c							\
				srcs/ft_hex_low.c srcs/ft_hex_low_2.c	\
				srcs/ft_hex_upp.c srcs/ft_hex_upp_2.c	\
				srcs/ft_unsigned.c						\
				srcs/ft_percent.c

SOURCES_LIBFT = libft/ft_putchar_fd.c	\
				libft/ft_putstr_fd.c	\
				libft/ft_putnbr_fd.c	\
				libft/ft_isdigit.c		\
				libft/ft_strlen.c		\
				libft/ft_atoi.c			\
				libft/ft_itoa.c			\
				libft/ft_calloc.c		\
				libft/ft_bzero.c		\
				libft/ft_memset.c		\
				libft/ft_strdup.c		\
				libft/ft_strjoin.c		\
				libft/ft_strlcpy.c

MY_OBJECTS =  $(MY_SOURCES:.c=.o)

OBJECTS_LIBFT = $(SOURCES_LIBFT:.c=.o)

INCLUDES = includes/

FLAGS = -Wall -Wextra -Werror -I $(INCLUDES)

NAME = libftprintf.a 


all: $(NAME)

.c.o:
	@gcc $(FLAGS) -c $< -o $(<:.c=.o)
	@echo $(UP)"\033[0;93mCompiling $(NAME) : $@ \033[0;39m                       "

$(NAME): $(MY_OBJECTS) $(OBJECTS_LIBFT)
	@ar rcs $(NAME) $(MY_OBJECTS) $(OBJECTS_LIBFT)
	@echo "\033[0;92m$(NAME) compiled\033[0;39m                                "

clean:
	@rm -f $(MY_OBJECTS) $(OBJECTS_LIBFT)
	@echo "\033[0;92m$(NAME) .o files cleaned.\033[0;39m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;92m$(NAME) cleaned\033[0;39m"

bonus: $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
