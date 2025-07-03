/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:47:51 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/03 19:26:35 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_env_value(t_env *environ, char *key)
{
	t_env	*curr;
	int		key_len;

	curr = environ;
	key_len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(curr->key, key, key_len + 1) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return ("");
}

void	append_and_free(char **res, char *tmp)
{
	char	*joined;

	joined = ft_strjoin(*res, tmp);
	untrack_pointer(*res);
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
	val = ft_strdup(get_env_value(environ, key));
	untrack_pointer(key);
	return (val);
}
