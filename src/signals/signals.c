/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:22:44 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/05/24 14:00:38 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*get_cmd_context(t_command *cmd)
{
	static t_command	*context;

	if (cmd)
		context = cmd;
	return (context);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	t_command	*cmd = get_cmd_context(NULL);

	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		cmd->signal = SIGINT;
	}
}

void	setup_signals(t_command *cmd)
{
	struct sigaction	sa;
	
	get_cmd_context(cmd);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, NULL);
}