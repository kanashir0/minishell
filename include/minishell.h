/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:27:43 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/22 14:22:40 by cbrito-s         ###   ########.fr       */
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
	WORD,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	PIPE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

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

// env
t_env		**env_list_copy(t_env *env_list);
t_env		**env_list_ord(t_env **environ, int count);
void		addback_env(t_env **head, t_env *new_node);
t_env		*get_env(t_env *env_list, char *key);
t_env		*new_env(char *key, char *val);
void		ft_swap(t_env **a, t_env **b);
int			count_env(t_env *env_list);
int			count_env_arr(t_env **environ);

// Executor
void	execute(t_command *cmd);

// Utils
t_command	*get_cmd_context(t_command *cmd);
t_command	*init_command(void);
void		init_env(t_command *cmd, char **envp);
void		error_handler(char *msg);


// Tokenizer
t_token	**tokenizer(char *input);

#endif
