/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:46:31 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/03 19:24:14 by cbrito-s         ###   ########.fr       */
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
			(*i)++;
			if (input[*i] == '?')
			{
				tmp = ft_itoa(status);
				(*i)++;
			}
			else
				tmp = extract_env_value(input, i, ev);
		}
		else
		{
			tmp = ft_substr(input, *i, 1);
			(*i)++;
		}
		append_and_free(res, tmp);
	}
	if (input[*i] == '"')
		(*i)++;
}

static void	unquoted(char *input, int *i, char **res, t_env *ev, int status)
{
	char	*tmp;

	if (input[*i] == '$')
	{
		(*i)++;
		if (input[*i] == '?')
		{
			tmp = ft_itoa(status);
			(*i)++;
		}
		else
			tmp = extract_env_value(input, i, ev);
	}
	else
	{
		tmp = ft_substr(input, *i, 1);
		(*i)++;
	}
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

void	expand(t_node *node)
{
	t_command	*cmd;
	t_env		*environ;
	int			status;
	int			index;
	char		*new;

	cmd = get_cmd_context(NULL);
	environ = cmd->env_list;
	status = cmd->status;
	if (!node)
		return ;
	if (node->type == WORD_NODE && node->argv)
	{
		index = 0;
		while (node->argv[index])
		{
			new = expand_string(node->argv[index], environ, status);
			free(node->argv[index]);
			node->argv[index] = new;
			index++;
		}
	}
	expand(node->left);
	expand(node->right);
}
