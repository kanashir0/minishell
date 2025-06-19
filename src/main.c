/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:25:24 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/19 17:58:32 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	gambiarra(t_command *cmd)
{
	cmd->args = ft_split(cmd->input, ' ');
}

int	main(int ac, char **av, char **envp)
{
	t_command	*cmd;

	(void)ac;
	(void)av;
	cmd = init_command();
	init_env(cmd, envp);
	setup_signals();
	while (42)
	{
		read_input(cmd);
		if (!is_empty_input(cmd->input))
		{
			cmd->tokens = tokenizer(cmd->input);
			gambiarra(cmd);
			execute(cmd);
		}
	}
	ft_clear_mem();
	return (0);
}
