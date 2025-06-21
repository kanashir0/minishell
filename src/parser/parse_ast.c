/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:31:16 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/21 17:38:48 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**consume_words(t_token **tokens)
{
	
}

t_node	*parse_word(t_token **tokens)
{
	
}

t_node	*parse_pipe(t_token **tokens)
{
	t_node	*left;

	left = parse_word(tokens);
	if (!left)
		return (NULL);
	if ((*tokens)->value == '|')
	{
		// consume token
		pipe_node = ft_collect_mem(1, sizeof(t_node));
		pipe_node->right = parse_word(tokens);
		pipe_node->left = left;
	}
	
}

t_node	*generate_ast(t_token **tokens)
{
	return parse_pipe(tokens);
}
