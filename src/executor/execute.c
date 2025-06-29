/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:12:13 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/29 17:43:40 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int open_redir_file(t_token_type type, const char *filename)
{
	int	fd;

	fd = -1;
	if (type == REDIR_OUT_TOKEN)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND_TOKEN)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_IN_TOKEN)
		fd = open(filename, O_RDONLY);
	else if (type == HEREDOC_TOKEN)
		return (-1); //TODO: implementar HEREDOC
	else
		return (-1);
	if (fd < 0)
		perror("open error");
	return (fd);
}

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
	int	res;

	res = is_builtin(cmd);
	if (res == -1)
		printf("executar pelo $PATH");
	return ;
}
