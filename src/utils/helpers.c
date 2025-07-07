/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:25:40 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/07 19:10:38 by cbrito-s         ###   ########.fr       */
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

int	handle_escape(char *input, int len)
{
	if (input[len] == '\\')
	{
		if (input[len + 1])
			return (2);
		return (1);
	}
	return (0);
}

int	handle_quote(char *input, int len)
{
	char	quote;
	int		start;

	quote = input[len++];
	start = len;
	while (input[len] && input[len] != quote)
	{
		if (quote == '\"' && input[len] == '\\' && input[len + 1])
			len += 2;
		else
			len++;
	}
	if (input[len] == quote)
		return (len - start + 2);
	return (-1);
}

void	syntax_error_unclosed_quote(void)
{
	ft_putstr_fd("syntax error: unclosed quote\n", 2);
	get_cmd_context(NULL)->status = 2;
}
