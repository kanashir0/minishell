/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:25:24 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/13 15:32:44 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_command	*cmd;
	t_node		*ast;

	(void)ac;
	cmd = init_command();
	init_env(cmd, envp);
	init_under(cmd, av[0]);
	setup_signals();
	while (42)
	{
		read_input(cmd);
		if (!is_empty_input(cmd->input))
		{
			cmd->tokens = tokenizer(cmd->input);
			if (!cmd->tokens)
			{
				free(cmd->input);
				cmd->input = NULL;
				continue ;
			}
			expand_tokens(cmd->tokens, cmd->env_list, cmd->status);
			ast = generate_ast(cmd->tokens);
			execute_ast(ast);
			free_ast(ast);
		}
	}
	ft_clear_mem();
	return (0);
}
