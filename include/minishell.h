/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:27:43 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/05/25 14:14:36 by gyasuhir         ###   ########.fr       */
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

// Memory management
void	*ft_malloc(size_t size);
void	free_command(t_command *cmd);

// Input data
void	read_input(t_command *cmd);

// Signals
void	setup_signals(t_command *cmd);

#endif
