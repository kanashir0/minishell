/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:05:28 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/22 12:17:53 by gyasuhir         ###   ########.fr       */
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

void	print_ast(t_node *ast, int indent)
{
	if (!ast) return ;
	for (int i = 0; i < indent; i++) printf("\t");
	switch (ast->type) {
		case WORD_NODE:
			printf("WORD: ");
			for (int i = 0; ast->argv && ast->argv[i]; i++)
				printf(" %s", ast->argv[i]);
			printf("\n");
			break;
		case PIPE_NODE:
			printf("PIPE\n");
			print_ast(ast->left, indent + 1);
			print_ast(ast->right, indent + 1);
			break;
		case REDIR_NODE:
			printf("REDIR (%s): %s\n",
				ast->redir_type == REDIR_OUT_TOKEN ? ">" : "<",
				ast->redir_file);
			print_ast(ast->left, indent + 1);
			break;
	}
}
