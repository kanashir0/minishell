/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:47:51 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/18 11:30:00 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_env_value(t_env *environ, char *key)
{
	t_env	*ev;

	ev = get_env(environ, key);
	if (!ev || !ev->value)
		return (NULL);
	return (ev->value);
}

void	append_and_free(char **res, char *tmp)
{
	char	*joined;

	joined = ft_strjoin(*res, tmp);
	if (*res)
		untrack_pointer(*res);
	if (tmp)
		untrack_pointer(tmp);
	*res = joined;
}

char	*extract_env_value(char *input, int *i, t_env *environ)
{
	char	key[256];
	char	*val;
	int		k;

	k = 0;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		key[k++] = input[(*i)++];
	key[k] = '\0';
	val = get_env_value(environ, key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*handle_dollar_special_cases(char c, int *i, int status)
{
	(*i)++;
	if (c == '?')
		return (ft_itoa(status));
	if (c == '$')
		return (ft_strdup("$"));
	if (c == '!')
		return (ft_strdup(""));
	return (NULL);
}

char	*handle_dollar(char *input, int *i, t_env *ev, int status)
{
	if (input[*i] != '$')
		return (ft_substr(input, (*i)++, 1));
	(*i)++;
	if (input[*i] == '?')
		return (handle_dollar_special_cases('?', i, status));
	else if (input[*i] == '$')
		return (handle_dollar_special_cases('$', i, status));
	else if (input[*i] == '!')
		return (handle_dollar_special_cases('!', i, status));
	else if (input[*i] == '\0')
		return (ft_strdup("$"));
	else if (ft_isalnum(input[*i]) || input[*i] == '_')
		return (extract_env_value(input, i, ev));
	else
		return (ft_strdup("$"));
}

void	split_token(t_token *curr, char **words)
{
	t_token	*new_token;
	t_token	*tmp;
	int		i;

	untrack_pointer(curr->value);
	curr->value = words[0];
	tmp = curr->next;
	i = 1;
	while (words[i])
	{
		new_token = ft_calloc(1, sizeof(t_token));
		new_token->type = WORD_TOKEN;
		new_token->value = words[i];
		curr->next = new_token;
		curr = new_token;
		i++;
	}
	curr->next = tmp;
}
