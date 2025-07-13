/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:31:16 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/13 18:03:14 by gkana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_node	*parse_command(t_token **tokens)
{
	t_node			*cmd_node;
	t_node			*redir_node;
	t_token_type	redir_type;
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
		else if ((*tokens)->type == REDIR_IN_TOKEN
			|| (*tokens)->type == REDIR_OUT_TOKEN
			|| (*tokens)->type == APPEND_TOKEN
			|| (*tokens)->type == HEREDOC_TOKEN)
		{
			redir_type = consume_token(tokens)->type;
			if (!match_token(tokens, WORD_TOKEN))
			{
				cmd_node->argv[argc] = NULL;
				free_ast(current_cmd_root);
				return (NULL);
			}
			redir_node = new_node(REDIR_NODE, current_cmd_root, NULL);
			redir_node->redir_file = ft_strdup(consume_token(tokens)->value);
			redir_node->redir_type = redir_type;
			current_cmd_root = redir_node;
		}
		else
			break ;
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
