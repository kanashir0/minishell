/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:27:43 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/29 17:45:00 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1
# define SYNTAX_ERROR 2

typedef enum e_token_type
{
	WORD_TOKEN,
	REDIR_IN_TOKEN,
	REDIR_OUT_TOKEN,
	HEREDOC_TOKEN,
	APPEND_TOKEN,
	PIPE_TOKEN
}	t_token_type;

typedef enum e_node_type
{
	REDIR_NODE,
	PIPE_NODE,
	WORD_NODE
}	t_node_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_node
{
	t_node_type		type;
	struct s_node	*left;
	struct s_node	*right;
	char			**argv;
	char			*redir_file;
	t_token_type	redir_type;
}					t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_command
{
	char	*input;
	char	*command;
	char	**args;
	int		signal;
	int		status;
	t_env	*env_list;
	t_token	**tokens;
}			t_command;

// Input data
void	read_input(t_command *cmd);
int		is_empty_input(char *input);
int		ft_isspace(int c);

// Signals
void	setup_signals(void);
void	sigint_handler(int signum);

// Built-ins
int		echo(char **args);
int		pwd(t_command *cmd);
int		cd(char **args, t_command *cmd);
int		export(char **args, t_command *cmd);
int		unset(char **args, t_command *cmd);
int		env(char **args, t_command *cmd);
int		builtin_exit(char **args, t_command *cmd);

// Executor
void	execute(t_command *cmd);
int 	open_redir_file(t_token_type type, const char *filename);
int		execute_node(t_node *node, int input_fd, int output_fd);
int		execute_ast(t_node *root);

// Utils
t_command	*get_cmd_context(t_command *cmd);
t_command	*init_command(void);
void		init_env(t_command *cmd, char **envp);
void		addback_env(t_env **head, t_env *new_node);
t_env		*get_env(t_env *env_list, char *key);
void		error_handler(char *msg);

// Tokenizer
t_token	**tokenizer(char *input);
int		match_token(t_token **tokens, t_token_type t_type);
t_token	*consume_token(t_token **tokens);

// Parser
t_node	*generate_ast(t_token **tokens);
t_node	*new_node(t_node_type n_type, t_node *left, t_node *right);
void	print_ast(t_node *ast, int indent);

#endif
