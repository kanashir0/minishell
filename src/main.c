/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:25:24 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/05/29 18:56:36 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenizer(t_command *cmd)
{
	cmd->args = ft_split(cmd->input, ' ');
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_command	*cmd;

	(void)ac;
	(void)av;
	cmd = ft_collect_mem(1, sizeof(t_command));
	init_env(cmd, envp);
	setup_signals(cmd);
	while (42)
	{
		read_input(cmd);
		if (!cmd->input)
			break ;
		tokenizer(cmd);
		execute(cmd);
	}
	ft_clear_mem();
	return (0);
}
