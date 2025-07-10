/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:25:40 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/10 17:23:36 by cbrito-s         ###   ########.fr       */
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
	ft_putstr_fd("syntax error: unclosed quote ", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("\n", 2);
	get_cmd_context(NULL)->status = 2;
}

int	waitpid_status(int pid[2])
{
	int	status[2];

	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);

	if (WIFSIGNALED(status[0]))
		return (128 + WTERMSIG(status[0]));
	if (WIFSIGNALED(status[1]))
		return (128 + WTERMSIG(status[1]));
	if (WIFEXITED(status[1]))
		return (WEXITSTATUS(status[1]));
	return (1);
}
