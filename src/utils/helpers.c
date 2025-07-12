/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:25:40 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/12 15:49:07 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*concatenate(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(s1, s2);
	full = ft_strjoin(tmp, s3);
	untrack_pointer(tmp);
	return (full);
}

void	syntax_error_unclosed_quote(char quote)
{
	ft_printf_fd(STDERR_FILENO, "syntax error: unclosed quote ");
	ft_putchar_fd(quote, STDERR_FILENO);
	ft_printf_fd(STDERR_FILENO, "\n");
	get_cmd_context(NULL)->status = 2;
}

int	waitpid_status(int pid[2])
{
	int			status;
	int			sig;
	t_command	*cmd;


	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	cmd = get_cmd_context(NULL);
	if (WIFEXITED(status))
		cmd->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT && __WCOREDUMP(status))
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		cmd->status = 128 + sig;
	}
	else
		cmd->status = 1;
	return (cmd->status);
}
