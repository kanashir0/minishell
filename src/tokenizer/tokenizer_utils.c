/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:21:41 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/22 11:32:00 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
