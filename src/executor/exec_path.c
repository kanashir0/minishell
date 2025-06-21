/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:32:50 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/21 14:40:43 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**environ_list(t_env *env_list)
{
	t_env	*node;
	char	**envp;
	char	*tmp;
	int		i;
	int		count;

	if (!env_list)
		return (NULL);
	count = 0;
	node = env_list;
	while (node)
	{
		count++;
		node = node->next;
	}
	envp = ft_collect_mem(sizeof(char *), count + 1);
	if (!envp)
		return (NULL);
	i = 0;
	node = env_list;
	while (node)
	{
		tmp = ft_strjoin(node->key, "=");
		envp[i] = ft_strjoin(tmp, node->value);
		untrack_pointer(tmp);
		i++;
		node = node->next;
	}
	envp[i] = NULL;
	return (envp);
}

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

int	process_child(t_command *cmd, char *command)
{
	struct stat	file;
	char		**environ;

	environ = environ_list(cmd->env_list);
	if (!environ)
	{
		perror("malloc");
		exit (1);
	}
	if (stat(command, &file) == 0)
	{
		execve(command, cmd->args, environ);
		perror("exceve");
		ft_free_matrix(environ);
		exit(1);
	}
	printf("minishell: cmd not found: %s\n", command);
	exit(127);
}

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
		process_child(cmd, command);
	waitpid(pid, &cmd->status, 0);
	if (WIFEXITED(cmd->status))
		cmd->status = WEXITSTATUS(cmd->status);
	else
		cmd->status = 1;
	untrack_pointer(command);
	return (0);
}

