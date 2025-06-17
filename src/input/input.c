/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:05:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/17 17:52:16 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_input(t_command *cmd)
{
	cmd->input = readline("minishell> ");
	// TODO validação input
	if (!cmd->input)
	{
		ft_putstr_fd("exit\n", 1);
		ft_clear_mem();
		exit(EXIT_FAILURE);
	}
	if (cmd->input)
		add_history(cmd->input);
	return ;
}

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_empty_input(char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (0);
		input++;
	}
	return (1);
}
