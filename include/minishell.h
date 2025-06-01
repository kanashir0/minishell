/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:27:43 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/01 17:47:25 by gyasuhir         ###   ########.fr       */
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

typedef struct s_command
{
	char	*input;
	char	*command;
	char	**args;
	int		signal;
}			t_command;

// Input data
void	read_input(t_command *cmd);
int		is_empty_input(char *input);

// Signals
void	setup_signals(void);
void	sigint_handler(int signum);

// Built-ins
int		echo(char **args);

// Executor
void	execute(t_command *cmd);

// Utils
t_command	*get_cmd_context(t_command *cmd);
t_command	*init_command(void);

// Tokenizer
void	tokenizer(t_command *cmd);

#endif
