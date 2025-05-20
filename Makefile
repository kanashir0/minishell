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

SRC =	$(addprefix $(SRC_DIR), main.c) \
		$(addprefix $(BUI_DIR), ) \
		$(addprefix $(EXE_DIR), ) \
		$(addprefix $(EXP_DIR), ) \
		$(addprefix $(PAR_DIR), ) \
		$(addprefix $(RED_DIR), ) \
		$(addprefix $(SIG_DIR), ) \
		$(addprefix $(TOK_DIR), ) \
		$(addprefix $(UTL_DIR), )

OBJS = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))
OBJS_DIRS = $(sort $(dir $(OBJS)))

all: libft $(OBJS_DIRS) $(NAME)

$(OBJS_DIRS):
	@mkdir -p $@

$(OBJS_DIRS)%.o: $(SRC_DIR)%.c | $(OBJS_DIRS)
	@printf "$(GREEN)[Compiling]$(NC) %s...$(NC)\n" "$(notdir $(<))"
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -no-pie $(OBJS) -L$(LIB_DIR) -lft $(LDFLAGS) -o $(NAME)

libft:
	@make -C $(LIB_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) fclean

fclean: clean
	@printf "$(RED)[Cleaning]$(NC)\n" "$(notdir $(<))"
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
