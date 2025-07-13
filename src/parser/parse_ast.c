/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:31:16 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/13 17:24:14 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	append_redirection(t_node **current_cmd_root,
	t_node *cmd_node, t_node *redir_node)
{
	t_node	*last_redir;

	if ((*current_cmd_root)->type != REDIR_NODE)
	{
		redir_node->left = cmd_node;
		*current_cmd_root = redir_node;
	}
	else
	{
		last_redir = *current_cmd_root;
		while (last_redir->left && last_redir->left->type == REDIR_NODE)
			last_redir = last_redir->left;
		redir_node->left = last_redir->left;
		last_redir->left = redir_node;
	}
}

static int	handle_redir_token(t_token **tokens,
	t_node **current_cmd_root, t_node *cmd_node)
{
	t_node	*redir_node;

	redir_node = new_node(REDIR_NODE, NULL, NULL);
	redir_node->redir_type = consume_token(tokens)->type;
	if (!match_token(tokens, WORD_TOKEN))
	{
		free_ast(*current_cmd_root);
		untrack_pointer(redir_node);
		return (-1);
	}
	redir_node->redir_file = ft_strdup(consume_token(tokens)->value);
	append_redirection(current_cmd_root, cmd_node, redir_node);
	return (0);
}

static t_node	*parse_command(t_token **tokens)
{
	t_node			*cmd_node;
	t_node			*current_cmd_root;
	int				argc;

	cmd_node = new_node(WORD_NODE, NULL, NULL);
	cmd_node->argv = ft_collect_mem(1, sizeof(char *) * 64);
	argc = 0;
	current_cmd_root = cmd_node;
	while (*tokens && (*tokens)->type != PIPE_TOKEN)
	{
		if ((*tokens)->type == WORD_TOKEN)
			cmd_node->argv[argc++] = ft_strdup(consume_token(tokens)->value);
		else if (handle_redir_token(tokens, &current_cmd_root, cmd_node) == -1)
			return (NULL);
	}
	cmd_node->argv[argc] = NULL;
	if (argc == 0 && current_cmd_root == cmd_node)
	{
		free_ast(cmd_node);
		return (NULL);
	}
	return (current_cmd_root);
}

t_node	*parse_pipe(t_token **tokens)
{
	t_node	*left;
	t_node	*right;
	t_node	*pipe;

	left = parse_command(tokens);
	if (!left)
		return (NULL);
	while (match_token(tokens, PIPE_TOKEN))
	{
		consume_token(tokens);
		right = parse_command(tokens);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		pipe = new_node(PIPE_NODE, left, right);
		left = pipe;
	}
	return (left);
}

t_node	*generate_ast(t_token **tokens)
{
	return (parse_pipe(tokens));
}
