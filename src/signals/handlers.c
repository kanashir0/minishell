/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:41:34 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/11 19:14:42 by gyasuhir         ###   ########.fr       */
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

	if (signum == SIGINT)
	{
		cmd = get_cmd_context(NULL);
		ft_putendl_fd("", STDOUT_FILENO);
		cmd->status = 130;
		rl_cleanup_after_signal();
		close(STDIN_FILENO);
	}
}
