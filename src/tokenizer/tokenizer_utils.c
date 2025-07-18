/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:21:41 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/16 17:11:31 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_empty_token(t_token **tokens, t_token *curr, t_token *prev)
{
	t_token	*to_delete;

	to_delete = curr;
	if (prev)
		prev->next = curr->next;
	else
		*tokens = curr->next;
	curr = curr->next;
	untrack_pointer(to_delete->value);
}

void	free_token_list(t_token **tokens)
{
	t_token	*curr;
	t_token	*next;

	if (!tokens)
		return ;
	curr = *tokens;
	while (curr)
	{
		next = curr->next;
		if (curr->value)
			untrack_pointer(curr->value);
		untrack_pointer(curr);
		curr = next;
	}
	untrack_pointer(tokens);
}

t_token	*consume_token(t_token **tokens)
{
	t_token	*t;

	if (!tokens || !*tokens)
		return (NULL);
	t = *tokens;
	*tokens = (*tokens)->next;
	return (t);
}

int	match_token(t_token **tokens, t_token_type t_type)
{
	return (*tokens && (*tokens)->type == t_type);
}
