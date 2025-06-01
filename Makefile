NAME = minishell

RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -lreadline -lncurses


LIB_DIR = lib/libft/
INC_DIR = -I include/ -I $(LIB_DIR)
OBJ_DIR = objs/
SRC_DIR = src/
BUI_DIR = src/builtins/
EXE_DIR = src/executor/
EXP_DIR = src/expansion/
PAR_DIR = src/parser/
RED_DIR = src/redirect/
SIG_DIR = src/signals/
TOK_DIR = src/tokenizer/
UTL_DIR = src/utils/
INP_DIR = src/input/

SRC =	$(addprefix $(SRC_DIR), main.c) \
		$(addprefix $(BUI_DIR), echo.c pwd.c cd.c export.c unset.c env.c exit.c) \
		$(addprefix $(EXE_DIR), execute.c) \
		$(addprefix $(EXP_DIR), ) \
		$(addprefix $(PAR_DIR), ) \
		$(addprefix $(RED_DIR), ) \
		$(addprefix $(SIG_DIR), setup.c handlers.c) \
		$(addprefix $(TOK_DIR), tokenizer.c) \
		$(addprefix $(UTL_DIR), init.c error.c environ.c) \
		$(addprefix $(INP_DIR), input.c)

OBJS = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: libft $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "$(GREEN)[Compiling]$(NC) %s...$(NC)\n" "$(notdir $(<))"
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -no-pie $(OBJS) -L$(LIB_DIR) -lft $(LDFLAGS) -o $(NAME)

libft:
	@make -C $(LIB_DIR) --no-print-directory

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) fclean --no-print-directory

fclean: clean
	@printf "$(RED)[Cleaning]$(NC)\n" "$(notdir $(<))"
	@make -C $(LIB_DIR) fclean --no-print-directory
	@rm -f $(NAME)

re: fclean all

valg:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --trace-children=yes --track-origins=yes --track-fds=yes ./$(NAME)

.PHONY: all clean fclean valg re
