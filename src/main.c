/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:25:24 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/05 19:29:26 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	gambiarra(t_command *cmd)
{
	cmd->args = ft_split(cmd->input, ' ');
}

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
			ast = generate_ast(cmd->tokens);
			expand(ast);
			execute_ast(ast);
			// TODO: clear_ast(ast);
		}
	}
	ft_clear_mem();
	return (0);
}
