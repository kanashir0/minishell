/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:22:29 by gkana             #+#    #+#             */
/*   Updated: 2025/07/13 18:11:13 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	preprocess_heredocs(t_node *node)
{
	char	*tmp_file;

	if (!node)
		return ;
	if (node->type == REDIR_NODE && node->redir_type == HEREDOC_TOKEN)
	{
		tmp_file = handle_heredoc(node->redir_file);
		if (!tmp_file)
			return ;
		add_heredoc_file(get_cmd_context(NULL), tmp_file);
		untrack_pointer(node->redir_file);
		node->redir_file = tmp_file;
		node->redir_type = REDIR_IN_TOKEN;
	}
	preprocess_heredocs(node->left);
	preprocess_heredocs(node->right);
}
