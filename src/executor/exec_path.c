/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:32:50 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/19 16:55:54 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_command(char *command)
{
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
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

// int	process_child(t_command *cmd, char *command)
// {
// 	struct stat	file;
// 	char		**environ;

// 	if (stat(command, &file) == 0)
// 	{
// 		environ =
// 		execve(command, cmd->args, environ);
// 		perror("exceve");
// 		exit(1);
// 	}
// 	printf("minishell: cmd not found: %s\n", command);
// 	exit(127);
// }

int	exec_path(t_command *cmd)
{
	pid_t	pid;
	char	*command;

	command = get_command(cmd->args[0]);
	if (!command)
		return (printf("ERROR"), 1); // alterar o erro
	pid = fork();
	if (pid < 0)
		return (printf("Error: Failed to fork process"), 1);
	if (pid == 0)
	{
		// process_child(cmd, command);
		execve(command, cmd->args, NULL);
		perror("execve");
		exit(1);
	}
	waitpid(pid, &cmd->status, 0);
	if (WIFEXITED(cmd->status))
		cmd->status = WEXITSTATUS(cmd->status);
	else
		cmd->status = 1;
	untrack_pointer(command);
	return (0);
}

