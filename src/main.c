/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:25:24 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/01 17:10:33 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenizer(t_command *cmd)
{
	cmd->args = ft_split(cmd->input, ' ');
	return ;
}

int	main(void)
{
	t_command	*cmd;

	cmd = init_command();
	setup_signals();
	while (42)
	{
		read_input(cmd);
		if (!cmd->input)
			break ;
		tokenizer(cmd);
		execute(cmd);
	}
	ft_clear_men();
	return (0);
}
