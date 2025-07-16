/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:12:13 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/16 19:59:36 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipe_child_left(t_node *node, int fd[2])
{
	int	status;

	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_handler(FORK);
	close(fd[1]);
	status = execute_node(node);
	ft_clear_mem();
	exit(status);
}

void	pipe_child_right(t_node *node, int fd[2])
{
	int	status;

	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_handler(FORK);
	close(fd[0]);
	status = execute_node(node);
	ft_clear_mem();
	exit(status);
}

int	open_redir_file(t_token_type type, char *filename)
{
	int	fd;

	fd = -1;
	if (type == REDIR_OUT_TOKEN)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND_TOKEN)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_IN_TOKEN)
		fd = open(filename, O_RDONLY);
	else
		return (-1);
	if (fd < 0)
	{
		if (errno == ENOENT)
			print_cmd_error(filename, -2);
		else
			print_cmd_error(filename, -1);
	}
	return (fd);
}

int	is_builtin(char **args, t_command *cmd)
{
	if (!ft_strncmp(args[0], "echo", 4) && ft_strlen(args[0]) == 4)
		return (echo(args));
	if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
		return (cd(args, cmd));
	if (!ft_strncmp(args[0], "pwd", 3) && ft_strlen(args[0]) == 3)
		return (pwd(cmd));
	if (!ft_strncmp(args[0], "export", 6) && ft_strlen(args[0]) == 6)
		return (export(args, cmd));
	if (!ft_strncmp(args[0], "unset", 5) && ft_strlen(args[0]) == 5)
		return (unset(args, cmd));
	if (!ft_strncmp(args[0], "env", 3) && ft_strlen(args[0]) == 3)
		return (env(args, cmd));
	if (!ft_strncmp(args[0], "exit", 4) && ft_strlen(args[0]) == 4)
		return (builtin_exit(args, cmd));
	return (-1);
}
