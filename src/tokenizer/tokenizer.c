/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:39:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/05 21:32:35 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_type	*identify_token(char *input)
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

t_token	*get_token(char *input, t_token_type t_type)
{
	t_token	*token;

	token = ft_collect_mem(1, sizeof(t_token));
	token->type = t_type;
	if (t_type == PIPE || t_type == REDIR_IN || t_type == REDIR_OUT)
		ft_strlcpy(token->value, input, 2);
	else if (t_type == APPEND || t_type == HEREDOC)
		ft_strlcpy(token->value, input, 3);
	else
	{
		
	}
}

t_token	**tokenizer(char *input)
{
	t_token_type	t_type;
	t_token			*token;
	t_token			**tokens;

	tokens = ft_collect_mem(1, sizeof(t_token *));
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input)
		{
			// Identificar token
			t_type = identify_token(input);
			// Coletar token
			token = get_token(input, t_type);
			// Adicionar na lista de tokens
			append_token(tokens, token);
			untrack_pointer(token);
		}
	}
	return (tokens);
}
