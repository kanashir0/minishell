NAME = libft.a

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

CC = cc
FLAGS = -Wall -Werror -Wextra

SRCS =	ft_atol.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_itoa.c \
		ft_memmove.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c \
		ft_printf_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_substr.c \
		ft_collect_mem.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstnew.c \
		ft_free_matrix.c \


OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)

%.o: %.c
	@printf "$(GREEN)[Compiling]$(NC) %s...$(NC)\n" "$(notdir $(<))"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
