/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:43:49 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/17 18:45:46 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	db_quoted_heredoc(const char *delim, int *i, char **res)
{
	char	*tmp;

	(*i)++;
	while (delim[*i] && delim[*i] != '"')
	{
		tmp = ft_substr(delim, *i, 1);
		append_and_free(res, tmp);
		(*i)++;
	}
	if (delim[*i] == '\"')
		(*i)++;
}

char	*strip_quotes(char *delim)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (delim[i])
	{
		if (delim[i] == '\'')
			single_quoted(delim, &i, &res);
		else if (delim[i] == '"')
			db_quoted_heredoc(delim, &i, &res);
		else
		{
			tmp = ft_substr(delim, i, 1);
			append_and_free(&res, tmp);
		}
		i++;
	}
	return (res);
}

int	should_expand(char *delim)
{
	if (ft_strchr(delim, '\'') || ft_strchr(delim, '"'))
		return (0);
	return (1);
}

void	unquoted_heredoc(char **line)
{
	int			i;
	char		*new_line;
	char		*tmp;
	t_command	*cmd;

	i = 0;
	cmd = get_cmd_context(NULL);
	new_line = ft_strdup("");
	while (line[0][i])
	{
		if (line[0][i] != '$')
			append_and_free(&new_line, ft_substr(*line, i++, 1));
		else
		{
			tmp = handle_dollar(*line, &i, cmd->env_list, cmd->status);
			append_and_free(&new_line, tmp);
		}
	}
	*line = new_line;
}
