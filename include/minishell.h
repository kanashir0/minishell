/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:27:43 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/11 19:00:10 by cbrito-s         ###   ########.fr       */
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
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1
# define SYNTAX_ERROR 2

# define MINISHELL "\001\033[01;38;5;33m\002"
# define COMMAND "\001\033[0m\002"

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
	int		status;
	int		executing;
	t_env	*env_list;
	t_token	**tokens;
}			t_command;

// Input
void		read_input(t_command *cmd);
int			is_empty_input(char *input);
int			ft_isspace(int c);
int			check_input(char *input, int *len);

// Signals
void		setup_signals(void);
void		sigint_handler(int signum);
void		process_signals(int pid);

// Built-ins
int			echo(char **args);
int			pwd(t_command *cmd);
int			cd(char **args, t_command *cmd);
int			export(char **args, t_command *cmd);
int			unset(char **args, t_command *cmd);
int			env(char **args, t_command *cmd);
int			builtin_exit(char **args, t_command *cmd);
int			is_builtin(char **args, t_command *cmd);

// env
t_env		**env_list_copy(t_env *env_list);
t_env		**env_list_ord(t_env **environ, int count);
void		addback_env(t_env **head, t_env *new_node);
t_env		*get_env(t_env *env_list, char *key);
t_env		*new_env(char *key, char *val);
void		ft_swap(t_env **a, t_env **b);
int			count_env(t_env *env_list);
int			count_env_arr(t_env **environ);
char		**environ_list(t_env *env_list, int count);

// Executor
int			open_redir_file(t_token_type type, const char *filename);
int			execute_node(t_node *node, int input_fd, int output_fd);
int			execute_ast(t_node *root);
int			exec_path(char **args, int input_fd, int output_fd, t_command *cmd);
void		close_fd(int input_fd, int output_fd);
void	pipe_child_left(t_node *node, int fd[2], int in, int out);
void	pipe_child_right(t_node *node, int fd[2], int in, int out);

// Expansion
void		expand(t_node *node);
void		append_and_free(char **res, char *tmp);
char		*extract_env_value(char *input, int *i, t_env *environ);
char		*handle_dollar_special_cases(char c, int *i, int status);
char		*handle_dollar(char *input, int *i, t_env *ev, int status);

// Utils
t_command	*get_cmd_context(t_command *cmd);
t_command	*init_command(void);
void		init_env(t_command *cmd, char **envp);
void		init_under(t_command *cmd, char *prog);
void		error_handler(char *msg);
int			print_cmd_error(char *command, int res);
void 		update_under(t_command *cmd, char *new_value);

// Tokenizer
t_token		**tokenizer(char *input);
int			match_token(t_token **tokens, t_token_type t_type);
t_token		*consume_token(t_token **tokens);
void		free_token_list(t_token **tokens);

// Parser
t_node		*generate_ast(t_token **tokens);
t_node		*new_node(t_node_type n_type, t_node *left, t_node *right);

// Helpers
char		*concatenate(char *s1, char *s2, char *s3);
void		syntax_error_unclosed_quote(char quote);
int			waitpid_status(int pid[2]);

#endif
