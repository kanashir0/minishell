/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:27:43 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/05/25 15:59:22 by cbrito-s         ###   ########.fr       */
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

// Signals
void	setup_signals(t_command *cmd);

// Built-ins
int		echo(char **args);

// Executor
void	execute(t_command *cmd);

#endif
