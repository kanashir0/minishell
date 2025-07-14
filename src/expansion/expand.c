/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:46:31 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/13 18:10:33 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	single_quoted(char *input, int *i, char **res)
{
	char	*tmp;
	int		start;

	(*i)++;
	start = *i;
	while (input[*i] && input [*i] != '\'')
		(*i)++;
	tmp = ft_substr(input, start, *i - start);
	append_and_free(res, tmp);
	if (input[*i] == '\'')
		(*i)++;
}

static void	double_quoted(char *input, int *i, char **res, t_env *ev, int status)
{
	char	*tmp;

	(*i)++;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			tmp = handle_dollar(input, i, ev, status);
			append_and_free(res, tmp);
		}
		else
		{
			tmp = ft_substr(input, *i, 1);
			append_and_free(res, tmp);
			(*i)++;
		}
	}
	if (input[*i] == '\"')
		(*i)++;
}

static void	unquoted(char *input, int *i, char **res, t_env *ev, int status)
{
	char	*tmp;

	tmp = handle_dollar(input, i, ev, status);
	append_and_free(res, tmp);
}

static char	*expand_string(char *input, t_env *environ, int status)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '\'')
			single_quoted(input, &i, &res);
		else if (input[i] == '"')
			double_quoted(input, &i, &res, environ, status);
		else
			unquoted(input, &i, &res, environ, status);
	}
	return (res);
}

void	expand_tokens(t_token **tokens, t_env *env, int status)
{
	t_token	*curr;
	t_token	*prev;
	char	*expanded;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		if (curr->type == WORD_TOKEN && curr->value)
		{
			expanded = expand_string(curr->value, env, status);
			untrack_pointer(curr->value);
			curr->value = expanded;
			if (curr->value[0] == '\0')
			{
				remove_empty_token(tokens, curr, prev);
				continue ;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}
