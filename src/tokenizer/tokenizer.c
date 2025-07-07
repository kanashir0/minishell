/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:39:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/07 19:33:20 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_type	identify_token(char *input)
{
	if (!ft_strncmp(input, ">>", 2))
		return (APPEND_TOKEN);
	else if (!ft_strncmp(input, "<<", 2))
		return (HEREDOC_TOKEN);
	else if (!ft_strncmp(input, "|", 1))
		return (PIPE_TOKEN);
	else if (!ft_strncmp(input, "<", 1))
		return (REDIR_IN_TOKEN);
	else if (!ft_strncmp(input, ">", 1))
		return (REDIR_OUT_TOKEN);
	else
		return (WORD_TOKEN);
}

int	get_token_len(char *input, t_token_type t_type)
{
	int		len;
	int		delta;

	len = 0;
	if (t_type == PIPE_TOKEN || t_type == REDIR_IN_TOKEN
		|| t_type == REDIR_OUT_TOKEN)
		return (1);
	if (t_type == APPEND_TOKEN || t_type == HEREDOC_TOKEN)
		return (2);
	while (input[len] && !ft_isspace(input[len])
		&& (identify_token(input + len) == WORD_TOKEN))
	{
		if ((delta = handle_escape(input, len)) > 0)
			len += delta;
		else if (input[len] == '\"' || input[len] == '\'')
		{
			delta = handle_quote(input, len);
			if (delta < 0)
				return (syntax_error_unclosed_quote(), -1);
			len += delta;
		}
		else
			len++;
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
	if (t_type == WORD_TOKEN && token->value)
	{
		char *clean = remove_backslashes(token->value);
		untrack_pointer(token->value);
		token->value = clean;
	}
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

	tokens = ft_collect_mem(1, sizeof(t_token *));
	if (!tokens)
		error_handler("Memory allocation error.\n");
	*tokens = NULL;
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input)
		{
			t_type = identify_token(input);
			token_len = get_token_len(input, t_type);
			if (token_len < 0)
				return (free_token_list(tokens), NULL);
			token = get_token(input, t_type, token_len);
			append_token(tokens, token);
			input += token_len;
		}
	}
	return (tokens);
}
