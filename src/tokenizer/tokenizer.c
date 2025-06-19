/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:39:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/19 16:08:22 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_type	identify_token(char *input)
{
	if (!ft_strncmp(input, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(input, "<", 1))
		return (REDIR_IN);
	else if (!ft_strncmp(input, ">", 1))
		return (REDIR_OUT);
	else if (!ft_strncmp(input, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(input, "<<", 2))
		return (HEREDOC);
	else
		return (WORD);
}

int	get_token_len(char *input, t_token_type t_type)
{
	int	len;

	len = 0;
	if (t_type == PIPE || t_type == REDIR_IN || t_type == REDIR_OUT)
		return (1);
	else if (t_type == APPEND || t_type == HEREDOC)
		return (2);
	else
	{
		while (*input && !ft_isspace(*input) && (identify_token(input) == WORD))
		{
			len++;
			input++;
		}
	}
	return (len);
}

t_token	*get_token(char *input, t_token_type t_type, size_t token_len)
{
	t_token	*token;

	token = ft_collect_mem(1, sizeof(t_token));
	if (!token)
		error_handler("Memory allocation error.\n");
	token->type = t_type;
	token->value = ft_collect_mem(1, token_len + 1);
	if (!token->value)
		error_handler("Memory allocation error.\n");
	ft_strlcpy(token->value, input, token_len + 1);
	return (token);
}

void	append_token(t_token **tokens, t_token *token)
{
	t_token	*last_token;

	if (!token)
		return ;
	if (!*tokens)
		*tokens = token;
	else
	{
		last_token = *tokens;
		while (last_token->next)
			last_token = last_token->next;
		last_token->next = token;
	}
}

t_token	**tokenizer(char *input)
{
	t_token_type	t_type;
	t_token			*token;
	t_token			**tokens;
	int				token_len;

	tokens = ft_collect_mem(1, sizeof(t_token **));
	if (!tokens)
		error_handler("Memory allocation error.\n");
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input)
		{
			t_type = identify_token(input);
			token_len = get_token_len(input, t_type);
			token = get_token(input, t_type, token_len);
			append_token(tokens, token);
			input += token_len;
		}
	}
	return (tokens);
}
