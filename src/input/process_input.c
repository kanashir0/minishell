/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 22:22:56 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/17 22:12:48 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_tokenization(t_command *cmd)
{
	cmd->tokens = tokenizer(cmd->input);
	if (!cmd->tokens)
	{
		free(cmd->input);
		cmd->input = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	handle_expansion(t_command *cmd)
{
	expand_tokens(cmd->tokens, cmd->status);
	if (*(cmd->tokens) == NULL)
	{
		cmd->status = 0;
		free(cmd->input);
		cmd->input = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_node	*handle_ast_generation(t_command *cmd)
{
	t_node	*ast;

	ast = generate_ast(cmd->tokens);
	if (!ast)
	{
		free(cmd->input);
		cmd->input = NULL;
	}
	return (ast);
}

static int	process_heredocs(t_node *ast, t_command *cmd)
{
	if (preprocess_heredocs(ast) == -1)
	{
		free_ast(ast);
		cleanup_heredocs(cmd);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	process_input(t_command *cmd)
{
	t_node	*ast;

	read_input(cmd);
	if (is_empty_input(cmd->input))
		return ;
	if (handle_tokenization(cmd) != SUCCESS)
		return ;
	if (handle_expansion(cmd) != SUCCESS)
		return ;
	ast = handle_ast_generation(cmd);
	if (!ast)
		return ;
	if (process_heredocs(ast, cmd) != SUCCESS)
		return ;
	execute_ast(ast);
	free_ast(ast);
	cleanup_heredocs(cmd);
}
