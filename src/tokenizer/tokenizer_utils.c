/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:21:41 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/21 17:27:19 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	consume_token(t_token **tokens)
{
	t_token	*t;

	if (!tokens || !*tokens)
		return ;
	t = *tokens;
	tokens = &(t->next);
	return ;
}

int	match_token(t_token **tokens, t_token_type t_type)
{
	return (*tokens && ((*tokens)->type == t_type));
}
