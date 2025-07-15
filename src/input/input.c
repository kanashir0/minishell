/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:05:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/12 15:46:45 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_input(t_command *cmd)
{
	// TODO: fazer o free do input
	cmd->input = readline(MINISHELL "minishell$ " COMMAND);
	// TODO validação input
	if (!cmd->input)
	{
		ft_printf_fd(STDOUT_FILENO, "exit\n");
		ft_clear_mem();
		exit(131);
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

int	check_input(char *input, int *len)
{
	char	quote;
	int		start;

	quote = input[*len];
	start = *len;
	(*len)++;
	while (input[*len] && input[*len] != quote)
		(*len)++;
	if (input[*len] == quote)
	{
		(*len)++;
		return (*len - start);
	}
	syntax_error_unclosed_quote(quote);
	return (-1);
}
