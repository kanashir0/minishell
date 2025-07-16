/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:05:28 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/16 16:02:32 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*new_node(t_node_type n_type, t_node *left, t_node *right)
{
	t_node	*node;

	node = ft_collect_mem(1, sizeof(t_node));
	node->type = n_type;
	node->right = right;
	node->left = left;
	return (node);
}

void	free_ast(t_node *node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	i = 0;
	if (node->type == WORD_NODE && node->argv)
	{
		while (node->argv[i])
			untrack_pointer(node->argv[i++]);
		untrack_pointer(node->argv);
	}
	if (node->type == REDIR_NODE && node->redir_file)
		untrack_pointer(node->redir_file);
	untrack_pointer(node);
	return ;
}
