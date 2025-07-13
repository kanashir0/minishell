/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:46:31 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/13 15:33:55 by cbrito-s         ###   ########.fr       */
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
	t_token	*cur = *tokens;
	char	*expanded;

	while (cur)
	{
		if (cur->type == WORD_TOKEN && cur->value)
		{
			expanded = expand_string(cur->value, env, status);
			untrack_pointer(cur->value);   // libera a string antiga
			cur->value = expanded;         // seta a nova
		}
		cur = cur->next;
	}
}

// void	expand(t_node *node)
// {
// 	t_command	*cmd;
// 	t_env		*environ;
// 	int			index;
// 	char		*new;

// 	cmd = get_cmd_context(NULL);
// 	environ = cmd->env_list;
// 	if (!node)
// 		return ;
// 	if (node->type == WORD_NODE && node->argv)
// 	{
// 		index = 0;
// 		while (node->argv[index])
// 		{
// 			new = expand_string(node->argv[index], environ, cmd->status);
// 			node->argv[index] = new;
// 			index++;
// 		}
// 	}
// 	expand(node->left);
// 	expand(node->right);
// }
