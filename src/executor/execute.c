/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:12:13 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/24 17:24:21 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!ft_strncmp(cmd->args[0], "echo", 4) && ft_strlen(cmd->args[0]) == 4)
		return (echo(cmd->args));
	if (!ft_strncmp(cmd->args[0], "cd", 2) && ft_strlen(cmd->args[0]) == 2)
		return (cd(cmd->args, cmd));
	if (!ft_strncmp(cmd->args[0], "pwd", 3) && ft_strlen(cmd->args[0]) == 3)
		return (pwd(cmd));
	if (!ft_strncmp(cmd->args[0], "export", 6) && ft_strlen(cmd->args[0]) == 6)
		return (export(cmd->args, cmd));
	if (!ft_strncmp(cmd->args[0], "unset", 5) && ft_strlen(cmd->args[0]) == 5)
		return (unset(cmd->args, cmd));
	if (!ft_strncmp(cmd->args[0], "env", 3) && ft_strlen(cmd->args[0]) == 3)
		return (env(cmd->args, cmd));
	if (!ft_strncmp(cmd->args[0], "exit", 4) && ft_strlen(cmd->args[0]) == 4)
		return (builtin_exit(cmd->args, cmd));
	return (-1);
}

void	execute(t_command *cmd)
{
	cmd->status = is_builtin(cmd);
	if (cmd->status == -1)
		cmd->status = exec_path(cmd);
	// printf("Status code: %d\n", cmd->status);
	return ;
}
