/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:12:13 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/05/25 15:27:01 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h" 

int	is_builtin(t_command *cmd)
{
	if (!ft_strncmp(cmd->args[0], "echo", 4) && ft_strlen(cmd->args[0]) == 4)
		return (echo(cmd->args));
	return (-1);
}

void	execute(t_command *cmd)
{
	int	res;

	res = is_builtin(cmd);
	if (res == -1)
		printf("executar pelo $PATH");
	return ;
}