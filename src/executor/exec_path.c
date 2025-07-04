/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:32:50 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/04 16:18:35 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*validate_cmd_path(char *command, int *res)
{
	struct stat	info;

	if (!command || !command[0])
		return (NULL);
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) != 0 || stat(command, &info) != 0)
		{
			if (errno == EACCES)
				*res = -1;
			else if (errno == ENOENT)
				*res = -2;
			return (NULL);
		}
		if (S_ISDIR(info.st_mode))
		{
			*res = -3;
			return (NULL);
		}
		*res = 0;
		return (ft_strdup(command));
	}
	return (NULL);
}

char	*get_command(t_command *cmd, char *command)
{
	t_env	*path;
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	path = get_env(cmd->env_list, "PATH");
	if (!path || !path->value)
		return (NULL);
	paths = ft_split(path->value, ':');
	if (paths == NULL)
		return (0);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		untrack_pointer(tmp);
		if (access(full_path, X_OK) == 0)
			break ;
		untrack_pointer(full_path);
		full_path = NULL;
		i++;
	}
	while (paths[i])
		untrack_pointer(paths[i++]);
	return (full_path);
}

int	process_child(char **args, t_command *cmd, char *command)
{
	struct stat	file;
	char		**environ;

	environ = environ_list(cmd->env_list, count_env(cmd->env_list));
	if (!environ)
	{
		perror("malloc");
		exit (1);
	}
	if (stat(command, &file) == 0)
	{
		if (cmd->input_fd != STDIN_FILENO)
		{
			dup2(cmd->input_fd, STDIN_FILENO);
			close(cmd->input_fd);
		}
		if (cmd->output_fd != STDOUT_FILENO)
		{
			dup2(cmd->output_fd, STDOUT_FILENO);
			close(cmd->output_fd);
		}
		execve(command, args, environ);
		perror("exceve");
		ft_free_matrix(environ);
		exit(1);
	}
	printf("minishell: %s: could not execute command\n", command);
	exit(-1);
}

int	process_parent(t_command *cmd, pid_t pid)
{
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	waitpid(pid, &cmd->status, 0);
	if (WIFEXITED(cmd->status))
		cmd->status = WEXITSTATUS(cmd->status);
	else if (WIFSIGNALED(cmd->status) && WTERMSIG(cmd->status) == SIGINT)
	{
		ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		cmd->status = 128 + WTERMSIG(cmd->status);
	}
	return (cmd->status);
}

int	exec_path(char **args, t_command *cmd)
{
	pid_t	pid;
	char	*command;
	int		res;

	res = 0;
	command = validate_cmd_path(args[0], &res);
	if (res < 0)
		return (print_cmd_error(args[0], res));
	if (!command)
	{
		command = get_command(cmd, args[0]);
		if (!command)
			return (print_cmd_error(args[0], res));
	}
	pid = fork();
	process_signals(pid);
	if (pid < 0)
		return (error_handler("Error: Failed to fork process\n"), 1);
	if (pid == 0)
		res = process_child(args, cmd, command);
	if (pid > 0)
		res = process_parent(cmd, pid);
	untrack_pointer(command);
	return (res);
}

