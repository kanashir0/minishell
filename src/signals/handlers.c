/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:41:34 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/15 21:21:29 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signum)
{
	t_command	*cmd;

	cmd = get_cmd_context(NULL);
	if (signum == SIGINT)
	{
		if (cmd->executing == 0)
		{
			ft_putendl_fd("", STDOUT_FILENO);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			ft_putendl_fd("", STDOUT_FILENO);
		cmd->status = 128 + SIGINT;
	}
}

void	heredoc_sigint_handler(int signum)
{
	t_command	*cmd;

	(void)signum;
	cmd = get_cmd_context(NULL);
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	cmd->status = 130;
	close(STDIN_FILENO);
}
